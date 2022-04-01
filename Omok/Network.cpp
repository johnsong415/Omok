
#pragma comment(lib,"Ws2_32.lib")

#include "framework.h"
#include "Network.h"

#include <winsock2.h>
#include <ws2tcpip.h>

const USHORT LISTENING_PORT = 9998;
const int LISTEN_BACK_LOG = 1;

SOCKET g_listenSocket = INVALID_SOCKET;
SOCKET g_clientSocket = INVALID_SOCKET;

std::function<void(const char*, int)> g_onMessageReceived;
std::function<void()> g_onDisconnected;


class WinsockInitializer
{
public:
    WinsockInitializer()
    {
        WSADATA wsaData = { 0 };
        auto result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            MessageBox(NULL, L"Winsock initialization failed!\nMultiplay will not be supported.", L"Critical error", MB_ICONEXCLAMATION | MB_OK);
        }
    }

    ~WinsockInitializer()
    {
        if (g_listenSocket != INVALID_SOCKET) closesocket(g_listenSocket);
        WSACleanup();
    }
} _WinsockInitializerInstance;


bool Network::StartServer()
{
    if (g_listenSocket != INVALID_SOCKET) closesocket(g_listenSocket);

    g_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_listenSocket == INVALID_SOCKET) return false;

    sockaddr_in service;
    service.sin_family = AF_INET;
    inet_pton(AF_INET, "0.0.0.0", &service.sin_addr.s_addr);
    service.sin_port = htons(LISTENING_PORT);

    int result = bind(g_listenSocket, (SOCKADDR*) &service, sizeof(service));
    if (result == SOCKET_ERROR) return false;

    result = listen(g_listenSocket, LISTEN_BACK_LOG);
    if (result == SOCKET_ERROR) return false;

    return true;
}

bool Network::ConnectToServer(DWORD ipAddress)
{
    if (g_clientSocket != INVALID_SOCKET) closesocket(g_clientSocket);

    g_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_clientSocket == INVALID_SOCKET) return false;

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = htonl(ipAddress);
    service.sin_port = htons(LISTENING_PORT);
    
    return connect(g_clientSocket, (SOCKADDR*) &service, sizeof(service)) == 0;
}

void Network::NetworkUpdate()
{
    if (g_listenSocket == INVALID_SOCKET && g_clientSocket == INVALID_SOCKET) return;

    static fd_set readFDs;
    FD_ZERO(&readFDs);
    if (g_listenSocket != INVALID_SOCKET) FD_SET(g_listenSocket, &readFDs);
    if (g_clientSocket != INVALID_SOCKET) FD_SET(g_clientSocket, &readFDs);

    static fd_set writeFDs;
    FD_ZERO(&writeFDs);
    if (g_clientSocket != INVALID_SOCKET) FD_SET(g_clientSocket, &writeFDs);

    static timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10000;

    int selected = select(0, &readFDs, &writeFDs, nullptr, &tv);
    if (selected < 0) {
        MessageBox(NULL, L"Communication error!\nSocket multiplexing failed.", L"Critical error", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    if (selected == 0) return; // no changes in the sockets

    if (FD_ISSET(g_listenSocket, &readFDs)) {
        SOCKET clientSocket = accept(g_listenSocket, nullptr, nullptr);
        if (g_clientSocket == INVALID_SOCKET) {
            g_clientSocket = clientSocket;
        }
        else {
            // reject if a client is alrady connected
            closesocket(clientSocket);
        }
    }

    if (FD_ISSET(g_clientSocket, &readFDs)) {
        char recvBuffer[1024];
        int read = recv(g_clientSocket, recvBuffer, sizeof(recvBuffer) / sizeof(recvBuffer[0]), 0);
        if (read == 0) {
            // we're disconnected
            closesocket(g_clientSocket);
            closesocket(g_listenSocket);
            g_clientSocket = g_listenSocket = INVALID_SOCKET;
            if (g_onDisconnected) g_onDisconnected();
        }
        else if (read < 0) {
            shutdown(g_clientSocket, SD_BOTH);
            MessageBox(NULL, L"Communication error!\nReceiving from socket failed.", L"Critical error", MB_ICONEXCLAMATION | MB_OK);
        }
        else
        {
            if (g_onMessageReceived) g_onMessageReceived(recvBuffer, read);
        }
    }

    if (FD_ISSET(g_clientSocket, &writeFDs)) {
        ;
    }
}

void Network::SendData(const char* buffer, int size)
{
    if (g_clientSocket == INVALID_SOCKET) return;

    int sentAll = 0;
    while (sentAll < size) {
        int sent = send(g_clientSocket, &buffer[sentAll], size - sentAll, 0);
        if (sent < 0) {
            shutdown(g_clientSocket, SD_BOTH);
            MessageBox(NULL, L"Communication error!\nSending to socket failed.", L"Critical error", MB_ICONEXCLAMATION | MB_OK);
            return;
        }

        sentAll += sent;
    }
}

void Network::SetPacketHandler(std::function<void(const char*, int)>&& onMessageReceived)
{
    g_onMessageReceived = std::move(onMessageReceived);
}

void Network::SetDisconnectionHandler(std::function<void()>&& onDisconnected)
{
    g_onDisconnected = std::move(onDisconnected);
}

bool Network::DisconnectClient()
{
    return closesocket(g_clientSocket) == 0;
}
