/*
 * servercrypto.cpp
 *
 *  Created on: 22/10/2017
 *      Author: filip
 */

#include "../../../include/servercrypto.hpp"

servercrypto::servercrypto(string magicKey)
{
	if(magicKey.empty())
	{
		this->magicKey = byte::fromHexString(magicKey);
	}
	else
	{
		//Patched hardcoded key
		this->privateKey = byte::fromHexString("1891d401fadb51d25d3a9174d472a9f691a45b974285d47729c45c6538070d85");
		this->serverKey = byte::fromHexString("72f1a4a4c48e44da0c42310f800e96624e6dc6a641a9d41c3b5039d8dfadc27e");
	}
}

void basecrypto::decryptPacket(message message)
{

}

void basecrypto::encryptPacket(message message)
{

}
