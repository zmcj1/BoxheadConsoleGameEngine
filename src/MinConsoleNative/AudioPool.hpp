#pragma once

#include "MinDefines.hpp"
#include "Audio.hpp" //Audio
#include <string>
#include <vector>

//原计划使用多线程技术提升AudioPool的效率
//但是因为MCI的限制(如果想在多线程中使用mciSendString播放音乐，你必须保证所有的mciSendString方法调用都在一个线程中进行)
//因此暂时放弃使用多线程操作MCI
//参考:https://blog.csdn.net/daeba/article/details/43229115?spm=1001.2014.3001.5502

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