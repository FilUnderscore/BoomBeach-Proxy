/*
 * client.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_NETWORK_CLIENT_HPP_
#define PROXY_NETWORK_CLIENT_HPP_

#include "../../socket/clientsocket.hpp"

#ifndef __WIN32__
#include <thread>
#else
#include <windows.h>
#endif

using namespace std;

class client
{
public:
	//8 KiB
	static const int READ_BYTES = 8192;

	client(clientsocket socket);
	~client();

	client();

	clientsocket getSocket();
	clientsocket getGameSocket();

	void disconnect();

protected:
	/**
	 * Client/Device connection
	 */
	clientsocket socket;

	/**
	 * Game Server Socket - connects to Boom Beach server.
	 */
	clientsocket gameSocket;

#ifndef __WIN32__
	thread* clientRequestThread;
	thread* clientResponseThread;
#else
	DWORD clientRequestThreadId;
	DWORD clientResponseThreadId;

	HANDLE clientRequestThread;
	HANDLE clientResponseThread;

	static DWORD WINAPI startRequest(LPVOID lpParam);
	static DWORD WINAPI startResponse(LPVOID lpParam);
#endif

	/**
	 * Required to be static otherwise std::thread needs struct instance.
	 */
	static void runRequest(client instance);
	static void runResponse(client instance);
};

#endif /* PROXY_NETWORK_CLIENT_HPP_ */
