/*
 * messageheader.cpp
 *
 *  Created on: 21/10/2017
 *      Author: filip
 */

#include "../../include/proxy/message/messageheader.hpp"
#include <cstring>
#include "../../include/logger/logger.hpp"

messageheader::messageheader()
{
	this->messageId = -1;
	this->payloadLen = -1;
	this->messageVersion = -1;
}

messageheader::messageheader(short messageId, int payloadLen, short messageVersion)
{
	this->messageId = messageId;
	this->payloadLen = payloadLen;
	this->messageVersion = messageVersion;
}

messageheader::~messageheader()
{
}

short messageheader::getId()
{
	return this->messageId;
}

int messageheader::getPayloadLength()
{
	return this->payloadLen;
}

short messageheader::getVersion()
{
	return this->messageVersion;
}

messageheader messageheader::parse(byte_array array)
{
	messageheader header;

	byte_array messageIdArray(bytes::INT16_LENGTH);
	memcpy(messageIdArray.buffer, array.buffer, bytes::INT16_LENGTH);
	header.messageId = bytes::toInt16(messageIdArray);

	byte_array payloadLenArray(bytes::INT24_LENGTH);
	memcpy(payloadLenArray.buffer, array.buffer + 2, bytes::INT24_LENGTH);
	header.payloadLen = bytes::toInt24(payloadLenArray);

	byte_array messageVersionArray(bytes::INT16_LENGTH);
	memcpy(messageVersionArray.buffer, array.buffer + 5, bytes::INT16_LENGTH);
	header.messageVersion = bytes::toInt16(messageVersionArray);

	return header;
}

byte_array messageheader::array()
{
	byte_array array(HEADER_LENGTH);

	byte_array messageIdArray = bytes::fromInt16(messageId);
	memcpy(array.buffer, messageIdArray.buffer, messageIdArray.len);
	free(messageIdArray.buffer);

	byte_array payloadLenArray = bytes::fromInt24(payloadLen);
	memcpy(array.buffer + 2, payloadLenArray.buffer, payloadLenArray.len);
	free(payloadLenArray.buffer);

	byte_array messageVersionArray = bytes::fromInt16(messageVersion);
	memcpy(array.buffer + 5, messageVersionArray.buffer, messageVersionArray.len);
	free(messageVersionArray.buffer);

	return array;
}
