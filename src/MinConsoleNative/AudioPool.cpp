#include "AudioPool.hpp"

namespace MinConsoleNative
{
    AudioPool::AudioPool(const std::wstring& path, int allocCount)
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

    AudioPool::AudioPool(const std::wstring& path, int allocCount, AudioPoolLoadingCallback loadingCallback)
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

    AudioPool::~AudioPool()
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
    bool AudioPool::PlayOneShot(double volumeScale)
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

    void AudioPool::Clean()
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
}