/*
 * servercrypto.cpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#include "../../../include/servercrypto.hpp"

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

}

void basecrypto::encryptPacket(message message)
{

}
