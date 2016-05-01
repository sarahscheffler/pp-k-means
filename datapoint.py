class DataPoint:
	#representation of a dataPoint as a d dimensional vector

	def __init__(self, rawIn = None, d = 2 ):
		if rawIn:
			self.val = rawIn.split(" ")
		else:
			self.val=(0) * d
		self.d = d
		self.cluster=None

	def getVector(self):
		return self.val

	def addVector(self, B):
		self.val = [a+b for a,b in zip(self.val, B.getVal())]

	def distanceTo(self,B):
		return sum([abs(a**2 - b**2) for a,b in zip(self.val, B.getVal())] )

	def setCluster(self, cluster):
		self.cluster = cluster

	def getCluster(self):
		return self.cluster

