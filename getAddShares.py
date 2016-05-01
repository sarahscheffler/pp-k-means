from paillier.paillier import *
from modular import *
from random import *

import pickle

securityParameter = 64
verbose = False

def getAddShares(procNumber, totalProcs, value, leaderSocket, replySocket, requestSocket, broadSockets = None):
    if procNumber > 0:    #Process is NOT leader
        publicKey = pickle.loads(leaderSocket.recv())
        n = publicKey.n
        if verbose:
            print "Process", procNumber, ":", "Received ", publicKey, "from Leader"
        resp = int(replySocket.recv())
        if verbose:
            print "Process", procNumber, ":", "Received from Process", procNumber-1, ":", resp
        # multiply encrypted input by what we just received
        forwardMessage = (resp*encrypt(publicKey,value)) % (n*n)
        if procNumber < (totalProcs-1):
            requestSocket.send(str(forwardMessage))
            forwardMessage = int(requestSocket.recv())
            if verbose:
                print "Process", procNumber, ":", "Received from Process", procNumber+1, ":", forwardMessage
        # select a random share
        share = generate_share(n)
        leaderSocket.send(str(share)) # send share back to p1
        backMessage = mod_exp(forwardMessage,mod_inv(share,n),(n*n))
        replySocket.send(str(backMessage)); #send something backwards
        prod = int(leaderSocket.recv())    # receive shares
        leaderSocket.send("")
        if verbose:
            print "Process", procNumber, ":", "Received from Leader : ", prod
    
    else:            #Leader Process
        shares = [0 for i in range(totalProcs)]
        privateKey, publicKey = generate_keypair(securityParameter)
        #send public key to all parties
        for i in range(totalProcs-1):
            broadSockets[i].send(pickle.dumps(publicKey))
        requestSocket.send(str(encrypt(publicKey,value))) #send encrypted x0
        for i in range(totalProcs-1):
            shares[i+1] =  int(broadSockets[i].recv()) # collect all the shares
            if verbose:
                print "Process", procNumber, ":", "Received from Process", i+1, " -- Share :", shares[i+1]
        resp = int(requestSocket.recv())
        if verbose:
            print "Process", procNumber, ":", "Received from Process 1 :", resp

        prod = decrypt(privateKey, publicKey, resp)
        for i in range(1,totalProcs):
            prod = (prod * shares[i]) % publicKey.n

        for i in range(totalProcs-1):
            broadSockets[i].send(str(prod)); #send product
            broadSockets[i].recv()
        #resp=s_recv(broadSockets[i]);  receive acknowledgement
    return prod