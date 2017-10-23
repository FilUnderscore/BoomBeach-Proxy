/*
 * helpcommand.cpp
 *
 *  Created on: 24/10/2017
 *      Author: filip
 */

#include "../../../include/proxy/console/commands/helpcommand.hpp"
#include "../../../include/logger/logger.hpp"

void helpcommand::execute(vector<string> args)
{
	logger::log("Help");
}
