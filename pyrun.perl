#!/bin/perl
my $k = 5;
my $port = 6800;
for (my $i=0; $i<$k; $i++) {
	print "Starting $i\n";
	system("python node.py $i $k $port &");
}
