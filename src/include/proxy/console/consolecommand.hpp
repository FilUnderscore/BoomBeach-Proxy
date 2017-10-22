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
	consolecommand(string command, vector<string> aliases, string helpText);

	~consolecommand();

	virtual void execute();
};

#endif /* INCLUDE_CONSOLECOMMAND_HPP_ */
