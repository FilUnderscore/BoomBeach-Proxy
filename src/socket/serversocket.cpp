/*
 * serversocket.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../include/serversocket.hpp"
#include "../include/logger.hpp"

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

#ifdef __WIN32__
	WSAData wsaData;

	sockaddr_in serv_addr;
#else
	struct sockaddr_in serv_addr;
#endif

#ifdef __WIN32__
	int wsaret = WSAStartup(0x101,&wsaData);

	if(wsaret != 0)
	{
		throw std::runtime_error("WSAStartup failed.");
	}
#endif

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	serverSocketId = socket(AF_INET, SOCK_STREAM, 0);

#ifdef __WIN32__
	if(bind(serverSocketId, (sockaddr*) &serv_addr, sizeof(serv_addr)) != 0)
	{
		throw std::runtime_error("Failed to bind to server address/port.");
	}
#else
	if(bind(serverSocketId, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) != 0)
	{
		throw std::runtime_error("Failed to bind to server address/port.");
	}
#endif

	listen(serverSocketId, serversocket::DEFAULT_CONNECTIONS_MAX);

	this->socketId = serverSocketId;

	/*
#ifndef __WIN32__
	int serverSocketId;

	struct sockaddr_in serv_addr;

	serverSocketId = socket(AF_INET, SOCK_STREAM, 0);

	if(serverSocketId < 0)
	{
		throw std::runtime_error("Failed to create socket.");
	}

	//Should always be AF_INET
	serv_addr.sin_family = AF_INET;

	//Server Address Port
	serv_addr.sin_port = htons(this->port);

	//Server Address
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(serverSocketId, (struct sockaddr*) &serv_addr, sizeof(serv_addr)))
	{
		throw std::runtime_error("Failed to bind to server address/port.");
	}

	listen(serverSocketId, serversocket::DEFAULT_CONNECTIONS_MAX);

	this->socketId = serverSocketId;
#else
	int serverSocketId;

	WSADATA wsaData;

	sockaddr_in local;

	if(WSAStartup(0x101, &wsaData) != 0)
	{
		throw std::runtime_error("WSAStartup failed.");
	}

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons((u_short)port);

	if((serverSocketId = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		throw std::runtime_error("Failed to create serversocket.");
	}

	if(bind(serverSocketId, (sockaddr*) &local, sizeof(local)) != 0)
	{
		throw std::runtime_error("Failed to bind to address/port.");
	}

	if(listen(serverSocketId, serversocket::DEFAULT_CONNECTIONS_MAX) != 0)
	{
		throw std::runtime_error("Failed to listen for clients.");
	}

	//TODO: Implement Winsock2
	//throw std::runtime_error("Windows support not implemented!");
	 */
}

clientsocket serversocket::acceptClient()
{
	if(this->socketId < 0)
		throw std::runtime_error("Serversocket is not listening!");

#ifndef __WIN32__
	struct sockaddr_in cli_addr;
	unsigned int clientAddrLen = sizeof(cli_addr);

#else
	sockaddr_in cli_addr;
	int clientAddrLen = sizeof(cli_addr);
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
