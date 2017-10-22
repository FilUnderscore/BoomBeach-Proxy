/*
 * message.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/proxy/message/message.hpp"

message::message(messageheader header)
{
	this->header = header;
}

message::~message()
{

}

messageheader message::getHeader()
{
	return this->header;
}

void message::setEncryptedPayload(byte_array encrypted)
{
	this->encryptedPayload = encrypted;
}

void message::setDecryptedPayload(byte_array decrypted)
{
	this->decryptedPayload = decrypted;
}

byte_array message::getEncryptedPayload()
{
	return this->encryptedPayload;
}

byte_array message::getDecryptedPayload()
{
	return this->decryptedPayload;
}
