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

	static proxy* getProxy();

protected:
	string host;
	int port;

private:
	static proxy* instance;

	proxy(string host, int port);
};

#endif /* PROXY_PROXY_HPP_ */
