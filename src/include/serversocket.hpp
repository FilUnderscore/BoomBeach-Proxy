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

#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "clientsocket.hpp"

using namespace std;

class serversocket
{
public:
	static const int DEFAULT_CONNECTIONS_MAX = 100;

	serversocket(string host, int port);
	serversocket(int port);
	~serversocket();

	clientsocket acceptClient();

	int getSocketId();

private:
	void run();

	void initialize();

protected:
	string host;
	int port;

	int socketId;
};

#endif /* SOCKET_SERVERSOCKET_HPP_ */
