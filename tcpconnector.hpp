/**
* \file tcpconnector.hpp
*
* \authors Sarah Scheffler //TODO: add yourself
*
* \brief Class for a client to connect to a server
*/

#ifndef TCPCONNECTOR_HPP_INCLUDED
#define TCPCONNECTOR_HPP_INCLUDED 1

#include <netinet/in.h>
#include "tcpstream.hpp"
 
class TCPConnector
{

public:
	/// Connect to TCP Stream
    TCPStream* connect(int port, const char* server); // take in server name and port,
                                                      // return TCP stream object
};