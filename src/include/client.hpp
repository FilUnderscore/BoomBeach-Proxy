/*
 * client.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_NETWORK_CLIENT_HPP_
#define PROXY_NETWORK_CLIENT_HPP_

#include "clientsocket.hpp"

class client
{
public:
	client(clientsocket socket);
	~client();

protected:
	/**
	 * Client/Device connection
	 */
	clientsocket socket;

	/**
	 * Game Server Socket - connects to Boom Beach server.
	 */
	clientsocket gameSocket;
};

#endif /* PROXY_NETWORK_CLIENT_HPP_ */
