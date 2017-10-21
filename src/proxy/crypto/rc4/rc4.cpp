/*
 * rc4.cpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

/*
 * ported to C++, from Java at
 * https://github.com/SC-DevTeam/Pinocchio/blob/master/src/com/scdevteam/crypto/rc4/RC4.java
 */

#include "../../../include/rc4.hpp"

#include <cstdlib>

rc4::rc4(unsigned char* key, int key_len)
{
	this->state = (unsigned char*) malloc(256);

	this->setKey(key, key_len);
}

rc4::~rc4()
{

}

void rc4::setKey(unsigned char* key, int key_len)
{
	x = y = 0;

	for(int i = 0; i < 256; i++)
	{
		state[i] = (unsigned char) i;
	}

	for(int i = 0, j = 0, k = 0; i < 256; i++)
	{
		k = (key[j] + state[i] + k) & 0xFF;

		unsigned char temp = state[i];
		state[i] = state[k];
		state[k] = temp;

		j = (j + 1) % key_len;
	}
}

unsigned char* rc4::encrypt(unsigned char* clearText, int clear_text_len)
{
	unsigned char* cipherText = (unsigned char*) malloc(clear_text_len);

	for(int i = 0; i < clear_text_len; i++)
	{
		cipherText[i] = (unsigned char) (clearText[i] ^ state[next()]);
	}

	return cipherText;
}

int rc4::next()
{
	unsigned char temp;

	x = (x + 1) & 0xFF;
	y = (y + state[x]) & 0xFF;

	temp = state[x];
	state[x] = state[y];
	state[y] = temp;

	return (state[x] + state[y]) & 0xFF;
}

unsigned char* rc4::generate(int length)
{
	unsigned char* key = (unsigned char*) malloc(length);

	for(int i = 0; i < length; i++)
	{
		key[i] = (unsigned char) next();
	}
}

void rc4::skip(int length)
{
	for(int i = 0; i < length; i++)
	{
		next();
	}
}
