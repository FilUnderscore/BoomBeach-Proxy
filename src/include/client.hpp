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
	//8 KiB
	static const int READ_BYTES = 8192;

	client(clientsocket socket);
	~client();

	client();

	clientsocket getSocket();
	clientsocket getGameSocket();

	void disconnect();

protected:
	/**
	 * Client/Device connection
	 */
	clientsocket socket;

	/**
	 * Game Server Socket - connects to Boom Beach server.
	 */
	clientsocket gameSocket;

	thread* clientRequestThread;
	thread* clientResponseThread;

	static void runRequest(client instance);
	static void runResponse(client instance);
};

#endif /* PROXY_NETWORK_CLIENT_HPP_ */
