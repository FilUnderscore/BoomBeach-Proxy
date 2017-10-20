/*
 * messages.hpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#ifndef PROXY_MESSAGE_MESSAGES_HPP_
#define PROXY_MESSAGE_MESSAGES_HPP_

class messages
{
public:
	/* Client - Authentication */
	static const short CLIENT_HELLO = 10100;
	static const short CLIENT_LOGIN = 10101;

	/* Server - Authentication */
	static const short SERVER_HELLO = 20100;
	static const short SERVER_LOGIN_BAD = 20103;
	static const short SERVER_LOGIN_OK = 20104;
};

#endif /* PROXY_MESSAGE_MESSAGES_HPP_ */
