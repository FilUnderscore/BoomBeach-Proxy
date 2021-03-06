/*
 * client.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/network/client.hpp"
#include "../../include/proxy/proxy.hpp"

#include "../../include/logger/logger.hpp"

#include "../../include/proxy/message/messageheader.hpp"
#include "../../include/proxy/message/messagemap.hpp"

client::client() {}

client::client(clientsocket socket) : client()
{
	//TODO: Testing
	messageHistory = *new vector<message>;

	this->socket = socket;
	this->gameSocket = *new clientsocket(proxy::getProxy().getHost(), proxy::getProxy().getPort());

#ifndef __WIN32__
	this->clientRequestThread = new thread(runRequest, *this);
	this->clientRequestThread->detach();

	this->clientResponseThread = new thread(runResponse, *this);
	this->clientResponseThread->detach();
#else
	clientRequestThread = CreateThread(NULL, 0, client::startRequest, (void*)this, 0, &clientRequestThreadId);
	clientResponseThread = CreateThread(NULL, 0, client::startResponse, (void*)this, 0, &clientResponseThreadId);
#endif
}

client::~client()
{

}

void client::disconnect()
{
	this->socket.disconnect();
	this->gameSocket.disconnect();

#ifndef __WIN32__
	//TODO: Deconstructors called during thread execution?
	this->clientRequestThread->~thread();
	this->clientResponseThread->~thread();
#else
	TerminateThread(this->clientRequestThread, 0);
	TerminateThread(this->clientResponseThread, 0);
#endif
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

		if(clientAvailable == -2)
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

				logger::log("[CLIENT] Message: " + messagemap::getName(clientHeader.getId()));
				logger::log("[CLIENT] ID: " + to_string(clientHeader.getId()));
				logger::log("[CLIENT] Payload Length: " + to_string(clientHeader.getPayloadLength()));
				logger::log("[CLIENT] Version: " + to_string(clientHeader.getVersion()));
			}

			if(clientHeaderSet && clientAvailable >= clientHeader.getPayloadLength())
			{
				clientHeaderSet = false;

				instance.getSocket().readBuffer(clientPayload.buffer, 0, clientHeader.getPayloadLength());
				clientPayload.len = clientHeader.getPayloadLength();

				message msg(clientHeader);
				msg.setEncryptedPayload(clientPayload);

				logger::log("[CLIENT] Encrypted Payload [HEX]: " + bytes::toHexString(msg.getEncryptedPayload()));
				logger::log("[CLIENT] Encrypted Payload [TEXT]: " + bytes::toString(msg.getEncryptedPayload()));

				byte_array message = proxy::getProxy().getNetwork()->processMessage(msg);

				logger::log("");

				instance.getGameSocket().writeBuffer(message.buffer, 0, message.len);

				free(message.buffer);

				//TODO: Testing
				//instance.messageHistory.push_back(msg);
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

		if(serverAvailable == -2)
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

				logger::log("[SERVER] Message: " + messagemap::getName(serverHeader.getId()));
				logger::log("[SERVER] ID: " + to_string(serverHeader.getId()));
				logger::log("[SERVER] Payload Length: " + to_string(serverHeader.getPayloadLength()));
				logger::log("[SERVER] Version: " + to_string(serverHeader.getVersion()));
			}

			if(serverHeaderSet && serverAvailable >= serverHeader.getPayloadLength())
			{
				serverHeaderSet = false;

				instance.getGameSocket().readBuffer(serverPayload.buffer, 0, serverHeader.getPayloadLength());
				serverPayload.len = serverHeader.getPayloadLength();

				message msg(serverHeader);
				msg.setEncryptedPayload(serverPayload);

				logger::log("[SERVER] Encrypted Payload [HEX]: " + bytes::toHexString(msg.getEncryptedPayload()));
				logger::log("[SERVER] Encrypted Payload [TEXT]: " + bytes::toString(msg.getEncryptedPayload()));

				byte_array message = proxy::getProxy().getNetwork()->processMessage(msg);

				logger::log("");

				instance.getSocket().writeBuffer(message.buffer, 0, message.len);

				free(message.buffer);

				//TODO: Testing
				//instance.messageHistory.push_back(msg);
			}
		}
	}
}

//TODO: Testing
vector<message> client::getMessageHistory()
{
	return messageHistory;
}

#ifdef __WIN32__
	DWORD WINAPI client::startRequest(LPVOID lpParam)
	{
		client* instance = (client*) lpParam;
		client::runRequest(*instance);
	}

	DWORD WINAPI client::startResponse(LPVOID lpParam)
	{
		client* instance = (client*) lpParam;
		client::runResponse(*instance);
	}
#endif

clientsocket client::getSocket()
{
	return this->socket;
}

clientsocket client::getGameSocket()
{
	return this->gameSocket;
}
