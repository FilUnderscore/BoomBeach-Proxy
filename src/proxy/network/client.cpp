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
	this->clientThread = new thread(init, *this);
	this->clientThread->detach();
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
