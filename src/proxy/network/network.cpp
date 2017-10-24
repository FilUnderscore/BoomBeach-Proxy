/*
 * network.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/network/network.hpp"
#include "../../include/logger/logger.hpp"
#include "../../include/proxy/proxy.hpp"

network::network()
{
	this->running = false;
	this->clients = new vector<client>;
}

network::~network()
{
	//TODO: Deinitialize
	this->serverSocket->stop();

	this->running = false;

	clear();

	this->clients->~vector();
}

void network::clear()
{
	for(int index = 0; index < this->clients->size(); index++)
	{
		this->clients->at(index).disconnect();
		this->clients->at(index).~client();
	}

	this->clients->clear();
}

void network::start()
{
	this->serverSocket = new serversocket("", 9339);

	logger::log("BoomBeach Proxy running. Connect via " + this->serverSocket->getHost() + ":" + to_string(proxy::getProxy().getPort()));
	logger::log("GPL v3.0 LICENSE - https://www.github.com/FilUnderscore/BoomBeach-Proxy");

	this->running = true;

	while(this->running)
	{
		clientsocket clisock = this->serverSocket->acceptClient();

		this->connection(clisock);
	}
}

void network::connection(clientsocket socket)
{
	client cli(socket);

	this->clients->push_back(cli);

	logger::log("Client connected.");
}

byte_array network::processMessage(message msg)
{
	byte_array message(messageheader::HEADER_LENGTH + msg.getHeader().getPayloadLength());
	byte_array header = msg.getHeader().array();

	memcpy(message.buffer, header.buffer, messageheader::HEADER_LENGTH);
	free(header.buffer);

	memcpy(message.buffer + 7, msg.getEncryptedPayload().buffer, msg.getHeader().getPayloadLength());

	return message;
}

void network::disconnect(client cli, bool client)
{
	if(client)
	{
		//Client socket disconnect
	}
	else
	{
		//Game server socket disconnect
	}
}

void network::stop()
{

}

vector<client>* network::getClients()
{
	return clients;
}
