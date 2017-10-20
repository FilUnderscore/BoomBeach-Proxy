/*
 * proxy.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../include/proxy.hpp"

const string proxy::DEFAULT_HOST = "game.boombeachgame.com"; //22 chars long.

proxy* proxy::instance = NULL;

proxy::proxy(string host, int port)
{
	//TODO: Change host var.
	this->host = host;
	this->port = port;

	this->net = *new network();
	this->net.start();
}

void proxy::init(string host, int port)
{
	if(instance == NULL)
	{
		instance = new proxy(host, port);
	}
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

proxy* proxy::getProxy()
{
	return instance;
}
