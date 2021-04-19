#pragma once

#include "MinDefines.h"
#include <string>
#include <vector>

//SEE:https://docs.microsoft.com/en-us/windows/win32/multimedia/mci

namespace MinConsoleNative
{
    static int LastMCIResult = 0;
    static std::wstring MCIAlias = L"MIN_MCI_ALIAS_";
    static int MCIAliasIncrement = 1;

    EXPORT_CONSTEXPR int MCI_MIN_VOLUME = 0;
    EXPORT_CONSTEXPR int MCI_MAX_VOLUME = 1000;

    EXPORT_CONSTEXPR int MCI_SLOW_SPEED = 500;
    EXPORT_CONSTEXPR int MCI_NORMAL_SPEED = 1000;
    EXPORT_CONSTEXPR int MCI_FAST_SPEED = 2000;

    EXPORT_ENUM_CLASS MCIAudioMode
    {
        Unknown = 0,
        NotReady = 1,   //even I dont know when will return this value
        Paused = 2,     //paused
        Playing = 3,    //is playing
        Stopped = 4,    //when audio is not opened or finished.
    };

    EXPORT_STRUCT MCIAudio
    {
    public:
        EXPORT_STRUCT_MEMBER wchar Path[MAX_PATH];  //Absolute path
        EXPORT_STRUCT_MEMBER wchar Extension[32];   //File extension
        EXPORT_STRUCT_MEMBER wchar Alias[32];       //Similar to a unique ID

        EXPORT_STRUCT_MEMBER int TotalMilliSecond;  //total milliSecond of this audio
        EXPORT_STRUCT_MEMBER int Minute;            //minute part of this audio
        EXPORT_STRUCT_MEMBER int Second;            //second part of this audio
        EXPORT_STRUCT_MEMBER int MilliSecond;       //milliSecond part of this audio
    };

    EXPORT_FUNC_EX(bool) MinMCISendString(_IN_ const wchar* str);

    EXPORT_FUNC_EX(bool) MinMCISendStringEx(_IN_ const wchar* str, _OUT_ wchar* returnStr, int returnStrLen);

    EXPORT_FUNC_EX(bool) MinMCIGetErrorString(_OUT_ wchar* errStr, int errStrLen);

    //This method is very simple and only supports playing .wav files
    EXPORT_FUNC_EX(bool) MinPlaySound(_IN_ const wchar* path, bool repeatPlay);

    extern std::vector<MCIAudio*> shots;

    //volumeScale[0, 1]
    EXPORT_FUNC_EX(bool) MinPlayOneShot(_IN_ const wchar* path, double volumeScale);

    //call this to remove and delete audios that has finished playing.
    EXPORT_FUNC_EX(void) MinCleanShots();

    //-------------------------------MCIAudio functions---------------------------------

    EXPORT_FUNC_EX(bool) MinInitMCIAudio(_OUT_ MCIAudio* mciAudio, _IN_ const wchar* path);

    EXPORT_FUNC_EX(bool) MinDeinitMCIAudio(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinPlayMCIAudio(_IN_ MCIAudio* mciAudio, bool repeat, bool wait);

    EXPORT_FUNC_EX(bool) MinPlayMCIAudioEx(_IN_ MCIAudio* mciAudio, bool repeat, bool wait, int from, int to);

    //The stop command will stop playback and reset the current track position to zero.
    EXPORT_FUNC_EX(bool) MinStopMCIAudio(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinPauseMCIAudio(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinResumeMCIAudio(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(int) MinGetMCIAudioVolume(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinSetMCIAudioVolume(_IN_ MCIAudio* mciAudio, int volume);

    EXPORT_FUNC_EX(int) MinGetMCIAudioPosition(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinSetMCIAudioPosition(_IN_ MCIAudio* mciAudio, int position);

    EXPORT_FUNC_EX(int) MinGetMCIAudioSpeed(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinSetMCIAudioSpeed(_IN_ MCIAudio* mciAudio, int speed);

    EXPORT_FUNC_EX(MCIAudioMode) MinGetMCIAudioMode(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsPlaying(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOver(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOverEx(_IN_ MCIAudio* mciAudio, int length);

    class Audio
    {
    public:
        static bool MCISendString(const std::wstring& cmd);

        static std::wstring MCISendStringEx(const std::wstring& cmd);

    public:
        Audio(const std::wstring& path, int defaultVolume = 1000);

        ~Audio();

        //play audio(.mp3, .wav etc) this function wont block the main thread.
        //NOTICE:if play .wav music, repeat is useless.
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
        std::wstring extension;
        bool paused;

        int minute;         //minute part of this audio
        int second;         //second part of this audio
        int milliSecond;    //milliSecond part of this audio
    private:
        int volume;
    };
}