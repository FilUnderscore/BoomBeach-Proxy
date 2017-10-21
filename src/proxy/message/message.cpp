/*
 * message.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../include/message.hpp"

message::message(messageheader header)
{
	this->header = header;
}

messageheader message::getHeader()
{
	return this->header;
}

void message::setEncryptedPayload(char* encrypted)
{
	this->encryptedPayload = encrypted;
}

void message::setDecryptedPayload(char* decrypted)
{
	this->decryptedPayload = decrypted;
}

char* message::getEncryptedPayload()
{
	return this->encryptedPayload;
}

char* message::getDecryptedPayload()
{
	return this->decryptedPayload;
}
