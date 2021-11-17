#pragma once

#include "MinDefines.hpp"
#include "Audio.hpp"
#include <string>
#include <vector>

namespace MinConsoleNative
{
    typedef void (*AudioPoolLoadingCallback)(int index);

    class AudioPool
    {
    private:
        bool loadSuccess = false;

    public:
        std::wstring path;
        std::vector<Audio*> readyAudios;
        std::vector<Audio*> playingAudios;

        AudioPool(const std::wstring& path, int allocCount);

        AudioPool(const std::wstring& path, int allocCount, AudioPoolLoadingCallback loadingCallback);

        ~AudioPool();

        bool Success();

        //volumeScale[0, 1]
        bool PlayOneShot(double volumeScale = 1.0);

        void Clean();
    };
}