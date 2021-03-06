/*
 * helpcommand.hpp
 *
 *  Created on: 24/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_PROXY_CONSOLE_COMMANDS_HELPCOMMAND_HPP_
#define INCLUDE_PROXY_CONSOLE_COMMANDS_HELPCOMMAND_HPP_

#include "../consolecommand.hpp"

class helpcommand : public consolecommand
{
public:
	helpcommand() : consolecommand("help", "Displays this message.") {}
	~helpcommand() {}

	void execute(vector<string> args);
};

#endif /* INCLUDE_PROXY_CONSOLE_COMMANDS_HELPCOMMAND_HPP_ */
