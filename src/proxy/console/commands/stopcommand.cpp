/*
 * stopcommand.cpp
 *
 *  Created on: 23/10/2017
 *      Author: filip
 */

#include "../../../include/proxy/console/commands/stopcommand.hpp"
#include "../../../include/proxy/proxy.hpp"

void stopcommand::execute(vector<string> args)
{
	logger::log("Stopping proxy... ");

	proxy::getProxy().stop();
}
