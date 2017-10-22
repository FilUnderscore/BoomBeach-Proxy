/*
 * message.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_MESSAGE_MESSAGE_HPP_
#define PROXY_MESSAGE_MESSAGE_HPP_

#include "byte_array.hpp"
#include "messageheader.hpp"

class message
{
public:
	message(messageheader header);
	~message();

	messageheader getHeader();

	void setEncryptedPayload(byte_array encrypted);

	void setDecryptedPayload(byte_array decrypted);

	byte_array getEncryptedPayload();

	byte_array getDecryptedPayload();

protected:
	messageheader header;

	byte_array encryptedPayload;
	byte_array decryptedPayload;
};

#endif /* PROXY_MESSAGE_MESSAGE_HPP_ */
