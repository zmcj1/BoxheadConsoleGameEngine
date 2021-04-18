#pragma once

#include "MinDefines.h"
#include <string>

//SEE:https://docs.microsoft.com/en-us/windows/win32/multimedia/mci

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinMCISendString(_IN_ const wchar* str);

    EXPORT_FUNC_EX(bool) MinMCISendStringEx(_IN_ const wchar* str, _OUT_ wchar* returnStr, int returnStrLen);

    //This method is very simple and only supports playing .wav files
    EXPORT_FUNC_EX(bool) MinPlaySound(_IN_ const wchar* path, bool repeatPlay);

    class Audio
    {
    public:
        static const int MIN_VOLUME = 0;

        static const int MAX_VOLUME = 1000;

        static bool MCISendString(const std::wstring& cmd);

        static std::wstring MCISendStringEx(const std::wstring& cmd);

    public:
        Audio(const std::wstring& path, int defaultVolume = MAX_VOLUME);

        ~Audio();

        //play audio(.mp3, .wav etc) this function wont block the main thread.
        //NOTICE:if play .wav music, you should not repeat.
        bool Play(bool repeat = false);

        void Pause();

        //set volume [0-1000]
        int GetVolume();

        //set volume [0-1000]
        void SetVolume(int volume);

        //get audio current position (in milliSecond)
        int GetPosition();

        //seek to (in milliSecond) after calling this API, you need to use Play to start playing audio.
        void SetPosition(int milliSecond);

        //get status return(playing paused stopped)
        std::wstring GetMode();

        std::wstring path;
        std::wstring shortPathName;
        bool paused;

        int minute;         //minute part of this audio
        int second;         //second part of this audio
        int milliSecond;    //milliSecond part of this audio
    private:
        int volume;
    };
}