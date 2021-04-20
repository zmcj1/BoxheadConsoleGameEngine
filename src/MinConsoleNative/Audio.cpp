﻿#include "Audio.h"
#include "File.h"
//Provide MCI interface, mmsystem header file depends on Windows.h
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinMCISendString(_IN_ const wchar* str)
    {
        MCIERROR mci_result = ::mciSendString(str, nullptr, 0, nullptr);
        LastMCIResult = mci_result;
        return mci_result == 0;
    }

    EXPORT_FUNC_EX(bool) MinMCISendStringEx(_IN_ const wchar* str, _OUT_ wchar* returnStr, int returnStrLen)
    {
        MCIERROR mci_result = ::mciSendString(str, returnStr, returnStrLen, nullptr);
        LastMCIResult = mci_result;
        return mci_result == 0;
    }

    EXPORT_FUNC_EX(bool) MinMCIGetErrorString(_OUT_ wchar* errStr, int errStrLen)
    {
        return ::mciGetErrorString(LastMCIResult, errStr, errStrLen);
    }

    EXPORT_FUNC_EX(bool) MinPlaySound(_IN_ const wchar* path, bool repeatPlay)
    {
        if (repeatPlay)
        {
            return ::PlaySound(path, nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
        }
        else
        {
            return ::PlaySound(path, nullptr, SND_FILENAME | SND_ASYNC);
        }
    }

    EXPORT_FUNC_EX(bool) MinInitSoundPool(_IN_ const wchar* path)
    {
        //can't add the same key.
        if (SoundPools.count(path) != 0)
        {
            return false;
        }
        const int Count = 32;
        ObjectPool<MCIAudio>* pool = new ObjectPool<MCIAudio>(0);
        for (size_t i = 0; i < Count; i++)
        {
            MCIAudio* mciAudio = new MCIAudio;
            bool init_suc = MinInitMCIAudio(mciAudio, path);
            if (!init_suc)
            {
                delete mciAudio;
                return false;
            }
            pool->ReturnInstance(mciAudio);
        }
        SoundPools[path] = pool;
        return true;
    }

    EXPORT_FUNC_EX(bool) MinDeinitSoundPool(_IN_ const wchar* path)
    {
        //doesn't exsist
        if (SoundPools.count(path) == 0)
        {
            return false;
        }
        ObjectPool<MCIAudio>* pool = SoundPools[path];
        for (size_t i = 0; i < pool->pool.size(); i++)
        {
            MCIAudio* mciAudio = pool->pool[i];
            MinDeinitMCIAudio(mciAudio);
        }
        delete pool;
        return true;
    }

    EXPORT_FUNC_EX(bool) MinPlayOneShot(_IN_ const wchar* path, double volumeScale)
    {
        //doesn't exsist
        if (SoundPools.count(path) == 0)
        {
            return false;
        }
        ObjectPool<MCIAudio>* pool = SoundPools[path];
        MCIAudio* mciAudio = pool->GetInstance();

        int volume = volumeScale * 1000;
        bool set_volume_suc = MinSetMCIAudioVolume(mciAudio, volume);
        if (!set_volume_suc)
        {
            return false;
        }

        bool play_suc = MinPlayMCIAudio(mciAudio, false, false);
        if (!play_suc)
        {
            return false;
        }

        PlayingSounds.push_back(mciAudio);
        return true;
    }

    EXPORT_FUNC_EX(void) MinCleanShots()
    {
        for (size_t i = 0; i < PlayingSounds.size(); i++)
        {
            MCIAudio* mciAudio = PlayingSounds[i];
            if (MinGetMCIAudioIsOver(mciAudio))
            {
                SoundPools[mciAudio->Path]->ReturnInstance(mciAudio);
            }
        }
    }

    EXPORT_FUNC_EX(bool) MinInitMCIAudio(_OUT_ MCIAudio* mciAudio, _IN_ const wchar* path)
    {
        ::wcscpy_s(mciAudio->Path, ::wcslen(path) + 1, path);

        wstring extension = File::GetFileExtension(path);
        ::wcscpy_s(mciAudio->Extension, ::wcslen(extension.c_str()) + 1, extension.c_str());

        wstring alias = MCIAlias + to_wstring(MCIAliasIncrement++);
        ::wcscpy_s(mciAudio->Alias, ::wcslen(alias.c_str()) + 1, alias.c_str());

        //open the audio with alias.(should close audio when you dont use it.)
        wstring shortPathName = File::ToShortPathName(path);
        bool openSuccess = Audio::MCISendString(_T("open ") + shortPathName + L" alias " + alias);
        if (!openSuccess)
        {
            return false;
        }

        //get the length of the audio(you can directly use this cmd without open operation)
        wstring length = Audio::MCISendStringEx(_T("status ") + alias + _T(" length"));
        mciAudio->TotalMilliSecond = ::_wtoi(length.c_str());
        mciAudio->Minute = (int)(mciAudio->TotalMilliSecond / 1000 / 60);
        mciAudio->Second = mciAudio->TotalMilliSecond / 1000 - mciAudio->Minute * 60;
        mciAudio->MilliSecond = mciAudio->TotalMilliSecond % 1000;

        return true;
    }

    EXPORT_FUNC_EX(bool) MinDeinitMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        bool closeSuccess = Audio::MCISendString(L"close " + wstring(mciAudio->Alias));
        delete mciAudio;
        return closeSuccess;
    }

    EXPORT_FUNC_EX(bool) MinPlayMCIAudio(_IN_ MCIAudio* mciAudio, bool repeat, bool wait)
    {
        return MinPlayMCIAudioEx(mciAudio, repeat, wait, 0, mciAudio->TotalMilliSecond);
    }

    EXPORT_FUNC_EX(bool) MinPlayMCIAudioEx(_IN_ MCIAudio* mciAudio, bool repeat, bool wait, int from, int to)
    {
        //Use alias instead of path as param to implement API:PlayOneShot!
        wstring cmd = _T("play ") + wstring(mciAudio->Alias);

        //from x ms to y ms
        cmd += L" from " + to_wstring(from) + L" to " + to_wstring(to);

        //NOTICE:if play .wav music, repeat is useless. If file is .wav and repeat is on, it will fail. Seems it's a bug in MCI.
        if (repeat && !String::CompareIgnoreCase(L".wav", mciAudio->Extension))
        {
            cmd += L" repeat";
        }
        //wait will block the thread.
        if (wait)
        {
            cmd += L" wait";
        }

        bool suc = Audio::MCISendString(cmd);
        return suc;
    }

    EXPORT_FUNC_EX(bool) MinStopMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        return Audio::MCISendString(L"stop " + wstring(mciAudio->Alias));
    }

    EXPORT_FUNC_EX(bool) MinPauseMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        bool pause_suc = Audio::MCISendString(L"pause " + wstring(mciAudio->Alias));
        return pause_suc;
    }

    EXPORT_FUNC_EX(bool) MinResumeMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        bool resume_suc = Audio::MCISendString(L"resume " + wstring(mciAudio->Alias));
        return resume_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioVolume(_IN_ MCIAudio* mciAudio)
    {
        //get the volume of this audio(you should open audio before call this)
        wstring volume = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->Alias) + _T(" volume"));
        return ::_wtoi(volume.c_str());
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioVolume(_IN_ MCIAudio* mciAudio, int volume)
    {
        bool set_volume_suc = Audio::MCISendString(_T("setaudio ") + wstring(mciAudio->Alias) + _T(" volume to ") + to_wstring(volume));
        return set_volume_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioPosition(_IN_ MCIAudio* mciAudio)
    {
        wstring position = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->Alias) + _T(" position"));
        int pos = ::_wtoi(position.c_str());
        return pos;
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioPosition(_IN_ MCIAudio* mciAudio, int position)
    {
        bool seek_suc = Audio::MCISendString(_T("seek ") + wstring(mciAudio->Alias) + _T(" to ") + to_wstring(position));
        return seek_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioSpeed(_IN_ MCIAudio* mciAudio)
    {
        wstring speed = Audio::MCISendStringEx(L"status " + wstring(mciAudio->Alias) + L" speed");
        return ::_wtoi(speed.c_str());
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioSpeed(_IN_ MCIAudio* mciAudio, int speed)
    {
        bool set_speed_suc = Audio::MCISendString(L"set " + wstring(mciAudio->Alias) + L" speed " + to_wstring(speed));
        return set_speed_suc;
    }

    EXPORT_FUNC_EX(MCIAudioMode) MinGetMCIAudioMode(_IN_ MCIAudio* mciAudio)
    {
        wstring mode = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->Alias) + _T(" mode"));
        if (String::CompareIgnoreCase(mode, L"not ready"))
        {
            return MCIAudioMode::NotReady;
        }
        else if (String::CompareIgnoreCase(mode, L"paused"))
        {
            return MCIAudioMode::Paused;
        }
        else if (String::CompareIgnoreCase(mode, L"playing"))
        {
            return MCIAudioMode::Playing;
        }
        else if (String::CompareIgnoreCase(mode, L"stopped"))
        {
            return MCIAudioMode::Stopped;
        }
        else
        {
            return MCIAudioMode::Unknown;
        }
    }

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsPlaying(_IN_ MCIAudio* mciAudio)
    {
        MCIAudioMode audioMode = MinGetMCIAudioMode(mciAudio);
        return audioMode == MCIAudioMode::Playing;
    }

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOver(_IN_ MCIAudio* mciAudio)
    {
        return MinGetMCIAudioIsOverEx(mciAudio, mciAudio->TotalMilliSecond);
    }

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOverEx(_IN_ MCIAudio* mciAudio, int length)
    {
        MCIAudioMode mode = MinGetMCIAudioMode(mciAudio);
        if (mode == MCIAudioMode::Stopped)
        {
            int curPos = MinGetMCIAudioPosition(mciAudio);
            if (curPos >= length)
            {
                return true;
            }
        }
        return false;
    }

    bool Audio::MCISendString(const wstring& cmd)
    {
        return MinMCISendString(cmd.c_str());
    }

    wstring Audio::MCISendStringEx(const wstring& cmd)
    {
        wchar res[MAX_PATH] = { 0 };
        MinMCISendStringEx(cmd.c_str(), res, MAX_PATH);
        wstring result(res);
        return result;
    }

    Audio::Audio(const wstring& path)
    {
        this->mciAudio = new MCIAudio;
        bool init_suc = MinInitMCIAudio(this->mciAudio, path.c_str());
        if (!init_suc)
        {
            delete this->mciAudio;
        }
    }

    Audio::~Audio()
    {
        MinDeinitMCIAudio(this->mciAudio);
    }

    bool Audio::Play(bool repeat, bool wait)
    {
        return MinPlayMCIAudio(this->mciAudio, repeat, wait);
    }

    bool Audio::PlayEx(bool repeat, bool wait, int from, int to)
    {
        return MinPlayMCIAudioEx(this->mciAudio, repeat, wait, from, to);
    }

    bool Audio::Stop()
    {
        return MinStopMCIAudio(this->mciAudio);
    }

    bool Audio::Pause()
    {
        return MinPauseMCIAudio(this->mciAudio);
    }

    bool Audio::Resume()
    {
        return MinResumeMCIAudio(this->mciAudio);
    }

    int Audio::GetVolume()
    {
        return MinGetMCIAudioVolume(this->mciAudio);
    }

    bool Audio::SetVolume(int volume)
    {
        return MinSetMCIAudioVolume(this->mciAudio, volume);
    }

    int Audio::GetPosition()
    {
        return MinGetMCIAudioPosition(this->mciAudio);
    }

    bool Audio::SetPosition(int position)
    {
        return MinSetMCIAudioPosition(this->mciAudio, position);
    }

    int Audio::GetSpeed()
    {
        return MinGetMCIAudioSpeed(this->mciAudio);
    }

    bool Audio::SetSpeed(int speed)
    {
        return MinSetMCIAudioSpeed(this->mciAudio, speed);
    }

    MCIAudioMode Audio::GetMode()
    {
        return MinGetMCIAudioMode(this->mciAudio);
    }

    bool Audio::IsPlaying()
    {
        return MinGetMCIAudioIsPlaying(this->mciAudio);
    }

    bool Audio::IsOver()
    {
        return MinGetMCIAudioIsOver(this->mciAudio);
    }

    bool Audio::IsOverEx(int length)
    {
        return MinGetMCIAudioIsOverEx(this->mciAudio, length);
    }
}