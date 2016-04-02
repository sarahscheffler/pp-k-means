/**
* \file client.hpp
* \author Sarah Scheffler and //TODO ADD YOURSELVES
*
* \brief Client header file
*/

#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED 1

#include "globals.hpp"
#include "datamanager.hpp"
#include <vector>

/**
* \class Client
*
* \brief A client that performs privacy-preserving horizontally-partitioned k-means
*
* \details A Client first tells a Server what it wants to do.  It then listens to the Server until
* the server tells them what to do, and it then listens to its preceding client for inputs to
* MultiPartyAdditionForward, sends its output to its following client, then listens to its following
* client for input to MultiPartyAdditionBackward, then sends its output to the preceding client.
* It then listens to the server again to learn what its next step is, either doing another
* MultiPartyAddition or learning the final means.
*/
class Client {

	const DataManager* dataManager_; // also used to check agreements
	const char[] selfIdentity_; // the client's own identity //TODO: const chars themselves, not just pointer?
	vector<char*> identities_; // list of all clients


public:

    /// decide on number of parties, get data, find server info, etc
	void initialize(); 

    /// get connection to server
    TCPConnector* connect(int port, const char* server); // take in server name and port,
                                                         // return TCP stream object


   

    


};
