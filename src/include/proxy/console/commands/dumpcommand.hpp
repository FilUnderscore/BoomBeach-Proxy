/*
 * dumpcommand.hpp
 *
 *  Created on: 24/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_PROXY_CONSOLE_COMMANDS_DUMPCOMMAND_HPP_
#define INCLUDE_PROXY_CONSOLE_COMMANDS_DUMPCOMMAND_HPP_

#include "../consolecommand.hpp"

class dumpcommand : public consolecommand
{
public:
	dumpcommand() : consolecommand("dump", "Dumps a packet from a list.") {}
	~dumpcommand() {}

	void execute(vector<string> args);
};

#endif /* INCLUDE_PROXY_CONSOLE_COMMANDS_DUMPCOMMAND_HPP_ */
