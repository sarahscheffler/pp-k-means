#!/bin/perl
my $k = 5;
my $port = 5300;
print "Generating Data ...\n";
system("python datagen.py &");
for (my $i=0; $i<$k; $i++) {
	print "Starting $i\n";
	system("python node.py $i $k $port &");
}
