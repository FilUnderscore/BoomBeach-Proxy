/*
 * byte.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/util/bytes.hpp"
#include "../../include/proxy/util/rrsint32.hpp"
#include "../../include/logger/logger.hpp"
#include "../../include/proxy/io/binstream.hpp"

//FROM TYPE TO byte[]
byte_array bytes::fromInt16(short s)
{
	byte_array array(INT16_LENGTH);

	array.buffer[0] = (s >> 8) & 0xFF;
	array.buffer[1] = s & 0xFF;

	return array;
}

byte_array bytes::fromInt24(int i)
{
	byte_array array(INT24_LENGTH);

	array.buffer[0] = (i >> 16) & 0xFF;
	array.buffer[1] = (i >> 8) & 0xFF;
	array.buffer[2] = i & 0xFF;

	return array;
}

byte_array bytes::fromInt32(int i)
{
	byte_array array(INT32_LENGTH);

	array.buffer[0] = (i >> 24) & 0xFF;
	array.buffer[1] = (i >> 16) & 0xFF;
	array.buffer[2] = (i >> 8) & 0xFF;
	array.buffer[3] = i & 0xFF;

	return array;
}

byte_array bytes::fromInt64(long l)
{
	byte_array array(INT64_LENGTH);

	array.buffer[0] = (l >> 56) & 0xFFFFFFFF;
	array.buffer[1] = (l >> 48) & 0xFFFFFFFF;
	array.buffer[2] = (l >> 40) & 0xFFFFFFFF;
	array.buffer[3] = (l >> 32) & 0xFFFFFFFF;
	array.buffer[4] = (l >> 24) & 0xFFFFFFFF;
	array.buffer[5] = (l >> 16) & 0xFFFFFFFF;
	array.buffer[6] = (l >> 8) & 0xFFFFFFFF;
	array.buffer[7] = l & 0xFFFFFFFF;

	return array;
}

byte_array bytes::fromRrsInt32(rrsint32 r)
{
	//TODO: Implement
	return *new byte_array(0);
}

byte_array bytes::fromString(string s)
{
	byte_array array(s.length());

	memcpy(array.buffer, s.c_str(), s.length());

	return array;
}

byte_array bytes::fromHexString(string s)
{
	byte_array array(s.length() * 2);

	while(*s.c_str() && s[1])
	{
		*(array.buffer++) = charToInt(*s.c_str()) * 16 + charToInt(s[1]);
		s += 2;
	}

	return array;
}

int bytes::charToInt(char input)
{
  if(input >= '0' && input <= '9')
    return input - '0';
  if(input >= 'A' && input <= 'F')
    return input - 'A' + 10;
  if(input >= 'a' && input <= 'f')
    return input - 'a' + 10;
  throw std::invalid_argument("Invalid input string");
}

//FROM byte[] TO TYPE

short bytes::toInt16(byte_array array)
{
	return (array.buffer[0] << 8) | array.buffer[1];
}

int bytes::toInt24(byte_array array)
{
	return (array.buffer[0] << 16) | (array.buffer[1] << 8) | array.buffer[2];
}

int bytes::toInt32(byte_array array)
{
	return (array.buffer[0] << 24) | (array.buffer[1] << 16) | (array.buffer[2] << 8) | array.buffer[3];
}

long bytes::toInt64(byte_array array)
{
	return (array.buffer[0] << 56) | (array.buffer[1] << 48) | (array.buffer[2] << 40) |
			(array.buffer[3] << 32) | (array.buffer[4] << 24) | (array.buffer[5] << 16) |
			(array.buffer[6] << 8) | array.buffer[7];
}

rrsint32 bytes::toRrsInt32(byte_array array)
{
	int c = 0;
	unsigned int value = 0;
	unsigned char seventh;
	unsigned char msb;
	unsigned char b;

	binstream in(array);

	do
	{
		b = in.read();

		if(c == 0)
		{
			seventh = (b & 0x40) >> 6; //save 7th bit
			msb = (b & 0x80) >> 7; //save msb
			b = b << 1; //rotate to the left
			b = b & ~(0x181); //clear 8th and 1st bit and 9th if any
			b = b | (msb << 7) | (seventh); //insert msb and 6th back in
		}

		value |= (b & 0x7F) << (7 * c);
		c++;
	}
	while((b & 0x80) != 0);

	value = ((value >> 1) ^ -(value & 1));

	return *new rrsint32(c, value);
}

string bytes::toString(byte_array array)
{
	return string((char*)array.buffer);
}

/*
 * From https://codereview.stackexchange.com/questions/78535/
 */
string bytes::toHexString(byte_array array)
{
	char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	std::string s(array.len * 2, ' ');

	 for (int i = 0; i < array.len; ++i)
	 {
		 s[2 * i]     = hexmap[(array.buffer[i] & 0xF0) >> 4];
		 s[2 * i + 1] = hexmap[array.buffer[i] & 0x0F];
	 }

	 return s;
}
