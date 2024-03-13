// Server.cpp

#include "Server.h"
#include <WinSock2.h>

int Server::init(uint16_t port)
{
    
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return WINSOCK_INIT_ERROR;
    }

    
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor == INVALID_SOCKET)
    {
        WSACleanup();  
        return SETUP_ERROR;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        closesocket(socketDescriptor);
        WSACleanup();  
        return BIND_ERROR;
    }

    if (listen(socketDescriptor, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(socketDescriptor);
        WSACleanup(); 
        return SETUP_ERROR;
    }

    clientSocket = accept(socketDescriptor, NULL, NULL);
    if (clientSocket == INVALID_SOCKET)
    {
        closesocket(socketDescriptor);
        WSACleanup(); 
        return CONNECT_ERROR;
    }

    return SUCCESS;
}

int Server::readMessage(char* buffer, int32_t size)
{
    int bytesReceived = recv(clientSocket, buffer, size, 0);

    if (bytesReceived == SOCKET_ERROR)
    {
        
        closesocket(clientSocket);
        return RECEIVE_ERROR;
    }
    else if (bytesReceived == 0)
    {
        
        closesocket(clientSocket);
        return CLIENT_DISCONNECTED;
    }

    return SUCCESS;
}

int Server::sendMessage(char* data, int32_t length)
{
    int bytesSent = send(clientSocket, data, length, 0);
    if (bytesSent == SOCKET_ERROR)
    {
        closesocket(clientSocket);
        closesocket(socketDescriptor);
        return SEND_ERROR;
    }

    return SUCCESS;
}

void Server::stop()
{
    closesocket(clientSocket);
    closesocket(socketDescriptor);
    WSACleanup();  
}
