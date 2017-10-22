/*
 * logger.cpp
 *
 *  Created on: 20/10/2017
 *      Author: filip
 */

#include "../include/logger.hpp"

bool logger::fileInitialized = false;
string logger::logFileName = "";
std::ofstream* logger::logFileStream;

void logger::log(string message)
{
	cout << message << endl;

	if(logger::fileInitialized)
	{
		*logFileStream << message << '\n';
		logFileStream->flush();
	}
}

void logger::file(string fileName)
{
	logFileName = fileName;
	logFileStream = new std::ofstream(fileName, std::ios_base::out | std::ios_base::app);
	fileInitialized = true;

	log("Initialized file log.");
}
