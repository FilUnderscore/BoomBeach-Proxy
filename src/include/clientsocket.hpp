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

#include <arpa/inet.h>

#ifndef __WIN32__
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#else
//TODO: Implement Winsock2
#endif

using namespace std;

class clientsocket
{
public:
	clientsocket();
	clientsocket(int socketId);

	clientsocket(string host, int port);
	~clientsocket();

	void connectTo(char* host, int port);

	int getSocketId();

protected:
	int socketId;
};

#endif /* SOCKET_CLIENTSOCKET_HPP_ */
