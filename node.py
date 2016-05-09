import time
import sys
import zmq

from getAddShares import *
#from paillier.paillier import *
from modular import *
from random import *
from means import *
from datapoint import *

clientPrefix="tcp://localhost:";
serverPrefix="tcp://*:";
dataSize=9;
genericData="publicKey";
clusters = 4

basePort = 8000
broadcastPort = 9000
broadSockets=[]
leaderSocket = None
verbose = True

procNumber = int(sys.argv[1])
totalProcs = int(sys.argv[2])
if len(sys.argv)>3:
    basePort = int(sys.argv[3])
    broadcastPort = basePort + 10

context = zmq.Context()
requestSocket = context.socket(zmq.REQ)
replySocket = context.socket(zmq.REP)
kmeans = KMeans(clusters, "data/horizontal-k-means/"+str(procNumber)+".in")
dimensions = kmeans.getDims()

requestSocket.connect(clientPrefix + str(basePort+procNumber+1))
replySocket.bind(serverPrefix + str(basePort+procNumber))

if procNumber > 0:
    leaderSocket = context.socket(zmq.REP)
    leaderSocket.bind(serverPrefix + str(broadcastPort+procNumber))
    broadSockets = None
else:
    for i in range(1,totalProcs):
        broadSockets.append(context.socket(zmq.REQ))
        broadSockets[i-1].connect(clientPrefix + str(broadcastPort+i))

for iteration in range(10): # iterate 20 times for now
    centroids = kmeans.getClusterCentroids()
    newMeans = []
    for centroid, num in centroids:
        denom = getAddShares(procNumber, totalProcs, num, leaderSocket, replySocket, requestSocket, broadSockets)
        if denom == 0 :
            newMeans.append(centroid)
            continue
        newVal = []
        val = centroid.getVector()
        for i in range(dimensions):
            num = getAddShares(procNumber, totalProcs, val[i], leaderSocket, replySocket, requestSocket, broadSockets)
            newVal.append(num / (1.0 * denom))
        newMeans.append(DataPoint(dimensions, newVal))
    if verbose and not procNumber:
        print "[Process", str(procNumber)+"] iteration", iteration, ":", kmeans
    kmeans.updateMeans(newMeans)

# requestSocket.unbind()
# replySocket.disconnect()
# if procNumber > 0:
#     broadSockets[0].unbind()
# else:
#     for i in range(1,totalProcs):
#         broadSockets[i-1].disconnect()
