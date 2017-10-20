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

}

clientsocket::clientsocket(string host, int port)
{

}

clientsocket::~clientsocket()
{

}

void clientsocket::connectTo(char* host, int port)
{
	int clientSocketId;

	struct sockaddr_in serv_addr;

	//Host computer
	struct hostent *server;

	clientSocketId = socket(AF_INET, SOCK_STREAM, 0);

	if(clientSocketId < 0)
	{
		logger::log("Failed to open clientsocket.");
		return;
	}

	server = gethostbyname(host);

	//AF_INET for IPv4 support.
	serv_addr.sin_family = AF_INET;

	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = htons(port);

	unsigned int servAddrLen = sizeof(serv_addr);

	if(connect(clientSocketId, (struct sockaddr*) &serv_addr, servAddrLen) < 0)
	{
		logger::log("Failed to connect to host.");
		return;
	}

	this->socketId = clientSocketId;
}

int clientsocket::getSocketId()
{
	return this->socketId;
}
