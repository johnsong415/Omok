#pragma once

#include <functional>


namespace Messaging {
    void Initialize();
    void SendMove(int x, int y);
    void RegisterMovePacketHandler(std::function<void(int, int)>&& onMoveReceived);

    void CloseClientSocket();
}
