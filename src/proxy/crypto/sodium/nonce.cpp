/*
 * nonce.cpp
 *
 *  Created on: 21/10/2017
 *      Author: filip
 */

#include <cstdlib>
#include <cstring>
#include <stdexcept>

#include "../../../include/nonce.hpp"

nonce::nonce()
{
	this->bytes = (unsigned char*) malloc(24);
}

nonce::nonce(unsigned char* nc, int nonce_len)
{
	this->bytes = nc;
	this->bytes_len = nonce_len;
}

nonce::nonce(unsigned char* clientKey, int client_key_len, unsigned char* serverKey, int server_key_len) : nonce(clientKey, client_key_len, serverKey, server_key_len, NULL, 0)
{}

extern "C"
{
	#include "../blake2/blake2b.h"
}

nonce::nonce(unsigned char* clientKey, int client_key_len, unsigned char* serverKey, int server_key_len, unsigned char* nc, int nonce_len)
{
	blake2b_ctx ctx;

	if(blake2b_init(&ctx, 24, NULL, 0))
		throw std::runtime_error("Failed to initialize blake2b.");

	if(nc != NULL)
		blake2b_update(&ctx, nc, nonce_len);

	blake2b_update(&ctx, clientKey, client_key_len);
	blake2b_update(&ctx, serverKey, server_key_len);

	blake2b_final(&ctx, this->bytes);
	this->bytes_len = 24;
}

void nonce::increment()
{
	unsigned char buffer[byte::INT16_LENGTH];
	memcpy(buffer, this->bytes, byte::INT16_LENGTH);

	short s = byte::toInt16(buffer);

	s += 2;

	unsigned char* shortBuffer = byte::fromInt16(s);

	this->bytes[0] = shortBuffer[0];
	this->bytes[1] = shortBuffer[1];
}

unsigned char* nonce::getBytes()
{
	return this->bytes;
}
