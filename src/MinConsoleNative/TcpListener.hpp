#pragma once

#include "WinNetwork.hpp"

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