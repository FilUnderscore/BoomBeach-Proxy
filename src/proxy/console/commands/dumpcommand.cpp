/*
 * dumpcommand.cpp
 *
 *  Created on: 24/10/2017
 *      Author: filip
 */

#include "../../../include/proxy/console/commands/dumpcommand.hpp"
#include "../../../include/logger/logger.hpp"

//TODO: Testing
#include "../../../include/proxy/network/client.hpp"
#include "../../../include/proxy/proxy.hpp"

void dumpcommand::execute(vector<string> args)
{
	if(args.size() <= 0)
	{
		vector<client>* clientList = proxy::getProxy().getNetwork()->getClients();

		if(clientList->size() > 0)
		{
			for(vector<client>::iterator cli = clientList->begin(); cli < clientList->end(); cli++)
			{
				client client = *cli;

				vector<message> messageHistory = client.getMessageHistory();

				if(messageHistory.size() > 0)
				{
					logger::log("<DUMP> Please select an index to dump.");

					for(int mI = 0; mI < messageHistory.size(); mI++)
					{
						message msg = messageHistory.at(mI);

						logger::log("<DUMP> " + to_string(mI) + " : " + to_string(msg.getHeader().getId()));
					}
				}
				else
				{
					logger::log("<DUMP> Client " + to_string(client.getSocket().getSocketId()) + " does not have any history.");
				}
			}
		}
		else
		{
			logger::log("<DUMP> No clients are currently connected.");
		}
	}
	else
	{

	}
}
