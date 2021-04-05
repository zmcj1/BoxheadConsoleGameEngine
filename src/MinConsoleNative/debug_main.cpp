#ifdef _DEBUG

#include "MinConsoleNative.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    Window window;
    POINT pos = window.GetCenterPosOfWindowInDesktop();
    window.SetWindowPos(pos);

    bool legacyCon = ConRegistry::IsUsingLegacyConsole();
    cout << legacyCon;
    cin.get();
    return 0;
}

#endif