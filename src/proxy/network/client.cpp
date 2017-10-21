/*
 * client.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/client.hpp"
#include "../../include/proxy.hpp"

#include "../../include/messageheader.hpp"

client::client() {}

client::client(clientsocket socket) : client()
{
	this->socket = socket;
	this->gameSocket = *new clientsocket(proxy::getProxy().getHost(), proxy::getProxy().getPort());

	this->clientRequestThread = new thread(runRequest, *this);
	this->clientRequestThread->detach();

	this->clientResponseThread = new thread(runResponse, *this);
	this->clientResponseThread->detach();
}

client::~client()
{

}

void client::disconnect()
{
	this->socket.disconnect();
	this->gameSocket.disconnect();

	//TODO: Deconstructors called during thread execution?
	this->clientRequestThread->~thread();
	this->clientResponseThread->~thread();
}

void client::runRequest(client instance)
{
	logger::log("Starting client request thread.");

	unsigned char clientData[READ_BYTES];

	int clientAvailable = 0;

	bool clientHeaderSet = false;
	messageheader clientHeader;

	while(true)
	{
		//Client - Receive

		clientAvailable = instance.getSocket().available();

		if(clientAvailable == -1)
		{
			//EOF sent from client.
			break;
		}
		else if(clientAvailable >= 0)
		{
			if(!clientHeaderSet && clientAvailable >= messageheader::HEADER_LENGTH)
			{
				clientHeaderSet = true;

				instance.getSocket().readBuffer(clientData, 0, messageheader::HEADER_LENGTH);
				clientAvailable -= messageheader::HEADER_LENGTH;

				clientHeader = messageheader::parse(clientData);

				logger::log("[CLIENT] HEADER: " + byte::toHexString(clientData, 7));

				logger::log("[CLIENT] ID: " + to_string(clientHeader.getId()));
				logger::log("[CLIENT] PL: " + to_string(clientHeader.getPayloadLength()));
				logger::log("[CLIENT] V: " + to_string(clientHeader.getVersion()));
			}

			if(clientHeaderSet && clientAvailable >= clientHeader.getPayloadLength())
			{
				clientHeaderSet = false;

				instance.getSocket().readBuffer(clientData, 0, clientHeader.getPayloadLength());

				int messageLength = messageheader::HEADER_LENGTH + clientHeader.getPayloadLength();
				unsigned char message[messageLength];

				unsigned char* headerArray = clientHeader.array();

				memcpy(message, headerArray, messageheader::HEADER_LENGTH);

				free(headerArray);

				memcpy(message + 7, clientData, clientHeader.getPayloadLength());

				logger::log("[CLIENT] Payload: " + byte::toHexString(message, messageLength));
				logger::log("");

				instance.getGameSocket().writeBuffer(message, 0, messageLength);
			}
		}
	}
}

void client::runResponse(client instance)
{
	logger::log("Starting client response thread.");

	unsigned char serverData[READ_BYTES];

	int serverAvailable = 0;

	bool serverHeaderSet = false;
	messageheader serverHeader;

	while(true)
	{
		serverAvailable = instance.getGameSocket().available();

		if(serverAvailable == -1)
		{
			//EOF from server.
			break;
		}
		else if(serverAvailable >= 0)
		{
			if(!serverHeaderSet && serverAvailable >= messageheader::HEADER_LENGTH)
			{
				serverHeaderSet = true;

				instance.getGameSocket().readBuffer(serverData, 0, messageheader::HEADER_LENGTH);
				serverAvailable -= messageheader::HEADER_LENGTH;

				serverHeader = messageheader::parse(serverData);

				logger::log("[SERVER] HEADER: " + byte::toHexString(serverData, 7));

				logger::log("[SERVER] ID: " + to_string(serverHeader.getId()));
				logger::log("[SERVER] PL: " + to_string(serverHeader.getPayloadLength()));
				logger::log("[SERVER] V: " + to_string(serverHeader.getVersion()));
			}

			if(serverHeaderSet && serverAvailable >= serverHeader.getPayloadLength())
			{
				serverHeaderSet = false;

				instance.getGameSocket().readBuffer(serverData, 0, serverHeader.getPayloadLength());

				int messageLength = messageheader::HEADER_LENGTH + serverHeader.getPayloadLength();
				unsigned char message[messageLength];

				unsigned char* headerArray = serverHeader.array();

				memcpy(message, headerArray, messageheader::HEADER_LENGTH);

				free(headerArray);

				memcpy(message + 7, serverData, serverHeader.getPayloadLength());

				logger::log("[SERVER] Payload: " + byte::toHexString(message, messageLength));
				logger::log("");

				instance.getSocket().writeBuffer(message, 0, messageLength);
			}
		}
	}
}

clientsocket client::getSocket()
{
	return this->socket;
}

clientsocket client::getGameSocket()
{
	return this->gameSocket;
}
