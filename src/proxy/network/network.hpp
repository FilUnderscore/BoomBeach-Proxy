/*
 * network.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_NETWORK_NETWORK_HPP_
#define PROXY_NETWORK_NETWORK_HPP_

#include "clientsocket.hpp"
#include "serversocket.hpp"

class network
{
public:
	network();
	~network();

	void start();

	void connection(clientsocket socket);
};

#endif /* PROXY_NETWORK_NETWORK_HPP_ */
