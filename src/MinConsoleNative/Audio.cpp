#include "Audio.h"
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

    EXPORT_FUNC_EX(bool) MinPlayOneShot(_IN_ const wchar* path, double volumeScale)
    {
        return false;
    }

    EXPORT_FUNC_EX(bool) MinInitMCIAudio(_OUT_ MCIAudio* mciAudio, _IN_ const wchar* path)
    {
        ::wcscpy_s(mciAudio->Path, ::wcslen(path) + 1, path);

        wstring shortPathName = File::ToShortPathName(path);
        ::wcscpy_s(mciAudio->ShortPathName, ::wcslen(shortPathName.c_str()) + 1, shortPathName.c_str());

        wstring extension = File::GetFileExtension(path);
        ::wcscpy_s(mciAudio->Extension, ::wcslen(extension.c_str()) + 1, extension.c_str());

        //open the audio(should close audio when you dont use it.)
        bool openSuccess = Audio::MCISendString(_T("open ") + shortPathName);
        if (!openSuccess)
        {
            return false;
        }

        //get the length of the audio(you can directly use this cmd without open operation)
        wstring length = Audio::MCISendStringEx(_T("status ") + shortPathName + _T(" length"));
        mciAudio->TotalMilliSecond = ::_wtoi(length.c_str());
        mciAudio->Minute = (int)(mciAudio->TotalMilliSecond / 1000 / 60);
        mciAudio->Second = mciAudio->TotalMilliSecond / 1000 - mciAudio->Minute * 60;
        mciAudio->MilliSecond = mciAudio->TotalMilliSecond % 1000;

        return true;
    }

    EXPORT_FUNC_EX(bool) MinDeinitMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        bool closeSuccess = Audio::MCISendString(L"close " + wstring(mciAudio->ShortPathName));
        delete mciAudio;
        return closeSuccess;
    }

    EXPORT_FUNC_EX(bool) MinPlayMCIAudio(_IN_ MCIAudio* mciAudio, bool repeat, bool wait)
    {
        return MinPlayMCIAudioEx(mciAudio, repeat, wait, 0, mciAudio->TotalMilliSecond);
    }

    EXPORT_FUNC_EX(bool) MinPlayMCIAudioEx(_IN_ MCIAudio* mciAudio, bool repeat, bool wait, int from, int to)
    {
        wstring cmd = _T("play ") + wstring(mciAudio->ShortPathName);

        //from x ms to y ms
        cmd += L" from " + to_wstring(from) + L" to " + to_wstring(to);

        //NOTICE:if play .wav music, repeat is useless.
        //if file is .wav and repeat is on, it will fail.
        //seems it's a bug in MCI.
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
        return Audio::MCISendString(L"stop " + wstring(mciAudio->ShortPathName));
    }

    EXPORT_FUNC_EX(bool) MinPauseMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        bool pause_suc = Audio::MCISendString(L"pause " + wstring(mciAudio->ShortPathName));
        return pause_suc;
    }

    EXPORT_FUNC_EX(bool) MinResumeMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        bool resume_suc = Audio::MCISendString(L"resume " + wstring(mciAudio->ShortPathName));
        return resume_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioVolume(_IN_ MCIAudio* mciAudio)
    {
        //get the volume of this audio(you should open audio before call this)
        wstring volume = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->ShortPathName) + _T(" volume"));
        return ::_wtoi(volume.c_str());
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioVolume(_IN_ MCIAudio* mciAudio, int volume)
    {
        bool set_volume_suc = Audio::MCISendString(_T("setaudio ") + wstring(mciAudio->ShortPathName) + _T(" volume to ") + to_wstring(volume));
        return set_volume_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioPosition(_IN_ MCIAudio* mciAudio)
    {
        wstring position = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->ShortPathName) + _T(" position"));
        int pos = ::_wtoi(position.c_str());
        return pos;
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioPosition(_IN_ MCIAudio* mciAudio, int position)
    {
        bool seek_suc = Audio::MCISendString(_T("seek ") + wstring(mciAudio->ShortPathName) + _T(" to ") + to_wstring(position));
        return seek_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioSpeed(_IN_ MCIAudio* mciAudio)
    {
        wstring speed = Audio::MCISendStringEx(L"status " + wstring(mciAudio->ShortPathName) + L" speed");
        return ::_wtoi(speed.c_str());
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioSpeed(_IN_ MCIAudio* mciAudio, int speed)
    {
        bool set_speed_suc = Audio::MCISendString(L"set " + wstring(mciAudio->ShortPathName) + L" speed " + to_wstring(speed));
        return set_speed_suc;
    }

    EXPORT_FUNC_EX(MCIAudioMode) MinGetMCIAudioMode(_IN_ MCIAudio* mciAudio)
    {
        wstring mode = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->ShortPathName) + _T(" mode"));
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

    Audio::Audio(const wstring& path, int defaultVolume)
    {
        this->path = path;
        this->shortPathName = File::ToShortPathName(path);
        this->extension = File::GetFileExtension(path);
        this->paused = !MCISendString(_T("open ") + this->shortPathName);

        SetVolume(defaultVolume);

        //get the length of the audio
        wstring result = MCISendStringEx(_T("status ") + this->shortPathName + _T(" length"));

        int totalMilliSecond = ::_wtoi(result.c_str());

        this->minute = (int)(totalMilliSecond / 1000 / 60);
        this->second = totalMilliSecond / 1000 - this->minute * 60;
        this->milliSecond = totalMilliSecond % 1000;
    }

    Audio::~Audio()
    {
        MCISendString(_T("close ") + this->shortPathName);
    }

    bool Audio::Play(bool repeat)
    {
        wstring cmd;
        if (repeat)
        {
            //NOTICE:if play .wav music, repeat is useless.
            //if file is .wav and repeat is on, it will fail.
            //seems it's a bug in MCI.
            if (String::CompareIgnoreCase(L".wav", this->extension))
            {
                cmd = _T("play ") + this->shortPathName;
            }
            else
            {
                cmd = _T("play ") + this->shortPathName + _T(" repeat");
            }
        }
        else
        {
            cmd = _T("play ") + this->shortPathName;
        }
        this->paused = !MCISendString(cmd);
        return !this->paused;
    }

    void Audio::Pause()
    {
        this->paused = MCISendString(_T("pause ") + this->shortPathName);
    }

    int Audio::GetVolume()
    {
        return this->volume;
    }

    void Audio::SetVolume(int volume)
    {
        bool suc = MCISendString(_T("setaudio ") + this->shortPathName + _T(" volume to ") + to_wstring(volume));

        if (suc)
        {
            this->volume = volume;
        }
    }

    int Audio::GetPosition()
    {
        wstring r = MCISendStringEx(_T("status ") + this->shortPathName + _T(" position"));

        int pos = ::_wtoi(r.c_str());
        return pos;
    }

    void Audio::SetPosition(int milliSecond)
    {
        MCISendString(_T("seek ") + this->shortPathName + _T(" to ") + to_wstring(milliSecond));
    }

    wstring Audio::GetMode()
    {
        return MCISendStringEx(_T("status ") + this->shortPathName + _T(" mode"));
    }
}