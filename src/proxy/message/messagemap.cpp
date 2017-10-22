/*
 * messagemap.cpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/messagemap.hpp"
#include <strings.h>

bool messagemap::initialized = false;
map<short, string> messagemap::messages;

string messagemap::getName(short id)
{
	initialize();

	if(messages.count(id))
	{
		return messages.at(id);
	}
	else
	{
		return messages.at(-1);
	}
}

int messagemap::getId(string name)
{
	initialize();

	for(map<short, string>::iterator it = messages.begin(); it != messages.end(); it++)
	{
		if(strcasecmp(it->second.c_str(), name.c_str()) == 0)
		{
			return it->first;
		}
	}

	return -1;
}

void messagemap::initialize()
{
	if(initialized)
		return;

	initialized = true;

	messages.insert({-1, "UnknownMessage"});

	/*
	 * CLIENT
	 */

	messages.insert({10100, "ClientHello"});
	messages.insert({10101, "ClientLogin"});

	messages.insert({10108, "ClientPing"});

	messages.insert({14101, "ClientAskHomeDataOwn"});

	messages.insert({14102, "ClientCommands"});

	/*
	 * SERVER
	 */

	messages.insert({20100, "ServerHello"});

	messages.insert({20103, "ServerLoginBad"});
	messages.insert({20104, "ServerLoginOk"});

	messages.insert({20108, "ServerPong"});

	messages.insert({24101, "ServerHomeDataOwn"});
	messages.insert({24102, "ServerOwnAvatarData"});
	messages.insert({24104, "ServerOutOfSync"});

	messages.insert({24351, "ServerUnknown1"});
	messages.insert({25100, "ServerUnknown2"});
	messages.insert({20118, "ServerUnknown3"});
	messages.insert({24497, "ServerUnknown4"});
	messages.insert({24411, "ServerUnknown5"});

	messages.insert({24111, "ServerCommand"});
}
