#pragma once
#include "../platform.h"
#include "../definitions.h"
#define INVALID_ADDRESS_ERROR -1
#define SERVER_DISCONNECTED -5
#define RECEIVE_ERROR -3
#define SEND_ERROR -7

class Client
{
public:
    int init(uint16_t port, char* address);
    int readMessage(char* buffer, int32_t size);
    int sendMessage(char* data, int32_t length);
    void stop();

private:
    SOCKET socketDescriptor;
};
