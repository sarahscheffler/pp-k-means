#include <zmq.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const string clientPrefix="tcp://localhost:";
const string serverPrefix="tcp://*:";
const int dataSize=9;
const string genericData="publicKey";

int procNumber, totalProcs;
int basePort=8000;
int broadcastPort=7000;
zmq::socket_t *reqSocket, *repSocket;
zmq::socket_t **broadSockets;

string s_recv (zmq::socket_t *socket) {

    zmq::message_t request;
    socket->recv(&request);
    return string(static_cast<char*>(request.data()), request.size());
}

void s_send (zmq::socket_t *socket, string send) {

    zmq::message_t request(send.length());
    memcpy(request.data(), send.c_str(), send.length());
    socket->send(request);
}

vector<int> getAddShares(int in)  
{
    string resp;
    if(procNumber) {
        cout<<"Received "<<s_recv(broadSockets[0])<<endl;

        resp = s_recv(repSocket,genericData);
        // multiply encrypted input by waht we just got
        s_send(reqSocket, genericData);
        resp = s_recv(reqSocket)

        //select a random share 
        s_send(broadSockets[0],genericData); //send share back to p1
        s_send(repSocket, genericData); //send something backwards

        resp = s_recv(broadSockets[0]); 

    } else {
        //send public key e to all parties
        for(int i=0; i<(totalProcs-1); i++) {
            s_send(broadSockets[i],genericData);
        }

        s_send(reqSocket, genericData); //send encrypted x1

        for(int i=0; i<(totalProcs-1); i++) {
            resp=s_recv(broadSockets[i]); // collect all the shares
        }

        resp = s_recv(reqSocket); 
        //now compute its own share. We know all shares now

        for(int i=0; i<(totalProcs-1); i++) {
            s_send(broadSockets[i],genericData); //send all shares
            //resp=s_recv(broadSockets[i]); // receive acknowledgement
        }
    }
    return vector<int>();
}

int main (int argc, char* argv[])
{
    procNumber = atoi(argv[1]);
    totalProcs =atoi(argv[2]);
    if(argc>3) {
        basePort=atoi(argv[3]);
        broadcastPort=basePort+10;
    }

    cout<<"Starting "<<procNumber<<" "<<totalProcs<<endl;

    zmq::context_t context (1);
    reqSocket = new zmq::socket_t (context, ZMQ_REQ);
    repSocket = new zmq::socket_t (context, ZMQ_REP);

    //cout<<clientPrefix+to_string(basePort+procNumber+1)<<" "<<serverPrefix+to_string(basePort+procNumber)<<endl;

    reqSocket->connect(clientPrefix+to_string(basePort+procNumber+1));
    repSocket->bind(serverPrefix+to_string(basePort+procNumber));


    if(procNumber) {
        broadSockets = new zmq::socket_t*[1];
        broadSockets[0] = new zmq::socket_t (context, ZMQ_REP);
        broadSockets[0]->bind(serverPrefix+to_string(broadcastPort+procNumber));
    } else {
        broadSockets = new zmq::socket_t*[totalProcs-1];
        for(int i=1;i<totalProcs;i++) {
            broadSockets[i-1] = new zmq::socket_t (context, ZMQ_REQ);
            broadSockets[i-1]->connect(clientPrefix+to_string(broadcastPort+i));
        }
    }

    usleep(2000000);
    getAddShares(0);

/*
    reqSocket->close();
    repSocket->unbind(serverPrefix+to_string(basePort+procNumber));
    if(procNumber) broadSockets[0]->unbind(serverPrefix+to_string(broadcastPort+procNumber));
    else for(int i=1;i<totalProcs;i++) broadSockets[i-1]->close();
    */

    return 0;
} 