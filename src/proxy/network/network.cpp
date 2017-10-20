/*
 * network.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/network.hpp"
#include "../../include/logger.hpp"

network::network()
{

}

network::~network()
{

}

void network::start()
{
	serversocket servsock("127.0.0.1", 9339);

	std::thread t(thread, *this, servsock);
	t.join();
}

void network::thread(network instance, serversocket servsock)
{
	instance.running = true;

	while(instance.running)
	{
		clientsocket clisock = servsock.acceptClient();

		logger::log("new client");
	}
}

void network::connection(clientsocket socket)
{

}

void network::disconnect(client client)
{

}

void network::stop()
{

}
