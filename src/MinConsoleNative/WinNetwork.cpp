#include "WinNetwork.h"

#pragma comment(lib, "ws2_32.lib")

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinInitWinSocket()
    {
        WSADATA data;
        int r = WSAStartup(MAKEWORD(2, 2), &data);
        return r == 0;
    }

    EXPORT_FUNC_EX(bool) MinReleaseWinSocket()
    {
        return WSACleanup() == 0;
    }
}