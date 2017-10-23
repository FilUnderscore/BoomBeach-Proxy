/*
 * console.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/console/console.hpp"
#include "../../include/proxy/util/stringutil.hpp"

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
		getline(cin, input);

		vector<string> text = stringutil::split(input, ' ');
		vector<string> args = *new vector<string>;

		string cmdName = text[0];

		for(std::vector<string>::iterator s = text.begin() + 1; s < text.end(); s++)
		{
			args.push_back(*s);
		}

		for(std::vector<consolecommand*>::iterator i = commands->begin(); i < commands->end(); i++)
		{
			consolecommand* cmd = *i;

			for(std::vector<string>::iterator j = cmd->getAliases()->begin(); j < cmd->getAliases()->end(); j++)
			{
				string msg = *j;

				std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
				std::transform(cmdName.begin(), cmdName.end(), cmdName.begin(), ::tolower);

				if(msg == cmdName)
				{
					cmd->execute(args);
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
