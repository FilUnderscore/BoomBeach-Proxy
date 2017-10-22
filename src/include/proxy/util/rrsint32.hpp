/*
 * rrsint32.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_RRSINT32_HPP_
#define INCLUDE_RRSINT32_HPP_

#include "../io/binstream.hpp"

struct rrsint32
{
	int length;
	unsigned int value;

	rrsint32(int length, long value)
	{
		this->length = length;
		this->value = value;
	}
};

#endif /* INCLUDE_RRSINT32_HPP_ */
