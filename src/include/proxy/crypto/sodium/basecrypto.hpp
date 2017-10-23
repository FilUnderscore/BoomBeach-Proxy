/*
 * basecrypto.hpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_BASECRYPTO_HPP_
#define INCLUDE_BASECRYPTO_HPP_

#include "../../util/byte_array.hpp"
#include "nonce.hpp"
#include "../../message/message.hpp"

#include "../../../../proxy/crypto/tweetnacl/tweetnacl.h"

class basecrypto
{
public:
	static const int KEY_LENGTH = 32;

	basecrypto();
	~basecrypto();

	byte_array encrypt(byte_array message)
	{
		return this->encrypt(message, NULL);
	}

	byte_array encrypt(byte_array message, nonce* nonce)
	{
		if(nonce == NULL)
		{
			encryptNonce.increment();
			nonce = &encryptNonce;
		}

		byte_array ciphertext(message.len);

		crypto_box_afternm(ciphertext.buffer, message.buffer, message.len, nonce->getBytes().buffer, sharedKey.buffer);

		return ciphertext;
	}

	byte_array decrypt(byte_array ciphertext)
	{
		return this->decrypt(ciphertext, NULL);
	}

	byte_array decrypt(byte_array ciphertext, nonce* nonce)
	{
		if(nonce == NULL)
		{
			decryptNonce.increment();
			nonce = &decryptNonce;
		}

		byte_array message(ciphertext.len);

		crypto_box_open_afternm(message.buffer, ciphertext.buffer, ciphertext.len, nonce->getBytes().buffer, sharedKey.buffer);

		return message;
	}

	void decryptPacket(message message);
	void encryptPacket(message message);

protected:
	byte_array privateKey;
	byte_array serverKey;
	byte_array clientKey;
	byte_array sharedKey;

	nonce decryptNonce;
	nonce encryptNonce;

	byte_array sessionKey;

	/**
	 * For new encryption
	 */
	byte_array magicKey;
};

#endif /* INCLUDE_BASECRYPTO_HPP_ */
