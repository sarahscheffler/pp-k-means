from datapoint import DataPoint

class KMeans:

	def __init__(self, initMeans):
		self.dataPoints = []
		self.means = initMeans
		self.k = len(initMeans)

	def addPoint(self, rawIn):
		#add point for a line of raw input
		self.dataPoints.append(DataPoint(rawIn))

	def readData(self, inputFile):
		f = open(inputFile, 'r')
		for line in f:
			self.addPoint(line)

	def getClusterCentroids(self):
		centroids = [(DataPoint(),0) for i in range(self.k)]
		for point in dataPoints:
			closestCluster =min([(means[i].distanceTo(point), i) for i in range(self.k)])[1]
			point.setCluster(means[closestCluster])
			centroids[closestCluster][0].addVector(point)
			centroids[closestCluster][1]+=1
		return centroids

	def updateMeans(means):
		self.means = means







