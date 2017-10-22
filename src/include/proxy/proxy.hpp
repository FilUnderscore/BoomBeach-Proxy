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

#include "console/console.hpp"
#include "network/network.hpp"

#include "../logger/logger.hpp"

using namespace std;

/*
 * SINGLETON
 */
class proxy
{
public:
	static const string DEFAULT_HOST;
	static const int DEFAULT_PORT = 9339; //Same in every supercell game.

	static void init(int port);
	static void init(string host, int port);

	void stop();

	string getHost();

	int getPort();

	static proxy& getProxy()
	{
		static proxy instance;
		return instance;
	}

	network* getNetwork();

protected:
	string host;
	int port;

	console* con;
	network* net;

private:
	static proxy* instance;

	proxy();
	proxy(const proxy&);
	proxy& operator=(const proxy&);
	~proxy();
};

#endif /* PROXY_PROXY_HPP_ */
