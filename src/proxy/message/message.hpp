/*
 * message.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_MESSAGE_MESSAGE_HPP_
#define PROXY_MESSAGE_MESSAGE_HPP_

class message
{
public:
	message(short messageID, int payloadLen, short messageVersion, char* payload);

	void setEncryptedPayload(char* encrypted);

	void setDecryptedPayload(char* decrypted);

protected:
	short messageID;
	int payloadLen;
	short messageVersion;

	char* encryptedPayload;
	char* decryptedPayload;
};

#endif /* PROXY_MESSAGE_MESSAGE_HPP_ */
