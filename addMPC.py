from paillier.paillier import *
from modular import *
from random import *

priv, pub = generate_keypair(32)
n = pub.n

numParties = 5
x = [randint(0,1000) for i in range(numParties)]
l = [generate_share(n) for i in range(numParties)]
x = [13, 54, 32, 22, 45]
l = [0,1,1,1,1]

prod = 1
for i in range(len(x)):
    prod = (prod*encrypt(pub,x[i])) % (n*n)
    print prod

for i in range(1,len(l)):
    prod = mod_exp(prod,mod_inv(l[len(l)-i],n),(n*n))
    print prod

l[0] = decrypt(priv, pub, prod)

print x
print l
print sum(x)
prod = 1
for i in range(len(l)):
    prod = (prod*l[i]) % n
print prod
