#include <zmq.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

const string clientPrefix="tcp://localhost:";
const string serverPrefix="tcp://*:";
const int basePort=5000;
const int broadcastPort=6000;

int procNumber, totalProcs;
zmq::socket_t *reqSocket, *repSocket;
zmq::socket_t **broadSockets;

vector<int> getAddShares(int in)  
{
    return vector<int>();
}

int main (int argc, char* argv[])
{
    procNumber = atoi(argv[1]);
    totalProcs =atoi(argv[2]);

    zmq::context_t context (1);
    reqSocket = new zmq::socket_t (context, ZMQ_REQ);
    repSocket = new zmq::socket_t (context, ZMQ_REP);

    //cout<<clientPrefix+to_string(basePort+procNumber+1)<<" "<<serverPrefix+to_string(basePort+procNumber)<<endl;

    reqSocket->connect(clientPrefix+to_string(basePort+procNumber+1));
    repSocket->bind(serverPrefix+to_string(basePort+procNumber));

    if(procNumber!=0) {
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

    return 0;
} 