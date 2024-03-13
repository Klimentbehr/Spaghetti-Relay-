
#pragma once
#include "../platform.h"
#include "../definitions.h"
#define WINSOCK_INIT_ERROR -2
#define RECEIVE_ERROR -3
#define SEND_ERROR -7
#define CLIENT_DISCONNECTED -4
class Server
{
public:
    int init(uint16_t port);
    int readMessage(char* buffer, int32_t size);
    int sendMessage(char* data, int32_t length);
    void stop();

private:
    SOCKET socketDescriptor;
    SOCKET clientSocket;
};