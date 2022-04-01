#pragma once

#include <functional>

#define BUFFER_SIZE         1024


namespace Network {
    bool StartServer();
    bool ConnectToServer(DWORD ipAddress);
    void NetworkUpdate();

    void SendData(const char* buffer, int size);
    void SetPacketHandler(std::function<void(const char*, int)>&& onMessageReceived);
    void SetDisconnectionHandler(std::function<void()>&& onDisconnected);

    bool DisconnectClient();
}
