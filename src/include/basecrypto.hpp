/*
 * basecrypto.hpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_BASECRYPTO_HPP_
#define INCLUDE_BASECRYPTO_HPP_

#include "nonce.hpp"
#include "message.hpp"

#include "../proxy/crypto/tweetnacl/tweetnacl.h"

class basecrypto
{
public:
	unsigned char* encrypt(unsigned char* message, int message_len)
	{
		return this->encrypt(message, message_len, NULL);
	}

	unsigned char* encrypt(unsigned char* message, int message_len, nonce* nonce)
	{
		if(nonce == NULL)
		{
			encryptNonce.increment();
			nonce = &encryptNonce;
		}

		unsigned char* cipher;

		crypto_box_afternm(cipher, message, message_len, nonce->getBytes(), sharedKey);

		return cipher;
	}

	unsigned char* decrypt(unsigned char* ciphertext, int ciphertext_len)
	{
		return this->decrypt(ciphertext, ciphertext_len, NULL);
	}

	unsigned char* decrypt(unsigned char* ciphertext, int ciphertext_len, nonce* nonce)
	{
		if(nonce == NULL)
		{
			decryptNonce.increment();
			nonce = &decryptNonce;
		}

		unsigned char* message;

		crypto_box_open_afternm(message, ciphertext, ciphertext_len, nonce->getBytes(), sharedKey);

		return message;
	}

	virtual void decryptPacket(message message);
	virtual void encryptPacket(message message);

protected:
	unsigned char* privateKey;
	unsigned char* serverKey;
	unsigned char* clientKey;
	unsigned char* sharedKey;

	nonce decryptNonce;
	nonce encryptNonce;

	unsigned char* sessionKey;

	/**
	 * For new encryption
	 */
	unsigned char* magicKey;
};

#endif /* INCLUDE_BASECRYPTO_HPP_ */
