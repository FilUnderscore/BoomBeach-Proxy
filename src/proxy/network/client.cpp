/*
 * client.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/client.hpp"
#include "../../include/proxy.hpp"

client::client() {}

client::client(clientsocket socket) : client()
{
	this->socket = socket;
	this->gameSocket = *new clientsocket(proxy::getProxy().getHost(), proxy::getProxy().getPort());

	this->clientThread = new thread(run, *this);
	this->clientThread->detach();
}

client::~client()
{

}

void client::run(client instance)
{
	unsigned char clientData[4096];
	unsigned char serverData[4096];

	int clientAvailable = 0;
	int serverAvailable = 0;

	while(true)
	{
		//Client - Receive

		clientAvailable = instance.getSocket().available();
		serverAvailable = instance.getGameSocket().available();

		if(clientAvailable == -1 || serverAvailable == -1)
		{
			//EOF sent from client/server.
			break;
		}
		else
		{
			if(clientAvailable > 0)
			{
				logger::log("Client Message");

				instance.getSocket().readBuffer(clientData, 0, clientAvailable);
				instance.getGameSocket().writeBuffer(clientData, 0, clientAvailable);
			}

			if(serverAvailable > 0)
			{
				logger::log("Server Message");

				instance.getGameSocket().readBuffer(serverData, 0, serverAvailable);
				instance.getSocket().writeBuffer(serverData, 0, serverAvailable);
			}
		}
	}

	/*
	if(!instance.getSocket().connected())
	{
		//TODO: Client Disconnected
	}
	else if(!instance.getGameSocket().connected())
	{
		//TODO: Game Server Disconnected
	}
	*/
}

clientsocket client::getSocket()
{
	return this->socket;
}

clientsocket client::getGameSocket()
{
	return this->gameSocket;
}
