/*
 * stringutil.hpp
 *
 *  Created on: 24/10/2017
 *      Author: filip
 */

#ifndef INCLUDE_PROXY_UTIL_STRINGUTIL_HPP_
#define INCLUDE_PROXY_UTIL_STRINGUTIL_HPP_

#include <string>
#include <vector>

using namespace std;

class stringutil
{
public:

	/*
	 * from https://stackoverflow.com/questions/16749069
	 */

	static vector<string> &split(const string &s, char delim, vector<string> &elems);

	static vector<string> split(const string &s, char delim);
};

#endif /* INCLUDE_PROXY_UTIL_STRINGUTIL_HPP_ */
