/*
 * clientsocket.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef SOCKET_CLIENTSOCKET_HPP_
#define SOCKET_CLIENTSOCKET_HPP_

#include <string>
#include <strings.h>

#include <unistd.h>

#include <cstring>

#ifndef __WIN32__
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#else
//TODO: Implement Winsock2
#include <Winsock2.h>
#endif

using namespace std;

class clientsocket
{
public:
	clientsocket();
	clientsocket(int socketId);

	clientsocket(string host, int port);
	~clientsocket();

	void connectTo(string host, int port);

	bool connected();

	void disconnect();

	//void writeBuffer(unsigned char* data);
	void writeBuffer(unsigned char* data, off_t offset, size_t length);

	//int readBuffer(unsigned char* array);
	int readBuffer(unsigned char* array, off_t offset, size_t length);

	int available();

	int getSocketId();

protected:
	int socketId;

	bool conn;
};

#endif /* SOCKET_CLIENTSOCKET_HPP_ */
