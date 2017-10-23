/*
 * console.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/console/console.hpp"

#include <algorithm>
#include <cstring>

vector<consolecommand*>* console::commands;

console::console()
{
	commands = new vector<consolecommand*>();

#ifndef __WIN32__
	this->consoleThread = new thread(init);
	this->consoleThread->detach();
#else
	consoleThread = CreateThread(NULL, 0, console::initConsole, (void*)this, 0, &consoleThreadId);
#endif
}

console::~console()
{
#ifndef __WIN32__
	this->consoleThread->~thread();
#else
	TerminateThread(consoleThread, 0);
#endif
}

void console::init()
{
	commands->push_back(new stopcommand());

	string input;
	while(true)
	{
		cin >> input;

		for(std::vector<consolecommand*>::iterator i = commands->begin(); i < commands->end(); i++)
		{
			consolecommand* cmd = *i;

			for(std::vector<string>::iterator j = cmd->getAliases()->begin(); j < cmd->getAliases()->end(); j++)
			{
				string msg = *j;

				std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
				std::transform(input.begin(), input.end(), input.begin(), ::tolower);

				if(msg == input)
				{
					cmd->execute();
				}
				else
				{
					logger::log("Console command \'" + input + "\' not found.");
				}
			}
		}
	}
}

#ifdef __WIN32__
DWORD WINAPI console::initConsole(LPVOID lpParam)
{
	console* instance = (console*)lpParam;

	instance->init();
}
#endif
