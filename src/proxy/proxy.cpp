/*
 * proxy.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../include/proxy.hpp"

const string proxy::DEFAULT_HOST = "game.boombeachgame.com"; //22 chars long.

proxy* proxy::instance;

proxy::proxy() {}

proxy::~proxy()
{
	proxy::getProxy().con.~console();
	proxy::getProxy().net.~network();

	exit(0);
}

void proxy::init(string host, int port)
{
	proxy::getProxy().host = host;
	proxy::getProxy().port = port;

	proxy::getProxy().con = *new console();

	proxy::getProxy().net = *new network();
	proxy::getProxy().net.start();
}

void proxy::stop()
{
	proxy::getProxy().~proxy();
}

network proxy::getNetwork()
{
	return this->net;
}

string proxy::getHost()
{
	return this->host;
}

int proxy::getPort()
{
	return this->port;
}
