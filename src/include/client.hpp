/*
 * client.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_NETWORK_CLIENT_HPP_
#define PROXY_NETWORK_CLIENT_HPP_

#include "clientsocket.hpp"
#include <thread>

using namespace std;

class client
{
public:
	client(clientsocket socket);
	~client();

	client();

	clientsocket getSocket();
	clientsocket getGameSocket();

protected:
	/**
	 * Client/Device connection
	 */
	clientsocket socket;

	/**
	 * Game Server Socket - connects to Boom Beach server.
	 */
	clientsocket gameSocket;

	thread* clientThread;

	static void run(client instance);
};

#endif /* PROXY_NETWORK_CLIENT_HPP_ */
