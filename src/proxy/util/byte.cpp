/*
 * byte.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/byte.hpp"
#include "../../include/logger.hpp"

//FROM TYPE TO CHAR*
unsigned char* byte::fromInt16(short s)
{
	unsigned char* buffer = (unsigned char*)malloc(INT16_LENGTH);

	buffer[0] = (s >> 8) & 0xFF;
	buffer[1] = s & 0xFF;

	return buffer;
}

unsigned char* byte::fromInt24(int i)
{
	unsigned char* buffer = (unsigned char*)malloc(INT24_LENGTH);

	buffer[0] = (0xFF >> 24) & 0xFF;
	buffer[1] = (i >> 16) & 0xFF;
	buffer[2] = (i >> 8) & 0xFF;
	buffer[3] = i & 0xFF;

	return buffer;
}

unsigned char* byte::fromInt32(int i)
{
	unsigned char* buffer = (unsigned char*)malloc(INT32_LENGTH);

	buffer[0] = (i >> 24) & 0xFF;
	buffer[1] = (i >> 16) & 0xFF;
	buffer[2] = (i >> 8) & 0xFF;
	buffer[3] = i & 0xFF;

	return buffer;
}

unsigned char* byte::fromInt64(long l)
{
	unsigned char* buffer = (unsigned char*)malloc(INT64_LENGTH);

	buffer[0] = (l >> 56) & 0xFFFFFFFF;
	buffer[1] = (l >> 48) & 0xFFFFFFFF;
	buffer[2] = (l >> 40) & 0xFFFFFFFF;
	buffer[3] = (l >> 32) & 0xFFFFFFFF;
	buffer[4] = (l >> 24) & 0xFFFFFFFF;
	buffer[5] = (l >> 16) & 0xFFFFFFFF;
	buffer[6] = (l >> 8) & 0xFFFFFFFF;
	buffer[7] = l & 0xFFFFFFFF;

	return buffer;
}

unsigned char* byte::fromRrsInt32(rrsint32 r)
{
	return NULL;
}

unsigned char* byte::fromString(string s)
{
	return (unsigned char*)s.c_str();
}

//FROM CHAR* TO TYPE

short byte::toInt16(unsigned char* buffer)
{
	return (buffer[0] << 8) | buffer[1];
}

int byte::toInt24(unsigned char* buffer)
{
	return (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
}

int byte::toInt32(unsigned char* buffer)
{
	return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
}

long byte::toInt64(unsigned char* buffer)
{
	return (buffer[0] << 56) | (buffer[1] << 48) | (buffer[2] << 40) |
			(buffer[3] << 32) | (buffer[4] << 24) | (buffer[5] << 16) |
			(buffer[6] << 8) | buffer[7];
}

rrsint32 byte::toRrsInt32(unsigned char* buffer)
{
	return rrsint32();
}

string byte::toString(unsigned char* buffer)
{
	return string((char*)buffer);
}

/*
 * From https://codereview.stackexchange.com/questions/78535/
 */
string byte::toHexString(unsigned char* buffer, int buffersize)
{
	char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	std::string s(buffersize * 2, ' ');

	 for (int i = 0; i < buffersize; ++i)
	 {
		 s[2 * i]     = hexmap[(buffer[i] & 0xF0) >> 4];
		 s[2 * i + 1] = hexmap[buffer[i] & 0x0F];
	 }

	 return s;
}
