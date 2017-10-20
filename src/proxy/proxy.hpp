/*
 * proxy.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_PROXY_HPP_
#define PROXY_PROXY_HPP_

#include <iostream>
#include <string>

using namespace std;

class proxy
{
public:
	static const int DEFAULT_HOST = "game.boombeachgame.com"; //22 chars long.
	static const int DEFAULT_PORT = 9339; //Same in every supercell game.

	proxy(string host, int port);

	proxy(int port);

	void init();

	void stop();

	string getHost();

	int getPort();

	static proxy getProxy();

protected:
	string host;
	int port;
};

#endif /* PROXY_PROXY_HPP_ */
