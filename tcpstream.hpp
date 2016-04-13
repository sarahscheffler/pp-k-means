/**
* \file tcpstream.hpp
*
* \authors Sarah Scheffler //TODO: add yourself
* 
* \brief Main class for live TCP streams - per each connection, one of these is created by
* the server, and one is created by the connecting client
*/

#ifndef TCPSTREAM_HPP_INCLUDED
#define TCPSTREAM_HPP_INCLUDED 1

#include <sys/types.h> // for ssize_t
#include <sys/socket.h> // defines sockaddr_in
 
using namespace std
 
class TCPStream 
{
    int socketDescriptor_;
    int ipAddr_; // ip address of OTHER party
    int port_; // port connection of OTHER party
 
 public:
    friend class TCPAcceptor;
    friend class TCPConnector;
 
    /// Destructor
    ~TCPStream(); // will call close(socketDescriptor_)
 
    /// Send data to the stream
    ssize_t send(char* buffer, size_t len); // will call write() and return number bytes written 
                                            // (or negative for error)

    /// Receive data from the stream
    ssize_t receive(char* buffer, size_t len); // will call read() and return number bytes read
                                               // (or negative for error)

    /// Signal to the other party that you are closing the stream, then close the stream
    int close(); 

  private:

    /// Prohibit construction except by friends
    TCPStream(int socketDescriptor, struct sockaddr_in* address); // assume IPv4 for now

    /// Default constructor should not be used
    TCPStream();

    /// Copy constructor
    TCPStream(const TCPStream& stream);
};