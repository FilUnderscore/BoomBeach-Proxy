/*
 * servercrypto.cpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../../include/proxy/crypto/sodium/servercrypto.hpp"
#include <cstring>

servercrypto::servercrypto(string magicKey)
{
	if(magicKey.empty())
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

void basecrypto::decryptPacket(message message)
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

		memcpy(clientKey.buffer, message.getEncryptedPayload().buffer, 32);

		if(magicKey.len != 0)
		{
			sharedKey = magicKey;
		}
		else
		{
			sharedKey = *new byte_array(32);
			//Undefined reference?
			//crypto_box_beforenm(sharedKey.buffer, clientKey.buffer, privateKey.buffer);
		}

		nonce nc = *new nonce(clientKey, serverKey);


	}
	else
	{

	}
}

void basecrypto::encryptPacket(message message)
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
