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

messageheader messageheader::parse(unsigned char* buffer)
{
	messageheader header;

	unsigned char messageIdBuffer[byte::INT16_LENGTH];
	memcpy(messageIdBuffer, buffer, byte::INT16_LENGTH);
	header.messageId = byte::toInt16(messageIdBuffer);

	unsigned char payloadLenBuffer[byte::INT24_LENGTH];
	memcpy(payloadLenBuffer + 1, buffer + 2, byte::INT24_LENGTH);
	header.payloadLen = byte::toInt24(payloadLenBuffer);

	unsigned char messageVersionBuffer[byte::INT16_LENGTH];
	memcpy(messageVersionBuffer, buffer + 5, byte::INT16_LENGTH);
	header.messageVersion = byte::toInt16(messageVersionBuffer);

	return header;
}

unsigned char* messageheader::array()
{
	unsigned char* buffer = (unsigned char*)malloc(HEADER_LENGTH);

	unsigned char* messageIdBuffer = byte::fromInt16(messageId);
	memcpy(buffer, messageIdBuffer, byte::INT16_LENGTH);
	free(messageIdBuffer);

	unsigned char* payloadLenBuffer = byte::fromInt24(payloadLen);
	memcpy(buffer + 2, byte::fromInt24(payloadLen) + 1, byte::INT24_LENGTH);
	free(payloadLenBuffer);

	unsigned char* messageVersionBuffer = byte::fromInt16(messageVersion);
	memcpy(buffer + 5, byte::fromInt16(messageVersion), byte::INT16_LENGTH);
	free(messageVersionBuffer);

	return buffer;
}
