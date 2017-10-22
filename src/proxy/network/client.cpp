/*
 * client.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/client.hpp"
#include "../../include/proxy.hpp"

#include "../../include/messageheader.hpp"
#include "../../include/messagemap.hpp"

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

	byte_array clientPayload(READ_BYTES);

	int clientAvailable = 0;

	bool clientHeaderSet = false;
	messageheader clientHeader;

	while(true)
	{
		clientAvailable = instance.getSocket().available();

		if(clientAvailable == -1)
		{
			//EOF from client.
			break;
		}
		else if(clientAvailable >= 0)
		{
			if(!clientHeaderSet && clientAvailable >= messageheader::HEADER_LENGTH)
			{
				clientHeaderSet = true;

				instance.getSocket().readBuffer(clientPayload.buffer, 0, messageheader::HEADER_LENGTH);
				clientPayload.len = messageheader::HEADER_LENGTH;

				clientAvailable -= messageheader::HEADER_LENGTH;

				clientHeader = messageheader::parse(clientPayload);

				logger::log("[CLIENT] " + messagemap::getName(clientHeader.getId()));
				logger::log("[CLIENT] ID: " + to_string(clientHeader.getId()));
				logger::log("[CLIENT] PL: " + to_string(clientHeader.getPayloadLength()));
				logger::log("[CLIENT] V: " + to_string(clientHeader.getVersion()));
			}

			if(clientHeaderSet && clientAvailable >= clientHeader.getPayloadLength())
			{
				clientHeaderSet = false;

				instance.getSocket().readBuffer(clientPayload.buffer, 0, clientHeader.getPayloadLength());

				byte_array message(messageheader::HEADER_LENGTH + clientHeader.getPayloadLength());

				byte_array header = clientHeader.array();

				memcpy(message.buffer, header.buffer, messageheader::HEADER_LENGTH);

				free(header.buffer);

				memcpy(message.buffer + 7, clientPayload.buffer, clientHeader.getPayloadLength());

				logger::log("[SERVER] Payload: " + byte::toHexString(clientPayload));
				logger::log("");

				instance.getGameSocket().writeBuffer(message.buffer, 0, message.len);
			}
		}
	}
}

void client::runResponse(client instance)
{
	logger::log("Starting client response thread.");

	byte_array serverPayload(READ_BYTES);

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

				instance.getGameSocket().readBuffer(serverPayload.buffer, 0, messageheader::HEADER_LENGTH);
				serverPayload.len = messageheader::HEADER_LENGTH;

				serverAvailable -= messageheader::HEADER_LENGTH;

				serverHeader = messageheader::parse(serverPayload);

				//logger::log("[SERVER] HEADER: " + byte::toHexString(serverData, 7));

				logger::log("[SERVER] " + messagemap::getName(serverHeader.getId()));
				logger::log("[SERVER] ID: " + to_string(serverHeader.getId()));
				logger::log("[SERVER] PL: " + to_string(serverHeader.getPayloadLength()));
				logger::log("[SERVER] V: " + to_string(serverHeader.getVersion()));
			}

			if(serverHeaderSet && serverAvailable >= serverHeader.getPayloadLength())
			{
				serverHeaderSet = false;

				instance.getGameSocket().readBuffer(serverPayload.buffer, 0, serverHeader.getPayloadLength());

				byte_array message(messageheader::HEADER_LENGTH + serverHeader.getPayloadLength());

				byte_array header = serverHeader.array();

				memcpy(message.buffer, header.buffer, messageheader::HEADER_LENGTH);

				free(header.buffer);

				memcpy(message.buffer + 7, serverPayload.buffer, serverHeader.getPayloadLength());

				logger::log("[SERVER] Payload: " + byte::toHexString(serverPayload));
				logger::log("");

				instance.getSocket().writeBuffer(message.buffer, 0, message.len);
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
