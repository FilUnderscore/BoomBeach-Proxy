/*
 * consolecommand.hpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_CONSOLECOMMAND_HPP_
#define INCLUDE_CONSOLECOMMAND_HPP_

#include <vector>
#include <string>

using namespace std;

class consolecommand
{
public:
	consolecommand(string command, string helpText) : consolecommand(command, new vector<string>, helpText) {}

	consolecommand(string command, vector<string>* aliases, string helpText)
	{
		this->aliases = aliases;

		this->aliases->insert(this->aliases->begin(), command);

		this->helpText = helpText;
	}

	~consolecommand()
	{
		this->aliases->~vector();
	}

	void execute(vector<string> arguments);

	vector<string>* getAliases()
	{
		return aliases;
	}

protected:
	vector<string>* aliases;
	string helpText;
};

#endif /* INCLUDE_CONSOLECOMMAND_HPP_ */
