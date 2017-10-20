/*
 * serversocket.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef SOCKET_SERVERSOCKET_HPP_
#define SOCKET_SERVERSOCKET_HPP_

#include <iostream>
#include <string>

#include "clientsocket.hpp"

#ifndef __WIN32__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#else
//Implement Winsock2
#endif

using namespace std;

class serversocket
{
public:
	static const int DEFAULT_CONNECTIONS_MAX = 100;

	serversocket();
	serversocket(string host, int port);
	serversocket(int port);
	~serversocket();

	clientsocket acceptClient();

	int getSocketId();

private:
	void initialize();

protected:
	string host;
	int port;

	int socketId;
};

#endif /* SOCKET_SERVERSOCKET_HPP_ */
