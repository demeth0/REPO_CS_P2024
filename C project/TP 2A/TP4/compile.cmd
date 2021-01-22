@echo off
del /f *.o
gcc -c main.c -o main.o -g -Wall
gcc -c AlgoGenetique.c -o AlgoGenetique.o -g -Wall
gcc main.o AlgoGenetique.o -o main  