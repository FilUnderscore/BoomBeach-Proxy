/*
 * message.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_MESSAGE_MESSAGE_HPP_
#define PROXY_MESSAGE_MESSAGE_HPP_

#include "messageheader.hpp"

class message
{
public:
	message(messageheader header);
	~message();

	messageheader getHeader();

	void setEncryptedPayload(char* encrypted);

	void setDecryptedPayload(char* decrypted);

	char* getEncryptedPayload();

	char* getDecryptedPayload();

protected:
	messageheader header;

	char* encryptedPayload;
	char* decryptedPayload;
};

#endif /* PROXY_MESSAGE_MESSAGE_HPP_ */
