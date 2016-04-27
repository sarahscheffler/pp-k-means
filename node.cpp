#include <zmq.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const string clientPrefix="tcp://localhost:";
const string serverPrefix="tcp://*:";
const int basePort=8000;
const int broadcastPort=7000;
const int dataSize=9;
const string genericData="publicKey";

int procNumber, totalProcs;
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

    if(procNumber) {
        cout<<"Received "<<s_recv(broadSockets[0])<<endl;


    } else {
        //send public key e to all parties
        for(int i=0; i<(totalProcs-1); i++) {
            s_send(broadSockets[i],genericData);
            string resp=s_recv(broadSockets[i]);
        }
    }
    return vector<int>();
}

int main (int argc, char* argv[])
{
    procNumber = atoi(argv[1]);
    totalProcs =atoi(argv[2]);

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

    reqSocket->close();
    repSocket->unbind(serverPrefix+to_string(basePort+procNumber));
    if(procNumber) broadSockets[0]->unbind(serverPrefix+to_string(broadcastPort+procNumber));
    else for(int i=1;i<totalProcs;i++) broadSockets[i-1]->close();

    return 0;
} 