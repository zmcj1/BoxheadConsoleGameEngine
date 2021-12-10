﻿#include <cstdint> //uint32_t, uint16_t, uint8_t
#include <memory>  //shared_ptr
#include <string>  //string/wstring

//Socket支持, 引用这些头文件必须要在include <Windows.h>之前
#include <WinSock2.h> //socket
#include <ws2tcpip.h> //InetPton
#pragma comment(lib, "ws2_32.lib") //linker

//#include <Windows.h>

class SocketAddress
{
public:
    SocketAddress(uint32_t address, uint16_t port)
    {
        ::memset(&socketAddress, 0, sizeof(sockaddr));

        GetAsSockAddrIn()->sin_family = AF_INET;
        GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(address);
        GetAsSockAddrIn()->sin_port = htons(port);
    }

    SocketAddress(const std::wstring& addressStr, uint16_t port)
    {
        ::memset(&socketAddress, 0, sizeof(sockaddr));

        GetAsSockAddrIn()->sin_family = AF_INET;
        ::InetPton(AF_INET, addressStr.c_str(), &GetAsSockAddrIn()->sin_addr);
        GetAsSockAddrIn()->sin_port = htons(port);
    }

    SocketAddress(const sockaddr& sockAddr)
    {
        ::memcpy(&socketAddress, &sockAddr, sizeof(sockaddr));
    }

    size_t Size() const
    {
        return sizeof(sockaddr);
    }

    sockaddr_in* GetAsSockAddrIn()
    {
        return reinterpret_cast<sockaddr_in*>(&socketAddress);
    }

private:
    sockaddr socketAddress;
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

int main()
{
    WSADATA data;
    bool init_suc = ::WSAStartup(MAKEWORD(2, 2), &data) == 0;

    //SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    //开启TCP套接字
    SOCKET tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    //INVALID_SOCKET

    SocketAddress address(L"127.0.0.1", 17971);
    auto sockAdd = address.GetAsSockAddrIn();

    //getaddrinfo();

    //停止数据发送与接收
    shutdown(tcpSocket, SD_BOTH);

    //关闭套接字
    closesocket(tcpSocket);

    ::WSACleanup();
    return 0;
}