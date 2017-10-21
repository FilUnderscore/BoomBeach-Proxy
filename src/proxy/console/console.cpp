/*
 * console.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/console.hpp"
#include "../../include/proxy.hpp"


console::console()
{
	this->consoleThread = new thread(init);
	this->consoleThread->detach();
}

console::~console()
{
	this->consoleThread->~thread();
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
			logger::log("Stop");
			proxy::getProxy().stop();
		}
	}
}
