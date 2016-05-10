#!/bin/perl
my $numProcs = 5;
my $numClusters = 4;
my $numPoints = 100;
my $dim = 3;
my $iters = 10;
my $port = 5400;

print "Generating Data ...";
system("python datagen.py $numProcs $numClusters $numPoints $dim &");
print " Done\n";
for (my $i=0; $i<$numProcs; $i++) {
	print "Starting $i\n";
	system("python node.py $i $numProcs $numClusters $iters $port &");
}
