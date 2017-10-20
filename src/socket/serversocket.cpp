/*
 * serversocket.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../include/serversocket.hpp"
#include "../include/logger.hpp"

void serversocket::run()
{
	thread serverThread(initialize, (serversocket*)this);
	serverThread.join();
}

void serversocket::initialize(serversocket* servSocket)
{
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
	serv_addr.sin_port = htons(servSocket->port);

	//Server Address
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(serverSocketId, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))
	{
		logger::log("Failed to bind to server address/port.");
	}

	listen(serverSocketId, serversocket::DEFAULT_CONNECTIONS_MAX);

	servSocket->socketId = serverSocketId;
}

clientsocket serversocket::acceptClient()
{
	struct sockaddr_in cli_addr;
	unsigned int clientAddrLen = sizeof(cli_addr);

	int clientSocketId = accept(socketId, (struct sockaddr*) &cli_addr, &clientAddrLen);

	if(clientSocketId < 0)
		logger::log("Failed when attempting to connect clientsocket.");

	//TODO: Initialize clientsocket.
	return clientsocket(clientSocketId);
}

int serversocket::getSocketId()
{
	return this->socketId;
}
