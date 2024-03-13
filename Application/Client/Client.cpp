#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Client.h"
#include <WinSock2.h>

int Client::init(uint16_t port, char* address)
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor == INVALID_SOCKET)
    {
        return SETUP_ERROR;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    serverAddress.sin_addr.s_addr = inet_addr(address);
    if (serverAddress.sin_addr.s_addr == INADDR_NONE)
    {
        closesocket(socketDescriptor);
        return INVALID_ADDRESS_ERROR;
    }

    if (connect(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        closesocket(socketDescriptor);
        return CONNECT_ERROR;
    }

    return SUCCESS;
}

int Client::readMessage(char* buffer, int32_t size)
{
    
    int bytesReceived = recv(socketDescriptor, buffer, size, 0);

    if (bytesReceived == SOCKET_ERROR)
    {
        closesocket(socketDescriptor);
        return RECEIVE_ERROR;
    }
    else if (bytesReceived == 0)
    {
        closesocket(socketDescriptor);
        return SERVER_DISCONNECTED;
    }
    

    return SUCCESS;
}

int Client::sendMessage(char* data, int32_t length)
{

    int bytesSent = send(socketDescriptor, data, length, 0);
    if (bytesSent == SOCKET_ERROR)
    {
        closesocket(socketDescriptor);
        return SEND_ERROR;
    }


    return SUCCESS;
}

void Client::stop()
{
    closesocket(socketDescriptor);
}
