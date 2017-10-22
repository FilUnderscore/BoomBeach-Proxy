/*
 * main.cpp
 *
 *  Created on: 20/10/2017
 *      Author: Filip Jerkovic
 */

#include "include/proxy/proxy.hpp"

/*
 * argc - argument count
 * argv - argument variables
 */
int main(int argc, char** argv)
{
	//Starts the proxy with the default Supercell Game Server Port

	//Log to file, uncomment.
	//logger::file("proxy.log");
	proxy::init(proxy::DEFAULT_HOST, proxy::DEFAULT_PORT);

	return 0;
}
