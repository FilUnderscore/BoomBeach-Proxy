/*
 * console.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/console/console.hpp"
#include "../../include/proxy/proxy.hpp"

#ifndef __WIN32__
console::console()
{
	this->consoleThread = new thread(init);
	this->consoleThread->detach();
}

console::~console()
{
	this->consoleThread->~thread();
}
#else
console::console()
{
	CreateThread(NULL, 0, console::initConsole, (void*)this, 0, consoleThread);
}

console::~console()
{

}
#endif

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
