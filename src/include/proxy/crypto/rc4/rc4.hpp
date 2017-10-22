/*
 * rc4.hpp
 *
 *  Created on: 21/10/2017
 *      Author: Filip Jerkovic
 */

/*
 * ported to C++, from Java at
 * https://github.com/SC-DevTeam/Pinocchio/blob/master/src/com/scdevteam/crypto/rc4/RC4.java
 */

#ifndef INCLUDE_RC4_HPP_
#define INCLUDE_RC4_HPP_

class rc4
{
public:
	rc4(unsigned char* key, int key_len);

	~rc4();

	void setKey(unsigned char* key, int key_len);

	unsigned char* encrypt(unsigned char* clearText, int clear_text_len);

	unsigned char* generate(int length);

	void skip(int length);

private:
	unsigned char* state;
	int x, y;

	int next();
};

#endif /* INCLUDE_RC4_HPP_ */
