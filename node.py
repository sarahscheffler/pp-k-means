import time
import sys
import zmq
from means import KMeans

clientPrefix="tcp://localhost:";
serverPrefix="tcp://*:";
dataSize=9;
genericData="publicKey";

basePort = 8000
broadcastPort = 9000
broadSockets=[]
genericData = "publicKey"

procNumber = int(sys.argv[1])
totalProcs = int(sys.argv[2])
if len(sys.argv)>3:
	basePort = int(sys.argv[3])
	broadcastPort = basePort + 10

print "starting ", procNumber, totalProcs

def getAddShares(input):
	if procNumber > 0 :
		print "Received ", broadSockets[0].recv()

		resp = repSocket.recv()
		print "received from repSocket", resp

        # multiply encrypted input by waht we just got
		if procNumber < (totalProcs-1):
			reqSocket.send(genericData)
			resp = reqSocket.recv()
			print "received from reqSocket", resp

        #select a random share 
		broadSockets[0].send(genericData) # send share back to p1
		repSocket.send(genericData); #send something backwards

		resp = broadSockets[0].recv() #receive shares
	else :
    	#send public key e to all parties
		for i in range(totalProcs-1):
			broadSockets[i].send(genericData)

		reqSocket.send(genericData) #send encrypted x1

		for i in range(totalProcs-1):
			resp =  broadSockets[i].recv() # collect all the shares
			print "received from socket", i, "share ", resp
		resp = reqSocket.recv()
        #now compute its own share. We know all shares now

		for i in range(totalProcs-1):
			broadSockets[i].send(genericData); #send all shares
		#resp=s_recv(broadSockets[i]);  receive acknowledgement
	return []

context = zmq.Context()
reqSocket = context.socket(zmq.REQ)
repSocket = context.socket(zmq.REP)

reqSocket.connect(clientPrefix + str(basePort+procNumber+1))
repSocket.bind(serverPrefix + str(basePort+procNumber))

if procNumber > 0:
	broadSockets.append(context.socket(zmq.REP))
	broadSockets[0].bind(serverPrefix+str(broadcastPort +  procNumber))
else:
	for i in range(1,totalProcs):
		broadSockets.append(context.socket(zmq.REQ))
		broadSockets[i-1].connect(clientPrefix + str(broadcastPort + i))

getAddShares(0)

# reqSocket.unbind()
# repSocket.disconnect()
# if procNumber > 0:
# 	broadSockets[0].unbind()
# else:
# 	for i in range(1,totalProcs):
# 		broadSockets[i-1].disconnect()
