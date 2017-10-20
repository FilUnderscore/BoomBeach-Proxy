/*
 * client.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/client.hpp"
#include "../../include/proxy.hpp"

client::client()
{
	thread t(init, *this);
	t.join();
}

client::client(clientsocket socket) : client()
{
	this->socket = socket;
	this->gameSocket = *new clientsocket(proxy::getProxy().getHost(), proxy::getProxy().getPort());
}

client::~client()
{

}

void client::init(client client)
{

}
