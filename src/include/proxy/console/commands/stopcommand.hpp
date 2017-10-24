/*
 * stopcommand.hpp
 *
 *  Created on: 23/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_PROXY_CONSOLE_COMMANDS_STOPCOMMAND_HPP_
#define INCLUDE_PROXY_CONSOLE_COMMANDS_STOPCOMMAND_HPP_

#include "../consolecommand.hpp"
#include "../../../logger/logger.hpp"

class stopcommand : public consolecommand
{
public:
	stopcommand() : consolecommand("stop", "Stops the Proxy...") {}
	~stopcommand() {}

	void execute(vector<string> args);
};

#endif /* INCLUDE_PROXY_CONSOLE_COMMANDS_STOPCOMMAND_HPP_ */
