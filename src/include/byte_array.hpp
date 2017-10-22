/*
 * bytearray.hpp
 *
 *  Created on: 22/10/2017
 *      Author: filip
 */

#ifndef INCLUDE_BYTE_ARRAY_HPP_
#define INCLUDE_BYTE_ARRAY_HPP_

#include <string>
#include <string.h>
#include <cstdlib>

struct byte_array
{
	unsigned char* buffer;
	int len;

	byte_array()
	{

	}

	byte_array(int array_len) : byte_array((unsigned char*)malloc(array_len), array_len) {}

	byte_array(unsigned char* buffer, int array_len)
	{
		this->buffer = buffer;
		this->len = array_len;
	}
};

#endif /* INCLUDE_BYTE_ARRAY_HPP_ */
