/*
 * consolecommand.cpp
 *
 *  Created on: 23/10/2017
 *      Author: filip
 */

#include "../../include/proxy/console/consolecommand.hpp"

consolecommand::consolecommand()
{

}

consolecommand::consolecommand(string command, string helpText) : consolecommand(command, new vector<string>, helpText)
{

}

consolecommand::consolecommand(string command, vector<string>* aliases, string helpText)
{
	this->aliases = aliases;

	this->aliases->insert(this->aliases->begin(), command);

	this->helpText = helpText;
}

consolecommand::~consolecommand()
{
	this->aliases->~vector();
}

vector<string>* consolecommand::getAliases()
{
	return aliases;
}

string consolecommand::getHelpText()
{
	return helpText;
}

void consolecommand::execute(vector<string> args)
{

}
