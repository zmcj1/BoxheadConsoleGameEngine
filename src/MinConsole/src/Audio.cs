using System;
using System.Runtime.InteropServices;

using static MinConsole.MinConsoleNativeFuncs;
using static MinConsole.MinConsoleNativeStructs;

namespace MinConsole
{
    public class Audio
    {
        private MCIAudio mciAudio;
        private IntPtr mciAudioPtr = IntPtr.Zero;

        //Initialized successfully
        public bool Success => mciAudioPtr != IntPtr.Zero;

        //Absolute path
        public string Path => mciAudio.Path;

        //File extension
        public string Extension => mciAudio.Extension;

        //Similar to a unique ID
        public string Alias => mciAudio.Alias;

        //total milliSecond of this audio
        public int TotalMilliSecond => mciAudio.TotalMilliSecond;

        //minute part of this audio
        public int Minute => mciAudio.Minute;

        //second part of this audio
        public int Second => mciAudio.Second;

        //milliSecond part of this audio
        public int MilliSecond => mciAudio.Second;

        public Audio(string path)
        {
            mciAudioPtr = MinInitMCIAudio(path);
            //如果没有初始化失败才进行转换
            if (mciAudioPtr != IntPtr.Zero)
            {
                mciAudio = Marshal.PtrToStructure<MCIAudio>(mciAudioPtr);
            }
        }

        ~Audio()
        {
            //如果没有初始化失败才进行回收
            if (mciAudioPtr != IntPtr.Zero)
            {
                MinDeinitMCIAudio(ref mciAudio);
            }
        }

        public bool Play(bool repeat, bool wait)
        {
            return MinPlayMCIAudio(ref mciAudio, repeat, wait);
        }

        public bool PlayEx(bool repeat, bool wait, int from, int to)
        {
            return MinPlayMCIAudioEx(ref mciAudio, repeat, wait, from, to);
        }

        public bool Stop()
        {
            return MinStopMCIAudio(ref mciAudio);
        }

        public bool Pause()
        {
            return MinPauseMCIAudio(ref mciAudio);
        }

        public bool Resume()
        {
            return MinResumeMCIAudio(ref mciAudio);
        }

        public int GetVolume()
        {
            return MinGetMCIAudioVolume(ref mciAudio);
        }

        public bool SetVolume(int volume)
        {
            return MinSetMCIAudioVolume(ref mciAudio, volume);
        }

        public int GetPosition()
        {
            return MinGetMCIAudioPosition(ref mciAudio);
        }

        public bool SetPosition(int position)
        {
            return MinSetMCIAudioPosition(ref mciAudio, position);
        }

        public int GetSpeed()
        {
            return MinGetMCIAudioSpeed(ref mciAudio);
        }

        public bool SetSpeed(int speed)
        {
            return MinSetMCIAudioSpeed(ref mciAudio, speed);
        }

        public MCIAudioMode GetMode()
        {
            return MinGetMCIAudioMode(ref mciAudio);
        }

        public bool IsPlaying()
        {
            return MinGetMCIAudioIsPlaying(ref mciAudio);
        }

        public bool IsOver()
        {
            return MinGetMCIAudioIsOver(ref mciAudio);
        }

        public bool IsOverEx(int length)
        {
            return MinGetMCIAudioIsOverEx(ref mciAudio, length);
        }
    }
}