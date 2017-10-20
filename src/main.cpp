/*
 * main.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "proxy.hpp"

/*
 * argc - argument count
 * argv - argument variables
 */
int main(int argc, char** argv)
{
	//Starts the proxy with the default Supercell Game Server Port
	proxy proxy(proxy::DEFAULT_PORT);

	return 0;
}
