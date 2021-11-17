#pragma once

#include "MinDefines.hpp"
#include "Audio.hpp" //Audio
#include <string>
#include <vector>

namespace MinConsoleNative
{
    class AudioPool
    {
    private:
        bool success = false;

    public:
        std::wstring path;
        std::vector<Audio*> readyAudios;
        std::vector<Audio*> playingAudios;

        AudioPool(const std::wstring& path, int allocCount = 10);

        ~AudioPool();

        bool Success();

        //volumeScale[0, 1]
        bool PlayOneShot(double volumeScale = 1.0);

        void Clean();
    };
}