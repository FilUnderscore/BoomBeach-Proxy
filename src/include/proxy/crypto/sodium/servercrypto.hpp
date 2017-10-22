/*
 * servercrypto.hpp
 *
 *  Created on: 22/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef INCLUDE_SERVERCRYPTO_HPP_
#define INCLUDE_SERVERCRYPTO_HPP_

#include "basecrypto.hpp"
#include "../../message/messagemap.hpp"

#include <string>

using namespace std;

class servercrypto : basecrypto
{
public:
	servercrypto(string magicKey);
	~servercrypto();
};

#endif /* INCLUDE_SERVERCRYPTO_HPP_ */
