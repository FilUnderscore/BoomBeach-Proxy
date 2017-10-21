/*
 * console.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_CONSOLE_HPP_
#define INCLUDE_CONSOLE_HPP_

#include <thread>

using namespace std;

class console
{
public:
	console();
	~console();

protected:
	static void init();

	thread* consoleThread;
};

#endif /* INCLUDE_CONSOLE_HPP_ */
