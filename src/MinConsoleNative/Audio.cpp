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

    EXPORT_FUNC_EX(bool) MinMCISendString2(_IN_ const wchar* str, _OUT_ wchar* returnStr, int returnStrLen)
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

    wstring Audio::MCISendString2(const wstring& cmd)
    {
        wchar res[MAX_PATH] = { 0 };
        MinMCISendString2(cmd.c_str(), res, MAX_PATH);
        wstring result(res);
        return result;
    }

    Audio::Audio(const wstring& path, int defaultVolume)
    {
        this->path = path;
        this->short_path_name = File::ToShortPathName(path);

        this->paused = !MCISendString(_T("open ") + this->short_path_name);

        SetVolume(defaultVolume);

        //get the length of the audio
        wstring result = MCISendString2(_T("status ") + this->short_path_name + _T(" length"));

        int totalMilliSecond = ::_wtoi(result.c_str());

        this->minute = (int)(totalMilliSecond / 1000 / 60);
        this->second = totalMilliSecond / 1000 - this->minute * 60;
        this->milliSecond = totalMilliSecond % 1000;
    }

    Audio::~Audio()
    {
        MCISendString(_T("close ") + this->short_path_name);
    }

    bool Audio::Play(bool repeat)
    {
        wstring cmd;
        if (repeat)
        {
            cmd = _T("play ") + this->short_path_name + _T(" repeat");
        }
        else
        {
            cmd = _T("play ") + this->short_path_name;
        }
        this->paused = !MCISendString(cmd);
        return !this->paused;
    }

    void Audio::Pause()
    {
        this->paused = MCISendString(_T("pause ") + this->short_path_name);
    }

    int Audio::GetVolume()
    {
        return this->volume;
    }

    void Audio::SetVolume(int volume)
    {
        bool suc = MCISendString(_T("setaudio ") + this->short_path_name + _T(" volume to ") + to_wstring(volume));

        if (suc)
        {
            this->volume = volume;
        }
    }

    int Audio::GetPosition()
    {
        wstring r = MCISendString2(_T("status ") + this->short_path_name + _T(" position"));

        int pos = _wtoi(r.c_str());
        return pos;
    }

    void Audio::SetPosition(int milliSecond)
    {
        MCISendString(_T("seek ") + this->short_path_name + _T(" to ") + to_wstring(milliSecond));
    }

    wstring Audio::GetMode()
    {
        return MCISendString2(_T("status ") + this->short_path_name + _T(" mode"));
    }
}