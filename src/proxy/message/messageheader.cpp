/*
 * messageheader.cpp
 *
 *  Created on: 21/10/2017
 *      Author: filip
 */

#include "../../include/messageheader.hpp"
#include <cstring>
#include "../../include/logger.hpp"

messageheader::messageheader()
{}

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

	byte_array messageIdArray(byte::INT16_LENGTH);
	memcpy(messageIdArray.buffer, array.buffer, byte::INT16_LENGTH);
	header.messageId = byte::toInt16(messageIdArray);

	byte_array payloadLenArray(byte::INT24_LENGTH);
	memcpy(payloadLenArray.buffer, array.buffer + 2, byte::INT24_LENGTH);
	header.payloadLen = byte::toInt24(payloadLenArray);

	byte_array messageVersionArray(byte::INT16_LENGTH);
	memcpy(messageVersionArray.buffer, array.buffer + 5, byte::INT16_LENGTH);
	header.messageVersion = byte::toInt16(messageVersionArray);

	return header;
}

byte_array messageheader::array()
{
	byte_array array(HEADER_LENGTH);

	byte_array messageIdArray = byte::fromInt16(messageId);
	memcpy(array.buffer, messageIdArray.buffer, messageIdArray.len);
	free(messageIdArray.buffer);

	byte_array payloadLenArray = byte::fromInt24(payloadLen);
	memcpy(array.buffer + 2, payloadLenArray.buffer, payloadLenArray.len);
	free(payloadLenArray.buffer);

	byte_array messageVersionArray = byte::fromInt16(messageVersion);
	memcpy(array.buffer + 5, messageVersionArray.buffer, messageVersionArray.len);
	free(messageVersionArray.buffer);

	return array;
}
