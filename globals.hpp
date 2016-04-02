/**
* globals.hpp - global variable definitions
*/

#ifndef GLOBALS_HPP_INCLUDED
#define GLOBALS_HPP_INCLUDED 1

#define SERVER_IP "127.0.0.1" // server IP address

#define SERVER_PORT "22222" // port where server is listening for new requests

#define PACKET_SIZE 256 // number of bytes in a packet

#define CLOSE_STREAM "CLOSE_STREAM" // the packet to send when you want to close the stream

#define ORDER "ORDER" // the thing that signals the start of the server sending the order
#define END_ORDER "END_ORDER"

#define ENC_KEY "ENC_KEY" // the thing that signals the start of the server sending the enc key
#define END_ENC_KEY "END_ENC_KEY"

#define MEANS "MEANS" // start of the server sending the updated list of means
#define END_MEANS "END_MEANS"

#define COMPLETE "COMPLETE" // signal that the protocol is done and the current means are correct

