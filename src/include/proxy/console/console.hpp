/*
 * console.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_CONSOLE_HPP_
#define INCLUDE_CONSOLE_HPP_

#include <vector>
#include <string>

#include "consolecommand.hpp"

#ifndef __WIN32__
#include <thread>
#else
#include <windows.h>
#endif

using namespace std;

class console
{
public:
	console();
	~console();

	static vector<consolecommand*>* getCommands();

protected:
	static void init();

#ifdef __WIN32__
	DWORD consoleThreadId;

	HANDLE consoleThread;

	static DWORD WINAPI initConsole(LPVOID lpParam);
#else
	thread* consoleThread;
#endif

private:
	static vector<consolecommand*>* commands;

	static void registerCommands();
};

#endif /* INCLUDE_CONSOLE_HPP_ */
