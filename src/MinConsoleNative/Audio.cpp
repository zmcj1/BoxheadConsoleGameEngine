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
        return mci_result == 0;
    }

    EXPORT_FUNC_EX(bool) MinMCISendStringEx(_IN_ const wchar* str, _OUT_ wchar* returnStr, int returnStrLen)
    {
        MCIERROR mci_result = ::mciSendString(str, returnStr, returnStrLen, nullptr);
        return mci_result == 0;
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