/*
 * nonce.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_NONCE_HPP_
#define INCLUDE_NONCE_HPP_

#include "bytes.hpp"

class nonce
{
private:
	byte_array bytes;
	int bytes_len;

public:
	nonce();
	nonce(byte_array nonce);
	nonce(byte_array clientKey, byte_array serverKey);
	nonce(byte_array clientKey, byte_array serverKey, byte_array nonce);

	void increment();

	byte_array getBytes();
};

#endif /* INCLUDE_NONCE_HPP_ */
