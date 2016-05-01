import time
import sys
import zmq
from means import KMeans

from getAddShares import *
from paillier.paillier import *
from modular import *
from random import *

clientPrefix="tcp://localhost:";
serverPrefix="tcp://*:";
dataSize=9;
genericData="publicKey";

basePort = 8000
broadcastPort = 9000
broadSockets=[]
leaderSocket = None

procNumber = int(sys.argv[1])
totalProcs = int(sys.argv[2])
if len(sys.argv)>3:
    basePort = int(sys.argv[3])
    broadcastPort = basePort + 10

f = open("data/addShares/"+str(procNumber)+".in", "r")
for line in f:
    value = eval(line)
f.close()

print "Process", procNumber, "Value", value

context = zmq.Context()
requestSocket = context.socket(zmq.REQ)
replySocket = context.socket(zmq.REP)

requestSocket.connect(clientPrefix + str(basePort+procNumber+1))
replySocket.bind(serverPrefix + str(basePort+procNumber))

if procNumber > 0:
    leaderSocket = context.socket(zmq.REP)
    leaderSocket.bind(serverPrefix + str(broadcastPort+procNumber))
else:
    for i in range(1,totalProcs):
        broadSockets.append(context.socket(zmq.REQ))
        broadSockets[i-1].connect(clientPrefix + str(broadcastPort+i))

if procNumber == 0:
    shares, publicKey = getAddShares(procNumber, totalProcs, value, leaderSocket, replySocket, requestSocket, broadSockets)
else:
    shares, publicKey = getAddShares(procNumber, totalProcs, value, leaderSocket, replySocket, requestSocket)


prod = 1
for i in range(len(shares)):
    prod = (prod*shares[i]) % publicKey.n
print prod

# requestSocket.unbind()
# replySocket.disconnect()
# if procNumber > 0:
#     broadSockets[0].unbind()
# else:
#     for i in range(1,totalProcs):
#         broadSockets[i-1].disconnect()
