/*
 * nonce.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_NONCE_HPP_
#define INCLUDE_NONCE_HPP_

class nonce
{
private:
	unsigned char* bytes;

public:
	nonce();
	nonce(unsigned char* nonce);
	nonce(unsigned char* clientKey, unsigned char* serverKey);
	nonce(unsigned char* clientKey, unsigned char* serverKey, unsigned char* nonce);

	void increment();

	unsigned char* getBytes();
};

#endif /* INCLUDE_NONCE_HPP_ */
