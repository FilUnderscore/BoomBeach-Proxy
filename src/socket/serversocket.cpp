/*
 * serversocket.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../include/socket/serversocket.hpp"
#include "../include/logger/logger.hpp"

serversocket::serversocket()
{}

serversocket::serversocket(string host, int port)
{
	this->socketId = -1;

	this->host = host;
	this->port = port;

	this->initialize();
}

serversocket::serversocket(int port) : serversocket("127.0.0.1", port)
{}

serversocket::~serversocket(){}

void serversocket::initialize()
{
	int serverSocketId;

	struct sockaddr_in serv_addr;
#ifdef __WIN32__
	WSAData wsaData;

	if(WSAStartup(0x101, &wsaData))
	{
		throw std::runtime_error("WSAStartup failed.");
	}
#endif

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	serverSocketId = socket(AF_INET, SOCK_STREAM, 0);

	if(bind(serverSocketId, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) != 0)
	{
		throw std::runtime_error("Failed to bind to server address/port.");
	}

	listen(serverSocketId, serversocket::DEFAULT_CONNECTIONS_MAX);

	this->socketId = serverSocketId;
}

clientsocket serversocket::acceptClient()
{
	if(this->socketId < 0)
		throw std::runtime_error("Serversocket is not listening!");

	struct sockaddr_in cli_addr;
#ifdef __WIN32__
	int clientAddrLen = sizeof(cli_addr);
#else
	unsigned int clientAddrLen = sizeof(cli_addr);
#endif

	int clientSocketId = accept(socketId, (struct sockaddr*) &cli_addr, &clientAddrLen);

	if(clientSocketId < 0)
		throw std::runtime_error("Failed when attempting to connect clientsocket.");

	return clientsocket(clientSocketId);
}

void serversocket::stop()
{
#ifdef __WIN32__
	closesocket(this->socketId);
	WSACleanup();
#else
	close(this->socketId);
#endif
}

int serversocket::getSocketId()
{
	return this->socketId;
}

string serversocket::getHost()
{
	return this->host;
}

int serversocket::getPort()
{
	return this->port;
}
