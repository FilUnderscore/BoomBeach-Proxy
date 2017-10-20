/*
 * client.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/client.hpp"
#include "../../include/proxy.hpp"
#include "../../include/clientsocket.hpp"

client::client(clientsocket socket)
{
	this->socket = socket;
	this->gameSocket = *new clientsocket(proxy::getProxy()->getHost(), proxy::getProxy()->getPort());
}

client::~client()
{

}
