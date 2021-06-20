#include "TcpListener.h"

namespace MinConsoleNative
{
    TcpListener::TcpListener()
    {
        this->server = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (this->server < 0)
        {
            throw TcpListenerException::WrongInitialization;
        }


    }

    TcpListener::~TcpListener()
    {
        ::closesocket(this->server);
    }
}