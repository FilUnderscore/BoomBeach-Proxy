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

console::console()
{
	registerCommands();

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

vector<consolecommand*>* console::commands;

//Commands
#include "../../include/proxy/console/commands/helpcommand.hpp"
#include "../../include/proxy/console/commands/stopcommand.hpp"
#include "../../include/proxy/console/commands/dumpcommand.hpp"

void console::registerCommands()
{
	commands = new vector<consolecommand*>();

	commands->push_back(new helpcommand());
	commands->push_back(new stopcommand());
	commands->push_back(new dumpcommand());
}

void console::init()
{
	string input;
	while(true)
	{
		getline(cin, input);

		vector<string> text = stringutil::split(input, ' ');
		vector<string> args = *new vector<string>;

		string cmdName = text[0];

		bool found = false;

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

				if(strcmp(msg.c_str(), cmdName.c_str()) == 0)
				{
					cmd->execute(args);
					found = true;
					goto exit;
				}
				else
				{
					found = false;
				}
			}
		}

		exit:
			if(!found)
			{
				logger::log("Console command \'" + input + "\' not found. Type \'help\' for a list of commands.");
			}
			continue;
	}
}

vector<consolecommand*>* console::getCommands()
{
	return commands;
}

#ifdef __WIN32__
DWORD WINAPI console::initConsole(LPVOID lpParam)
{
	console* instance = (console*)lpParam;

	instance->init();
}
#endif
