/*
 * binstream.hpp
 *
 *  Created on: 22/10/2017
 *      Author: filip
 */

#ifndef INCLUDE_PROXY_IO_BINSTREAM_HPP_
#define INCLUDE_PROXY_IO_BINSTREAM_HPP_

#include "../util/byte_array.hpp"
#include "../util/bytes.hpp"
#include "../util/rrsint32.hpp"

class binstream
{
public:
	binstream(byte_array array);

	unsigned char read();

	byte_array readArray();

	byte_array readArray(int length);

	string readString();

	string readZipString();

	short readShort();

	int readInt();

	long readLong();

	struct rrsint32 readRrsInt32();

	void seek(int pos);

protected:
	byte_array array;

	int position;
	int length;
};

#endif /* INCLUDE_PROXY_IO_BINSTREAM_HPP_ */
