/*
 * stringutil.cpp
 *
 *  Created on: 24/10/2017
 *      Author: filip
 */

#include "../../include/proxy/util/stringutil.hpp"
#include <sstream>

vector<string> &stringutil::split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim))
	{
		if(item.length() > 0)
		{
			elems.push_back(item);
		}
	}

	return elems;
}

vector<string> stringutil::split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}
