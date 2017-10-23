/*
 * servercrypto.cpp
 *
 *  Created on: 23/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../../include/proxy/crypto/sodium/servercrypto.hpp"

basecrypto::basecrypto(){}
basecrypto::~basecrypto(){}

servercrypto::servercrypto(string magicKey)
{
	if(!magicKey.empty())
	{
		this->magicKey = bytes::fromHexString(magicKey);
	}
	else
	{
		//Patched hardcoded key
		this->privateKey = bytes::fromHexString("1891d401fadb51d25d3a9174d472a9f691a45b974285d47729c45c6538070d85");
		this->serverKey = bytes::fromHexString("72f1a4a4c48e44da0c42310f800e96624e6dc6a641a9d41c3b5039d8dfadc27e");
	}
}

servercrypto::~servercrypto()
{

}

void servercrypto::decryptPacket(message message)
{
	if(message.getHeader().getId() == messagemap::getId("ClientHello"))
	{
		if(magicKey.len != 0)
		{
			serverKey = bytes::fromHexString("");
		}

		message.setDecryptedPayload(message.getEncryptedPayload());
	}
	else if(message.getHeader().getId() == messagemap::getId("ClientLogin"))
	{
		clientKey = *new byte_array(32);

		memcpy(clientKey.buffer, message.getEncryptedPayload().buffer, KEY_LENGTH);

		if(magicKey.len != 0)
		{
			sharedKey = magicKey;
		}
		else
		{
			sharedKey = *new byte_array(KEY_LENGTH);

			crypto_box_beforenm(sharedKey.buffer, clientKey.buffer, privateKey.buffer);
		}

		nonce* nc = new nonce(clientKey, serverKey);

		byte_array payload(message.getEncryptedPayload().len);
		memcpy(payload.buffer, message.getEncryptedPayload().buffer + KEY_LENGTH, message.getEncryptedPayload().len);

		byte_array deciphered = decrypt(payload, nc);

		byte_array sessionKeyArray(nonce::NONCE_LENGTH);
		memcpy(sessionKeyArray.buffer, deciphered.buffer, nonce::NONCE_LENGTH);

		byte_array decryptEncryptNonceArray(nonce::NONCE_LENGTH);
		memcpy(decryptEncryptNonceArray.buffer, deciphered.buffer + nonce::NONCE_LENGTH, nonce::NONCE_LENGTH);

		decryptNonce = *new nonce(decryptEncryptNonceArray);
		//TODO: Client Crypto
		//proxy.client.crypto.encryptNonce = new nonce(decryptEncryptNonceArray);

		byte_array decryptedPayloadArray(deciphered.len - (nonce::NONCE_LENGTH * 2));
		memcpy(decryptedPayloadArray.buffer, deciphered.buffer + (nonce::NONCE_LENGTH * 2), decryptedPayloadArray.len);

		message.setDecryptedPayload(decryptedPayloadArray);
	}
	else
	{
		message.setDecryptedPayload(decrypt(message.getEncryptedPayload()));
	}
}

void servercrypto::encryptPacket(message message)
{
	if(message.getHeader().getId() == messagemap::getId("ServerHello")
	|| message.getHeader().getId() == messagemap::getId("ServerLoginBad"))
	{
		message.setEncryptedPayload(message.getDecryptedPayload());
	}
	else if(message.getHeader().getId() == messagemap::getId("ServerLoginOk"))
	{

	}
	else
	{

	}
}
