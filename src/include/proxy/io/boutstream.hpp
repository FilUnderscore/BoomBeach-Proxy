/*
 * boutstream.hpp
 *
 *  Created on: 24/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_PROXY_IO_BOUTSTREAM_HPP_
#define INCLUDE_PROXY_IO_BOUTSTREAM_HPP_

#include "../util/bytes.hpp"

#include <vector>

class boutstream
{
public:
	boutstream();
	~boutstream();

	void write(byte b);

	void writeArray(byte_array array);

	void writeArray(byte_array array, bool prefixed);

	void writeString(string str);

	void writeZipString(string str);

	void writeShort(short s);

	void writeInt(int i);

	void writeLong(long l);

	void writeRrsInt32(rrsint32 r);

	void seek(int pos);

	byte_array array();

protected:
	int position;
	int length;

	vector<byte>* arr;
};

#endif /* INCLUDE_PROXY_IO_BOUTSTREAM_HPP_ */
