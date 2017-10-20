/*
 * client.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "client.hpp"
#include "proxy.hpp"

client::client(clientsocket socket)
{
	this->socket = socket;
	this->gameSocket = clientsocket(proxy::getProxy().host, proxy::getProxy().port);
}
