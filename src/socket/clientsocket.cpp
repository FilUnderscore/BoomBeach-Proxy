/*
 * clientsocket.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../include/clientsocket.hpp"
#include "../include/logger.hpp"

clientsocket::clientsocket()
{

}

clientsocket::clientsocket(int socketId)
{
	this->socketId = socketId;
}

clientsocket::clientsocket(string host, int port)
{
	this->connectTo((char*)&host, port);
}

clientsocket::~clientsocket()
{

}

void clientsocket::connectTo(char* host, int port)
{
	int clientSocketId;

	struct sockaddr_in serv_addr;

	clientSocketId = socket(AF_INET, SOCK_STREAM, 0);

	if(clientSocketId < 0)
	{
		throw std::runtime_error("Failed to open clientsocket.");
	}

	//AF_INET for IPv4 support.
	serv_addr.sin_family = AF_INET;

	inet_pton(AF_INET, host, &serv_addr.sin_addr);

	serv_addr.sin_port = htons(port);

	unsigned int servAddrLen = sizeof(serv_addr);

	if(connect(clientSocketId, (struct sockaddr*) &serv_addr, servAddrLen) < 0)
	{
		throw std::runtime_error("Failed to connect to host.");
	}

	this->socketId = clientSocketId;
}

int clientsocket::getSocketId()
{
	return this->socketId;
}
