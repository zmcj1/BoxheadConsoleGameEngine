#pragma once

#include "WinNetwork.h"

namespace MinConsoleNative
{
    enum class TcpListenerException
    {
        WrongInitialization = 1,
    };

    class TcpListener
    {
    private:
        SOCKET server;

    public:
        TcpListener();

        ~TcpListener();
    };
}