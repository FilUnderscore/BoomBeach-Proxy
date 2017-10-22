/*
 * messageheader.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_MESSAGEHEADER_HPP_
#define INCLUDE_MESSAGEHEADER_HPP_

#include "../util/bytes.hpp"

class messageheader
{
public:
	static const int HEADER_LENGTH = 7;

	messageheader();
	messageheader(short messageId, int payloadLen, short messageVersion);
	~messageheader();

	short getId();
	int getPayloadLength();
	short getVersion();

	static messageheader parse(byte_array array);

	byte_array array();
protected:
	short messageId;
	int payloadLen;
	short messageVersion;
};

#endif /* INCLUDE_MESSAGEHEADER_HPP_ */
