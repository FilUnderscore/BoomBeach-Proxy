/*
 * nonce.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_NONCE_HPP_
#define INCLUDE_NONCE_HPP_

/**
 * cant be named nonce otherwise interferes with c++ libraries.
 */
class nonce
{
private:
	unsigned char* bytes;
	int bytes_len;

public:
	nonce();
	nonce(unsigned char* nc, int nonce_len);
	nonce(unsigned char* clientKey, int client_key_len, unsigned char* serverKey, int server_key_len);
	nonce(unsigned char* clientKey, int client_key_len, unsigned char* serverKey, int server_key_len, unsigned char* nc, int nonce_len);

	void increment();

	unsigned char* getBytes();
};

#endif /* INCLUDE_NONCE_HPP_ */
