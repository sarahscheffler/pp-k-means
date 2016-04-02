/**
* \file server.hpp
* \author Sarah Scheffler and //TODO ADD YOURSELVES
*
* \brief Server header file
*/

#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED 1

#include "globals.hpp"
#include "datamanager.hpp"
#include <set>
#include <utility> // for pair

/**
* \class Server
*
* \brief A server that helps many clients perform privacy-preserving horizontally-partitioned 
* k-means
*
* \details A server first listens to clients attempting to connect to it and learns their
* Agreement information.  When all clients agree, the protocol is started.  It randomly selects
* initial means (within the bounds agreed upon by the clients)
*/
class Server {

    /// When the clients agree with each other, write parameters in the data manager
	DataManager* dataManager_;

	/// Ordered list of clients for this iteration; call random_shuffle to randomize it
	vector<Client> participatingClients_;

	unsigned char[] encKey_;
	unsigned char[] decKey_;


public:

    /// create listener 
    TCPAcceptor* getClientConnection();

private:

	void setNewKeys(); // set encKey, decKey to new keypair
   

};
