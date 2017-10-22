/*
 * binstream.cpp
 *
 *  Created on: 22/10/2017
 *      Author: filip
 */

#include "../../include/proxy/io/binstream.hpp"

binstream::binstream(byte_array array)
{
	this->position = 0;
	this->array = array;
	this->length = array.len;
}

unsigned char binstream::read()
{
	if(this->position >= this->length)
		return 0;

	return this->array.buffer[this->position++];
}

byte_array binstream::readArray()
{
	int length = readInt();

	return readArray(length);
}

byte_array binstream::readArray(int length)
{
	byte_array array(length);

	for(int index = 0; index < length; index++)
	{
		array.buffer[index] = read();
	}

	return array;
}

string binstream::readString()
{
	int length = readInt();

	if(length == 0xFFFFFFFF)
	{
		throw std::runtime_error("String has invalid length.");
	}

	return bytes::toString(readArray(length));
}

string binstream::readZipString()
{
	//TODO: Implement zip strings using zlib
	throw std::runtime_error("Zip string not implemented.");
}

short binstream::readShort()
{
	return bytes::toInt16(readArray(bytes::INT16_LENGTH));
}

int binstream::readInt()
{
	return bytes::toInt32(readArray(bytes::INT32_LENGTH));
}

long binstream::readLong()
{
	return bytes::toInt64(readArray(bytes::INT64_LENGTH));
}

rrsint32 binstream::readRrsInt32()
{
	return bytes::toRrsInt32(readArray());
}

void binstream::seek(int pos)
{
	if(pos > this->length)
		pos = this->length;

	this->position = pos;
}
