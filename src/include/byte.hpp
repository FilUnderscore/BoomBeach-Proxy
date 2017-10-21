/*
 * byte.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_BYTE_HPP_
#define INCLUDE_BYTE_HPP_

#include <iostream>
#include <string>

using namespace std;

#include "rrsint32.hpp"

class byte
{
public:
	static const int INT16_LENGTH = 2;
	static const int INT24_LENGTH = 3;
	static const int INT32_LENGTH = 4;
	static const int INT64_LENGTH = 8;

	//TO CHAR* FROM TYPE

	static unsigned char* fromInt16(short s);

	static unsigned char* fromInt24(int i);

	static unsigned char* fromInt32(int i);

	static unsigned char* fromInt64(long l);

	static unsigned char* fromRrsInt32(rrsint32 r);

	static unsigned char* fromString(string s);

	static unsigned char* fromHexString(string s);

	//FROM CHAR* TO TYPE

	static short toInt16(unsigned char* buffer);

	static int toInt24(unsigned char* buffer);

	static int toInt32(unsigned char* buffer);

	static long toInt64(unsigned char* buffer);

	static rrsint32 toRrsInt32(unsigned char* buffer);

	static string toString(unsigned char* buffer);

	static string toHexString(unsigned char* buffer, int buffersize);

private:
	static int charToInt(char c);
};
#endif /* INCLUDE_BYTE_HPP_ */
