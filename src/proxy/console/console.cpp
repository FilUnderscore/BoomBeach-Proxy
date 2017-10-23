/*
 * console.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/console/console.hpp"
#include "../../include/proxy/proxy.hpp"

console::console()
{
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
	string input;

	while(true)
	{
		cin >> input;

		//TODO: Implement console commands.

		if(input == "stop")
		{
			logger::log("Stopping proxy...");

			proxy::getProxy().stop();
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
