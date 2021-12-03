#include "MinConsoleNative.hpp"

int main()
{
    Timer t;
    t.Start();

    t.Stop();
    console.WriteLine(std::to_wstring(t.Time()));

    AudioPool audio(L"../../res/562_Weapon.UZI.Fire.mp3");

    t.Stop();
    console.WriteLine(std::to_wstring(t.Time()));

    while (true)
    {
        if (Input::GetKey('A'))
        {
            if (audio.PlayOneShot())
            {
                console.Write(std::to_wstring(audio.playingAudios.size()));
                console.Write(L" ");
                console.WriteLine(std::to_wstring(audio.readyAudios.size()));
            }
            else
            {
                console.WriteLine(L"f");
            }
        }

        audio.Clean();
        Sleep(50);
    }

    return 0;
}