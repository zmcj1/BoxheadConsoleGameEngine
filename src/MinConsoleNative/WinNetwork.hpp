#pragma once

#include "MinDefines.hpp"
#include <WinSock2.h>

//See Docs:https://docs.microsoft.com/zh-cn/windows/win32/winsock/windows-sockets-start-page-2

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinInitWinSocket();

    EXPORT_FUNC_EX(bool) MinReleaseWinSocket();
}