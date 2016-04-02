/**
* \file tcpacceptor.hpp
*
* \authors Sarah Scheffler //TODO: add yourself
*
* \brief Class for accepting TCP connections
*/

#ifndef TCPACCEPTOR_HPP_INCLUDED
#define TCPACCEPTOR_HPP_INCLUDED 1

#include <netinet/in.h>
#include "tcpstream.h"
 
 
class TCPAcceptor
{
    int socketDescriptor_;
    char* ipAddr_;
    int port_;

public:

    /// Constructor that takes in a port and IP address
    TCPAcceptor(int port, char* ipAddr);

    /// Destructor closes stream, if able
    ~TCPAcceptor();
 
    /// Start listening - call socket(), bind(), and listen()
    int start();

    /// Accept connection
    TCPStream* accept();
 
private:
    /// Prohibit default construction
    TCPAcceptor() {}
};