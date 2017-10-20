/*
 * clientsocket.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef SOCKET_CLIENTSOCKET_HPP_
#define SOCKET_CLIENTSOCKET_HPP_

#include <string>

using namespace std;

class clientsocket
{
public:
	clientsocket();
	clientsocket(int socketId);

	clientsocket(string host, int port);
	~clientsocket();

	int getSocketId();

protected:
	int socketId;
};

#endif /* SOCKET_CLIENTSOCKET_HPP_ */
