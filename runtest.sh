#!/bin/sh

outf=./otest-$$.out
echo "outfile $outf"

n=$(getconf _NPROCESSORS_ONLN)

if [ ! -f /tmp/x/o-file ]; then
	mkdir -p /tmp/x; yes hello | dd count=1 > /tmp/x/o-file
	chmod 555 /tmp/x; chmod 400 /tmp/x/o-file
fi

# run otest on CPUs in parallel
for c in  1 2 4 8 10 16 20 27 32 40 50 55 64 80 96 100 111 128 150 180 200 223; do
	rm -f  /tmp/o-test
	if [ $c -gt $n ] ; then break; fi
	echo Run $c cpus
	for i in `seq $c` ; do ./otest 500000 $c & sleep .01 ; done >> $outf
	sleep .1
	touch /tmp/o-test
	wait
	sleep .5
done
