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
#include <string.h>

using namespace std;

#include "byte_array.hpp"
#include "rrsint32.hpp"

class byte
{
public:
	static const int INT16_LENGTH = 2;
	static const int INT24_LENGTH = 3;
	static const int INT32_LENGTH = 4;
	static const int INT64_LENGTH = 8;

	//TO byte[] FROM TYPE

	static byte_array fromInt16(short s);

	static byte_array fromInt24(int i);

	static byte_array fromInt32(int i);

	static byte_array fromInt64(long l);

	static byte_array fromRrsInt32(rrsint32 r);

	static byte_array fromString(string s);

	static byte_array fromHexString(string s);

	//FROM byte[] TO TYPE

	static short toInt16(byte_array buffer);

	static int toInt24(byte_array buffer);

	static int toInt32(byte_array buffer);

	static long toInt64(byte_array buffer);

	static rrsint32 toRrsInt32(byte_array buffer);

	static string toString(byte_array buffer);

	static string toHexString(byte_array buffer);

private:
	static int charToInt(char c);
};
#endif /* INCLUDE_BYTE_HPP_ */
