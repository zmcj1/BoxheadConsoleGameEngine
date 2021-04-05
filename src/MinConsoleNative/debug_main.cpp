#ifdef _DEBUG

#include "MinConsoleNative.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    Window window;
    //window.SetWindowMenuVisibility(false);
    POINT pos = window.GetCenterPosOfWindowInDesktop();
    window.SetWindowPos(pos);

    bool legacyCon = ConRegistry::IsUseLegacyConsole();
    cout << legacyCon;
    cin.get();
    return 0;
}

#endif