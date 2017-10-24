/*
 * logger.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_LOGGER_HPP_
#define INCLUDE_LOGGER_HPP_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class logger
{
public:
	static void file(string fileName);

	static void log(string message);

private:
	static string logFileName;
	static ofstream* logFileStream;
	static bool fileInitialized;
};

#endif /* INCLUDE_LOGGER_HPP_ */
