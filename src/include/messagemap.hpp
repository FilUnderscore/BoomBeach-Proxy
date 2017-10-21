/*
 * messagemap.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_MESSAGE_MESSAGES_HPP_
#define PROXY_MESSAGE_MESSAGES_HPP_

#include <string>
#include <map>

using namespace std;

class messagemap
{
public:
	static map<short, string> messages;

	static string getName(short id);

private:
	static bool initialized;

	static void initialize();
};

#endif /* PROXY_MESSAGE_MESSAGES_HPP_ */
