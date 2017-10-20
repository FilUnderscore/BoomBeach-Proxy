/*
 * proxy.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "proxy.hpp"
#include "network.hpp"

proxy::proxy(string host, int port)
{
	//TODO: Change host var.
}

proxy::proxy(int port)
{
	this->port = port;

	init();
}


void proxy::init()
{

}

void proxy::stop()
{

}

string proxy::getHost()
{
	return NULL;
}

int proxy::getPort()
{
	return this->port;
}
