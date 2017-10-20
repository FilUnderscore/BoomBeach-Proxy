/*
 * network.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/network.hpp"
#include "../../include/logger.hpp"
#include "../../include/proxy.hpp"

network::network()
{

}

network::~network()
{

}

void network::start()
{
	this->clients = *new vector<client>;

	serversocket servsock("127.0.0.1", 9339);

	logger::log("Proxy running. Connect via " + servsock.getHost() + ":" + to_string(proxy::getProxy().getPort()));

	this->running = true;

	while(this->running)
	{
		clientsocket clisock = servsock.acceptClient();

		logger::log("C");

		client cli(clisock);

		logger::log("D");

		this->clients.push_back(cli);

		logger::log("E");

		//void* arr = malloc(100);

		//cli.getSocket().read(arr);

		//logger::log("L: " + sizeof(arr));

		logger::log("new client");
	}
}

void network::thread(network instance, serversocket servsock)
{

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
