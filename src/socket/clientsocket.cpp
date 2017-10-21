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
	//fcntl(clientSocketId, F_SETFL, O_NONBLOCK);

	if(clientSocketId < 0)
	{
		throw std::runtime_error("Failed to open clientsocket.");
	}

	//AF_INET for IPv4 support.
	serv_addr.sin_family = AF_INET;

	long hostAddress;
	hostent* hostInfo = gethostbyname(host.c_str());

	std::memset(&hostAddress, 0, sizeof(hostAddress));
	memcpy(&hostAddress,hostInfo->h_addr,hostInfo->h_length);

	serv_addr.sin_addr.s_addr = hostAddress;

	serv_addr.sin_port = htons(port);

	int err = connect(clientSocketId, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	if(err < 0)
	{
		throw std::runtime_error("Failed to connect to host. " + to_string(errno));
	}

	this->socketId = clientSocketId;
	this->conn = true;
}

bool clientsocket::connected()
{
	return this->conn;
}

void clientsocket::disconnect()
{
	this->conn = false;
	close(this->socketId);
}

int clientsocket::getSocketId()
{
	return this->socketId;
}

void clientsocket::writeBuffer(unsigned char* data, off_t offset, size_t length)
{
	lseek(this->socketId, offset, SEEK_SET);

	write(this->socketId, data, length);
}

int clientsocket::readBuffer(unsigned char* array, off_t offset, size_t length)
{
	lseek(this->socketId, offset, SEEK_SET);
	int bytes_read = read(this->socketId, array, length);

	return bytes_read;
}

int clientsocket::available()
{
	int bytesAvailable;

	ioctl(this->socketId, FIONREAD, &bytesAvailable);

	return bytesAvailable;
}
