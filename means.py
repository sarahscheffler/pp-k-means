from datapoint import DataPoint
verbose = False

class KMeans:

    def __init__(self, k, inputFile):
        self.dataPoints = []
        if verbose:
            print inputFile
        f = open(inputFile, 'r')
        for line in f:
            val = eval(line)
            self.d = len(val)
            self.dataPoints.append(DataPoint(len(val), val))
        self.k = k
        self.means = self.dataPoints[:k]

    def getClusterCentroids(self):
        centroids = [[DataPoint(self.d),0] for i in range(self.k)]
        for point in self.dataPoints:
            closestCluster =min([(self.means[i].distanceTo(point), i) for i in range(self.k)])[1]
            point.setCluster(self.means[closestCluster])
            centroids[closestCluster][0].addVector(point)
            centroids[closestCluster][1]+=1
        return centroids

    def updateMeans(self, means):
        self.means = means

    def __str__(self):
        return str([mean.getVector() for mean in self.means])

    def getDims(self):
        return self.d






