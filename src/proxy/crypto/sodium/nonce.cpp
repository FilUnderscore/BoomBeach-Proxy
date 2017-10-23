/*
 * nonce.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#include <cstdlib>
#include <cstring>
#include <stdexcept>

#include "../../../include/proxy/crypto/sodium/nonce.hpp"

nonce::nonce()
{
	this->bytes = *new byte_array(NONCE_LENGTH);
}

nonce::nonce(byte_array nonce)
{
	this->bytes = nonce;
}

nonce::nonce(byte_array clientKey, byte_array serverKey) : nonce(clientKey, serverKey, *new byte_array())
{}

extern "C"
{
	#include "../blake2/blake2b.h"
}

nonce::nonce(byte_array clientKey, byte_array serverKey, byte_array nonce) : nonce::nonce()
{
	blake2b_ctx ctx;

	if(blake2b_init(&ctx, this->bytes.len, NULL, 0))
		throw std::runtime_error("Failed to initialize blake2b.");

	if(nonce.len > 0)
		blake2b_update(&ctx, nonce.buffer, nonce.len);

	blake2b_update(&ctx, clientKey.buffer, clientKey.len);
	blake2b_update(&ctx, serverKey.buffer, serverKey.len);

	blake2b_final(&ctx, this->bytes.buffer);
}

void nonce::increment()
{
	byte_array array(bytes::INT16_LENGTH);

	memcpy(array.buffer, this->bytes.buffer, array.len);

	short s = bytes::toInt16(array);

	s += 2;

	byte_array shortBuffer = bytes::fromInt16(s);

	this->bytes.buffer[0] = shortBuffer.buffer[0];
	this->bytes.buffer[1] = shortBuffer.buffer[1];

	free(shortBuffer.buffer);
}

byte_array nonce::getBytes()
{
	return this->bytes;
}
