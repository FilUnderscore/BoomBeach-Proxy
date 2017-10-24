/*
 * bytearray.hpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_BYTE_ARRAY_HPP_
#define INCLUDE_BYTE_ARRAY_HPP_

#include <string>
#include <string.h>
#include <cstdlib>

#include "byte.hpp"

struct byte_array
{
	byte* buffer;
	int len;

	byte_array() : byte_array(0) {}

	byte_array(int array_len) : byte_array((byte*)malloc(array_len), array_len) {}

	byte_array(byte* buffer, int array_len)
	{
		this->buffer = buffer;
		this->len = array_len;
	}
};

#endif /* INCLUDE_BYTE_ARRAY_HPP_ */
