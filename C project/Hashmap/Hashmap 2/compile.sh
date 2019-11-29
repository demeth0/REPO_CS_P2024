#!/bin/bash
echo "start compiling"
gcc -o bin/Main src/Main.c 2>error.txt
if [ "$1" == "-e" ] ; then
	echo "running program:"
	echo "--------------------------------------------------------------------------------"
	./bin/Main
	echo
	echo "--------------------------------------------------------------------------------"
fi
echo "compilation finished"