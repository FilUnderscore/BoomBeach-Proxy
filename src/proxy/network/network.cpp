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

		client cli(clisock);

		this->clients.push_back(cli);

		unsigned char arr[4096];

		int n = cli.getSocket().readBuffer(arr, 0, 4096);

		logger::log(to_string(n));

		//TEST - WORKS

		cli.getGameSocket().writeBuffer(arr, 0, n);

		int no = cli.getGameSocket().readBuffer(arr, 0, 4096);

		logger::log(to_string(no));

		//TEST END

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
