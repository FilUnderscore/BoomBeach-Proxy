/*
 * helpcommand.cpp
 *
 *  Created on: 24/10/2017
 *      Author: filip
 */

#include "../../../include/proxy/console/console.hpp"
#include "../../../include/proxy/console/commands/helpcommand.hpp"
#include "../../../include/logger/logger.hpp"

void helpcommand::execute(vector<string> args)
{
	logger::log("--- Proxy Help ---");

	std::vector<consolecommand*>* consoleCmds = console::getCommands();

	for(std::vector<consolecommand*>::iterator c = consoleCmds->begin(); c < consoleCmds->end(); c++)
	{
		consolecommand* cmd = *c;

		string text = "";

		string cmdName = cmd->getAliases()->at(0);

		text += cmdName;

		text += " [aliases: ";

		std::vector<string>* aliases = cmd->getAliases();

		for(std::vector<string>::iterator as = aliases->begin() + 1; as < aliases->end(); as++)
		{
			string alias = *as;

			text += alias + " ";
		}

		text += "] ";

		text += cmd->getHelpText();

		logger::log(text);
	}

	logger::log(""); //Newline (empty space)
}
