/*
 * boutstream.cpp
 *
 *  Created on: 24/10/2017
 *      Author: filip
 */

#include "../../include/proxy/io/boutstream.hpp"
#include "../../include/proxy/util/byte_array.hpp"

#include <iostream>
#include <memory>
#include <sstream>

boutstream::boutstream()
{
	this->arr = new vector<byte>;
	this->position = 0;
	this->length = 0;
}

boutstream::~boutstream()
{
	this->arr->~vector();
}

void boutstream::write(byte b)
{
	this->arr->push_back(b);

	this->position++;
	this->length++;
}

void boutstream::writeArray(byte_array array)
{
	for(int bI = 0; bI < array.len; bI++)
	{
		write(array.buffer[bI]);
	}
}

void boutstream::writeArray(byte_array array, bool prefixed)
{
	if(prefixed)
		writeInt(array.len);

	writeArray(array);
}

void boutstream::writeString(string str)
{
	byte_array strArray = bytes::fromString(str);

	writeInt(strArray.len);
	writeArray(strArray);
}

void boutstream::writeZipString(string str)
{
	//TODO: Implement Zip Strings
}

void boutstream::writeShort(short s)
{
	writeArray(bytes::fromInt16(s));
}

void boutstream::writeInt(int i)
{
	writeArray(bytes::fromInt32(i));
}

void boutstream::writeLong(long l)
{
	writeArray(bytes::fromInt64(l));
}

void boutstream::writeRrsInt32(rrsint32 r)
{
	//TODO: Implement RrsInt32.
}

void boutstream::seek(int pos)
{
	if(pos > this->length)
		pos = this->length;

	this->position = pos;
}

byte_array boutstream::array()
{
	byte_array array(this->arr->size());

	for(int aI = 0; aI < this->arr->size(); aI++)
	{
		array.buffer[aI] = this->arr->at(aI);
	}

	return array;
}
