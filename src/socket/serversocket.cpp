/*
 * serversocket.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../include/serversocket.hpp"
#include "../include/logger.hpp"

serversocket::serversocket(string host, int port)
{
	this->socketId = -1;

	this->host = host;
	this->port = port;

	this->initialize();
}

serversocket::serversocket(int port) : serversocket("127.0.0.1", port)
{}

serversocket::~serversocket()
{
	//TODO: Deinitialize
}

void serversocket::initialize()
{
#ifndef __WIN32__
	int serverSocketId;

	struct sockaddr_in serv_addr;

	serverSocketId = socket(AF_INET, SOCK_STREAM, 0);

	if(serverSocketId < 0)
	{
		logger::log("Failed to create socket.");
		return;
	}

	//Should always be AF_INET
	serv_addr.sin_family = AF_INET;

	//Server Address Port
	serv_addr.sin_port = htons(this->port);

	//Server Address
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(serverSocketId, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))
	{
		logger::log("Failed to bind to server address/port.");
	}

	listen(serverSocketId, serversocket::DEFAULT_CONNECTIONS_MAX);

	this->socketId = serverSocketId;
#else
//TODO: Implement Winsock2
#endif
}

clientsocket serversocket::acceptClient()
{
#ifndef __WIN32__
	struct sockaddr_in cli_addr;
	unsigned int clientAddrLen = sizeof(cli_addr);

	int clientSocketId = accept(socketId, (struct sockaddr*) &cli_addr, &clientAddrLen);

	if(clientSocketId < 0)
		logger::log("Failed when attempting to connect clientsocket.");

	return clientsocket(clientSocketId);
#else
//TODO: Implement Winsock2
#endif
}

int serversocket::getSocketId()
{
	return this->socketId;
}