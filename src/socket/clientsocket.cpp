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
	this->connectTo(host, port);
}

clientsocket::~clientsocket()
{

}

void clientsocket::connectTo(string host, int port)
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

	logger::log("Host: " + std::string(host) + " | Port: " + to_string(port));

	inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr);

	serv_addr.sin_port = htons(port);

	if(connect(clientSocketId, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		throw std::runtime_error("Failed to connect to host.");
	}

	this->socketId = clientSocketId;
}

int clientsocket::getSocketId()
{
	return this->socketId;
}

void clientsocket::write(void* data)
{
	this->write(data, 0, sizeof(data));
}

void clientsocket::write(void* data, int offset, int length)
{
	pwrite(this->socketId, data, length, offset);
}

void clientsocket::read(void* data)
{
	this->read(data, 0, sizeof(data));
}

void clientsocket::read(void* array, int offset, int length)
{
	pread(this->socketId, array, length, offset);
}
