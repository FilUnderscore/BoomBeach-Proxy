/*
 * network.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_NETWORK_NETWORK_HPP_
#define PROXY_NETWORK_NETWORK_HPP_

#include "client.hpp"
#include "../../socket/serversocket.hpp"
#include "../message/message.hpp"

#include <vector>
#include <thread>

using namespace std;

class network
{
public:
	network();
	~network();

	void start();

	void connection(clientsocket socket);

	byte_array processMessage(message message);

	void disconnect(client cli, bool client);

	void stop();

protected:
	vector<client> clients;
	serversocket* serverSocket;

	bool running;

private:
	void clear();
};

#endif /* PROXY_NETWORK_NETWORK_HPP_ */
