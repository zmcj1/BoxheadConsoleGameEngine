#include "MinConsoleNative.hpp"

int main()
{
    Timer t;
    t.Start();

    t.Stop();
    console.WriteLine(std::to_wstring(t.Time()));

    AudioPool audio(L"C:\\Users\\16692\\source\\repos\\MinConsole\\res\\562_Weapon.UZI.Fire.mp3");
    if (!audio.Success()) return -1;

    t.Stop();
    console.WriteLine(std::to_wstring(t.Time()));

    while (true)
    {
        if (Input::GetKey('A'))
        {
            console.WriteLine(std::to_wstring(audio.playingAudios.size()));
            audio.PlayOneShot();
        }

        audio.Clean();
        Sleep(50);
    }

    return 0;
}