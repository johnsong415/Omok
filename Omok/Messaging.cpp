#include "framework.h"
#include "Messaging.h"
#include "Network.h"

#define HEADER_LENGTH       2


class MessageAPI
{
public:
    MessageAPI();
    ~MessageAPI();

public:
    void Initialize();

    void SendMove(int x, int y);
    void RegisterMovePacketHandler(std::function<void(int, int)>&& onMoveReceived);

    void CloseClientSocket();
private:
    void OnDataReceived(const char* buffer, int size);

private:
    std::function<void(int, int)> m_onMoveReceived = nullptr;
    char m_packetBuffer[BUFFER_SIZE];
    size_t m_usedpacketBuffer = 0;
} g_singletonMessageAPI;



MessageAPI::MessageAPI()
{
}

MessageAPI::~MessageAPI()
{
}

void MessageAPI::Initialize()
{
}

void MessageAPI::SendMove(int x, int y)
{
    // Packet: header (body length; 2 bytes) + body
    Move move;
    move.x = x;
    move.y = y;

    unsigned short length = sizeof(move);
    Network::SendData((const char*) &length, 2);
    Network::SendData((const char*) &move, (int) length);
}


void MessageAPI::RegisterMovePacketHandler(std::function<void(int, int)>&& onMoveReceived)
{
    m_onMoveReceived = std::move(onMoveReceived);
    Network::SetPacketHandler([this](const char* buffer, int size) { OnDataReceived(buffer, size); });
}


void MessageAPI::OnDataReceived(const char* buffer, int size)
{
    if (!m_onMoveReceived || size <= 0) return;

    int bufferIndex = 0;
    while (bufferIndex < size) {
        unsigned short length = 0;
        if (m_usedpacketBuffer == 0) {
            if (size < HEADER_LENGTH) {
                memcpy(m_packetBuffer, (const void*) buffer, size);
                m_usedpacketBuffer = size;
                return;
            }

            length = *((unsigned short*) buffer);
            bufferIndex += sizeof(unsigned short);

            if ((size - bufferIndex) < length) {
                bufferIndex -= sizeof(unsigned short);
                memcpy(m_packetBuffer, (const void*) &buffer[bufferIndex], size - bufferIndex);
                m_usedpacketBuffer = (size - bufferIndex);
                return;
            }
        }
        else {
            if (m_usedpacketBuffer < HEADER_LENGTH) {
                memcpy(&m_packetBuffer[m_usedpacketBuffer], buffer, HEADER_LENGTH - m_usedpacketBuffer);
                bufferIndex += (HEADER_LENGTH - static_cast<int>(m_usedpacketBuffer));
                m_usedpacketBuffer += (HEADER_LENGTH - m_usedpacketBuffer);
            }

            length = *((unsigned short*) m_packetBuffer);

            if ((size - bufferIndex) < length) {
                memcpy(&m_packetBuffer[m_usedpacketBuffer], (const void*) &buffer[bufferIndex], size - bufferIndex);
                m_usedpacketBuffer += (size - bufferIndex);
                return;
            }
        }

        static Move move;
        if (length == sizeof(move)) {
            memcpy((void*) &move, (const void*) &buffer[bufferIndex], length);
            m_onMoveReceived(move.x, move.y);
        }
        else
        {
            MessageBox(NULL, L"Communication error!\nBad packet received.", L"Critical error", MB_ICONEXCLAMATION | MB_OK);
        }

        bufferIndex += length;
    }
}

void MessageAPI::CloseClientSocket()
{
    Network::DisconnectClient();
}


// public Messaging functions
////////////////////////////////////////////////////////////////////////////////////////////
void Messaging::Initialize()
{
    g_singletonMessageAPI.Initialize();
}

void Messaging::SendMove(int x, int y)
{
    g_singletonMessageAPI.SendMove(x, y);
}

void Messaging::RegisterMovePacketHandler(std::function<void(int, int)>&& onMoveReceived)
{
    g_singletonMessageAPI.RegisterMovePacketHandler(std::move(onMoveReceived));
}

void Messaging::CloseClientSocket()
{
    g_singletonMessageAPI.CloseClientSocket();
}