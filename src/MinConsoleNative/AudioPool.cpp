#include "AudioPool.hpp"

using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(AudioPool*) MinCreatAudioPool(_IN_ const wchar* path, int allocCount)
    {
        AudioPool* audioPool = new AudioPool(path, allocCount);

        if (audioPool->Success())
        {
            return audioPool;
        }
        else
        {
            return nullptr;
        }
    }

    EXPORT_FUNC_EX(void) MinDestroyAudioPool(_IN_ void* audioPool)
    {
        if (audioPool == nullptr) return;

        delete audioPool;
    }

    EXPORT_FUNC_EX(bool) MinPlayOneShot(_IN_ void* audioPool, double volumeScale)
    {
        if (audioPool == nullptr) return false;

        AudioPool* realAudioPool = (AudioPool*)audioPool;

        return realAudioPool->PlayOneShot(volumeScale);
    }

    EXPORT_FUNC_EX(void) MinCleanAudioPool(_IN_ void* audioPool)
    {
        if (audioPool == nullptr) return;

        AudioPool* realAudioPool = (AudioPool*)audioPool;

        realAudioPool->Clean();
    }

    AudioPool::AudioPool(const std::wstring& path, int allocCount)
    {
        this->path = path;
        this->success = Audio(path).Success();

        if (this->success)
        {
            for (size_t i = 0; i < allocCount; i++)
            {
                Audio* audio_ptr = new Audio(path);
                if (audio_ptr->Success())
                {
                    readyAudios.push_back(audio_ptr);
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

    bool AudioPool::Success()
    {
        return this->success;
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

        if (audio_ptr->Success())
        {
            audio_ptr->SetVolume(volumeScale * 1000);
            bool playSuccess = audio_ptr->Play();
            if (playSuccess)
            {
                playingAudios.push_back(audio_ptr);
            }
            return playSuccess;
        }
        else
        {
            delete audio_ptr;
            return false;
        }
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