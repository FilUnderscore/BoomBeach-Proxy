/*
 * console.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_CONSOLE_HPP_
#define INCLUDE_CONSOLE_HPP_

#ifndef __WIN32__
#include <thread>
#else
#include <windows.h>
#endif

using namespace std;

class console
{
public:
#ifndef __WIN32__
	console();
	~console();
#else
	console()
	{
		HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)initConsole, this, 0, this->consoleThread);
	}

	~console()
	{

	}
#endif

protected:
	static void init();
#ifdef __WIN32__
	PDWORD consoleThread;

	static DWORD WINAPI initConsole(LPVOID lpParam)
	{
		console* instance = (console*)lpParam;

		instance->init();
	}
#else
	thread* consoleThread;
#endif
};

#endif /* INCLUDE_CONSOLE_HPP_ */
