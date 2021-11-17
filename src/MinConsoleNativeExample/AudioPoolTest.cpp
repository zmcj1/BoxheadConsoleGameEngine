#include "MinConsoleNative.hpp"

int main()
{
    AudioPool audio(L"C:\\Users\\16692\\source\\repos\\MinConsole\\res\\562_Weapon.UZI.Fire.mp3", 10);
    if (!audio.Success()) return -1;

    while (true)
    {
        if (Input::GetKey('A'))
        {
            audio.PlayOneShot();
        }

        audio.Clean();
        Sleep(50);
    }

    return 0;
}