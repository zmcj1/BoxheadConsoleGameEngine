#pragma once

#include "MinDefines.h"
#include <vector>
#include <string>

//Audio support is developed based on Windows MCI
//SEE:https://docs.microsoft.com/en-us/windows/win32/multimedia/mci

namespace MinConsoleNative
{
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

    //---------------------------------static functions---------------------------------

    EXPORT_FUNC_EX(bool) MinMCISendString(_IN_ const wchar* str);

    EXPORT_FUNC_EX(bool) MinMCISendStringEx(_IN_ const wchar* str, _OUT_ wchar** returnStr);

    //if no error, return L""
    EXPORT_FUNC_EX(wchar*) MinMCIGetErrorString();

    //This method is very simple and only supports playing .wav files
    EXPORT_FUNC_EX(bool) MinPlaySound(_IN_ const wchar* path, bool repeatPlay);

    //---------------------------------MCIAudio functions---------------------------------

    EXPORT_FUNC_EX(MCIAudio*) MinInitMCIAudio(_IN_ const wchar* path);

    EXPORT_FUNC_EX(void) MinDeinitMCIAudio(_IN_ MCIAudio* mciAudio);

    //play audio(.mp3, .wav etc) this function wont block the main thread.
    //NOTICE:if play .wav music, repeat is useless.
    EXPORT_FUNC_EX(bool) MinPlayMCIAudio(_IN_ MCIAudio* mciAudio, bool repeat, bool wait);

    //play audio(.mp3, .wav etc) this function wont block the main thread.
    //NOTICE:if play .wav music, repeat is useless.
    EXPORT_FUNC_EX(bool) MinPlayMCIAudioEx(_IN_ MCIAudio* mciAudio, bool repeat, bool wait, int from, int to);

    //The stop command will stop playback and reset the current track position to zero.
    EXPORT_FUNC_EX(bool) MinStopMCIAudio(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinPauseMCIAudio(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinResumeMCIAudio(_IN_ MCIAudio* mciAudio);

    //volume [0-1000]
    EXPORT_FUNC_EX(int) MinGetMCIAudioVolume(_IN_ MCIAudio* mciAudio);

    //volume [0-1000]
    EXPORT_FUNC_EX(bool) MinSetMCIAudioVolume(_IN_ MCIAudio* mciAudio, int volume);

    //get audio current position (in milliSecond)
    EXPORT_FUNC_EX(int) MinGetMCIAudioPosition(_IN_ MCIAudio* mciAudio);

    //seek to (in milliSecond) after calling this API, you need to use Play to start playing audio.
    EXPORT_FUNC_EX(bool) MinSetMCIAudioPosition(_IN_ MCIAudio* mciAudio, int position);

    //standard speed(1000)
    EXPORT_FUNC_EX(int) MinGetMCIAudioSpeed(_IN_ MCIAudio* mciAudio);

    //standard speed(1000)
    EXPORT_FUNC_EX(bool) MinSetMCIAudioSpeed(_IN_ MCIAudio* mciAudio, int speed);

    EXPORT_FUNC_EX(MCIAudioMode) MinGetMCIAudioMode(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsPlaying(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOver(_IN_ MCIAudio* mciAudio);

    EXPORT_FUNC_EX(bool) MinGetMCIAudioIsOverEx(_IN_ MCIAudio* mciAudio, int length);

    //---------------------------------Audio class---------------------------------

    class Audio
    {
    public:
        static bool MCISendString(const std::wstring& cmd);

        static std::wstring MCISendStringEx(const std::wstring& cmd);

        //if no error, return L""
        static std::wstring MCIGetErrorString();

        static bool PlaySoundW(const std::wstring& path, bool repeatPlay);

    private:
        MCIAudio* mciAudio = nullptr;

    public:
        //Initialized successfully
        inline bool Success()
        {
            return this->mciAudio != nullptr;
        }

        //Absolute path
        inline std::wstring Path()
        {
            return std::wstring(mciAudio->Path);
        }

        //File extension
        inline std::wstring Extension()
        {
            return std::wstring(mciAudio->Extension);
        }

        //Similar to a unique ID
        inline std::wstring Alias()
        {
            return std::wstring(mciAudio->Alias);
        }

        //total milliSecond of this audio
        inline int TotalMilliSecond()
        {
            return mciAudio->TotalMilliSecond;
        }

        //minute part of this audio
        inline int Minute()
        {
            return mciAudio->Minute;
        }

        //second part of this audio
        inline int Second()
        {
            return mciAudio->Second;
        }

        //milliSecond part of this audio
        inline int MilliSecond()
        {
            return mciAudio->Second;
        }

    public:
        Audio(const std::wstring& path);

        ~Audio();

        bool Play(bool repeat = false, bool wait = false);

        bool PlayEx(bool repeat, bool wait, int from, int to);

        bool Stop();

        bool Pause();

        bool Resume();

        int GetVolume();

        bool SetVolume(int volume);

        int GetPosition();

        bool SetPosition(int position);

        int GetSpeed();

        bool SetSpeed(int speed);

        MCIAudioMode GetMode();

        bool IsPlaying();

        bool IsOver();

        bool IsOverEx(int length);
    };

    //---------------------------------AudioPool---------------------------------

    typedef void (*AudioPoolLoadingCallback)(int index);

    class AudioPool
    {
    public:
        std::wstring path;
        std::vector<Audio*> readyAudios;
        std::vector<Audio*> playingAudios;

        AudioPool(const std::wstring& path, int allocCount)
        {
            this->path = path;
            for (size_t i = 0; i < allocCount; i++)
            {
                Audio* audio_ptr = new Audio(path);
                if (audio_ptr->Success())
                {
                    readyAudios.push_back(audio_ptr);
                }
            }
        }

        AudioPool(const std::wstring& path, int allocCount, AudioPoolLoadingCallback loadingCallback)
        {
            this->path = path;
            for (size_t i = 0; i < allocCount; i++)
            {
                Audio* audio_ptr = new Audio(path);
                if (audio_ptr->Success())
                {
                    readyAudios.push_back(audio_ptr);
                    if (loadingCallback != nullptr)
                    {
                        loadingCallback(i);
                    }
                }
            }
        }

        ~AudioPool()
        {
            //clean both of them.
            for (size_t i = 0; i < readyAudios.size(); i++)
            {
                Audio* audio_ptr = readyAudios[i];
                delete audio_ptr;
            }
            for (size_t i = 0; i < playingAudios.size(); i++)
            {
                Audio* audio_ptr = playingAudios[i];
                delete audio_ptr;
            }
        }

        //volumeScale[0, 1]
        bool PlayOneShot(double volumeScale = 1.0)
        {
            Audio* audio_ptr = nullptr;
            if (!readyAudios.empty())
            {
                audio_ptr = readyAudios.back();
                readyAudios.pop_back();
            }
            else
            {
                audio_ptr = new Audio(this->path);
            }

            audio_ptr->SetVolume(volumeScale * 1000);
            audio_ptr->Play();
            playingAudios.push_back(audio_ptr);

            return true;
        }

        void Clean()
        {
            //check playing audios
            for (size_t i = 0; i < playingAudios.size(); i++)
            {
                Audio* audio_ptr = playingAudios[i];
                if (audio_ptr->IsOver())
                {
                    //reset
                    audio_ptr->SetPosition(0);
                    //add to ready
                    readyAudios.push_back(audio_ptr);
                    //remove from playing
                    playingAudios.erase(playingAudios.begin() + i);
                    i--;
                }
            }
        }
    };
}