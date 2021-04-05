#ifdef _DEBUG

#include "MinDefines.h"
#include "UnusualMethods.h"
#include "Clipboard.h"
#include "WinVersion.h"
#include <iostream>
#include <string>
using namespace MinConsoleNative;
using namespace std;

int main()
{
    WinVersion wv;
    bool ss = wv.IsWindows10Version1809OrLater();

    cin.get();
    return 0;
}

#endif