#include "Audio.h"
#include "File.h"
//Provide MCI interface, mmsystem header file depends on Windows.h
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

namespace MinConsoleNative
{
    static int LastMCIResult = 0;
    static const std::wstring MCIAlias = L"MIN_MCI_ALIAS_";
    static int MCIAliasIncrement = 1;

    EXPORT_FUNC_EX(void) MinStructTest(_OUT_ MCIAudio* s)
    {
        wstring path = L"nihao";
        ::wcscpy_s(s->Path, path.size() + 1, path.c_str());
    }

    EXPORT_FUNC_EX(HANDLE) MinStructTest2()
    {
        MCIAudio* s = ExternAlloc<MCIAudio>(1); //.net style alloc
        ::ZeroMemory(s, sizeof(MCIAudio));      //need to zero memory.

        wstring path = L"nihao";
        ::wcscpy_s(s->Path, path.size() + 1, path.c_str());

        return s;
    }

    EXPORT_FUNC_EX(MCIAudio) MinStructTest3()
    {
        MCIAudio s = { 0 };

        wstring path = L"nihao";
        ::wcscpy_s(s.Path, path.size() + 1, path.c_str());

        return s;
    }

    EXPORT_FUNC_EX(bool) MinMCISendString(_IN_ const wchar* str)
    {
        MCIERROR mci_result = ::mciSendString(str, nullptr, 0, nullptr);
        LastMCIResult = mci_result;
        return mci_result == 0;
    }

    EXPORT_FUNC_EX(bool) MinMCISendStringEx(_IN_ const wchar* str, _OUT_ wchar** returnStr)
    {
        *returnStr = ExternAlloc<wchar>(MAX_PATH);
        MCIERROR mci_result = ::mciSendString(str, *returnStr, MAX_PATH, nullptr);
        LastMCIResult = mci_result;
        return mci_result == 0;
    }

    EXPORT_FUNC_EX(wchar*) MinMCIGetErrorString()
    {
        wchar* wstr = ExternAlloc<wchar>(MAX_PATH);

        if (LastMCIResult == 0) //no error, all is ok.
        {
            ::ZeroMemory(wstr, MAX_PATH);
        }
        else
        {
            bool suc = ::mciGetErrorString(LastMCIResult, wstr, MAX_PATH);
        }

        return wstr;
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

    EXPORT_FUNC_EX(MCIAudio*) MinInitMCIAudio(_IN_ const wchar* path)
    {
        MCIAudio* mciAudio = ExternAlloc<MCIAudio>(1);

        //open the audio with alias.(should close audio when you dont use it.)
        wstring shortPathName = File::ToShortPathName(path);
        wstring alias = MCIAlias + ::to_wstring(MCIAliasIncrement++);
        bool openSuccess = Audio::MCISendString(_T("open ") + shortPathName + L" alias " + alias);
        //如果打开文件失败直接释放指针并且返回空指针
        if (!openSuccess)
        {
            ExternFree(mciAudio);
            return nullptr;
        }

        wstring extension = File::GetFileExtension(path);
        ::wcscpy_s(mciAudio->Path, ::wcslen(path) + 1, path);
        ::wcscpy_s(mciAudio->Extension, ::wcslen(extension.c_str()) + 1, extension.c_str());
        ::wcscpy_s(mciAudio->Alias, ::wcslen(alias.c_str()) + 1, alias.c_str());

        //get the length of the audio(you can directly use this cmd without open operation)
        wstring length = Audio::MCISendStringEx(_T("status ") + alias + _T(" length"));
        mciAudio->TotalMilliSecond = ::_wtoi(length.c_str());
        mciAudio->Minute = (int)(mciAudio->TotalMilliSecond / 1000 / 60);
        mciAudio->Second = mciAudio->TotalMilliSecond / 1000 - mciAudio->Minute * 60;
        mciAudio->MilliSecond = mciAudio->TotalMilliSecond % 1000;

        return mciAudio;
    }

    EXPORT_FUNC_EX(void) MinDeinitMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return;

        bool closeSuccess = Audio::MCISendString(L"close " + wstring(mciAudio->Alias));
        ExternFree(mciAudio);
    }

    EXPORT_FUNC_EX(bool) MinPlayMCIAudio(_IN_ MCIAudio* mciAudio, bool repeat, bool wait)
    {
        if (mciAudio == nullptr) return false;

        return MinPlayMCIAudioEx(mciAudio, repeat, wait, 0, mciAudio->TotalMilliSecond);
    }

    EXPORT_FUNC_EX(bool) MinPlayMCIAudioEx(_IN_ MCIAudio* mciAudio, bool repeat, bool wait, int from, int to)
    {
        if (mciAudio == nullptr) return false;

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
        if (mciAudio == nullptr) return false;

        return Audio::MCISendString(L"stop " + wstring(mciAudio->Alias));
    }

    EXPORT_FUNC_EX(bool) MinPauseMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return false;

        bool pause_suc = Audio::MCISendString(L"pause " + wstring(mciAudio->Alias));
        return pause_suc;
    }

    EXPORT_FUNC_EX(bool) MinResumeMCIAudio(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return false;

        bool resume_suc = Audio::MCISendString(L"resume " + wstring(mciAudio->Alias));
        return resume_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioVolume(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return 0;

        //get the volume of this audio(you should open audio before call this)
        wstring volume = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->Alias) + _T(" volume"));
        return ::_wtoi(volume.c_str());
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioVolume(_IN_ MCIAudio* mciAudio, int volume)
    {
        if (mciAudio == nullptr) return false;

        bool set_volume_suc = Audio::MCISendString(_T("setaudio ") + wstring(mciAudio->Alias) + _T(" volume to ") + to_wstring(volume));
        return set_volume_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioPosition(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return 0;

        wstring position = Audio::MCISendStringEx(_T("status ") + wstring(mciAudio->Alias) + _T(" position"));
        int pos = ::_wtoi(position.c_str());
        return pos;
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioPosition(_IN_ MCIAudio* mciAudio, int position)
    {
        if (mciAudio == nullptr) return false;

        bool seek_suc = Audio::MCISendString(_T("seek ") + wstring(mciAudio->Alias) + _T(" to ") + to_wstring(position));
        return seek_suc;
    }

    EXPORT_FUNC_EX(int) MinGetMCIAudioSpeed(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return 0;

        wstring speed = Audio::MCISendStringEx(L"status " + wstring(mciAudio->Alias) + L" speed");
        return ::_wtoi(speed.c_str());
    }

    EXPORT_FUNC_EX(bool) MinSetMCIAudioSpeed(_IN_ MCIAudio* mciAudio, int speed)
    {
        if (mciAudio == nullptr) return false;

        bool set_speed_suc = Audio::MCISendString(L"set " + wstring(mciAudio->Alias) + L" speed " + to_wstring(speed));
        return set_speed_suc;
    }

    EXPORT_FUNC_EX(MCIAudioMode) MinGetMCIAudioMode(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return MCIAudioMode::Unknown;

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
        if (mciAudio == nullptr) return false;

        MCIAudioMode audioMode = MinGetMCIAudioMode(mciAudio);
        return audioMode == MCIAudioMode::Playing;
    }

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOver(_IN_ MCIAudio* mciAudio)
    {
        if (mciAudio == nullptr) return false;

        return MinGetMCIAudioIsOverEx(mciAudio, mciAudio->TotalMilliSecond);
    }

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOverEx(_IN_ MCIAudio* mciAudio, int length)
    {
        if (mciAudio == nullptr) return false;

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
        wchar* buf = nullptr;
        bool suc = MinMCISendStringEx(cmd.c_str(), &buf);
        wstring wstr = buf;
        ExternFree(buf);
        return wstr;
    }

    std::wstring Audio::MCIGetErrorString()
    {
        wchar* buf = MinMCIGetErrorString();
        wstring wstr = buf;
        ExternFree(buf);
        return wstr;
    }

    bool Audio::PlaySoundW(const std::wstring& path, bool repeatPlay)
    {
        return MinPlaySound(path.c_str(), repeatPlay);
    }

    Audio::Audio(const wstring& path)
    {
        this->mciAudio = MinInitMCIAudio(path.c_str());
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