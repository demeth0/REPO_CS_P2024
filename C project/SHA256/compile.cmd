@echo off
del /f bin\\*.o
gcc -c preprocessing.c -o bin/preprocessing.o -g -Wall
gcc -c fonctions.c -o bin/fonctions.o -g -Wall
gcc -c main.c -o bin/main.o -g -Wall

gcc -o sha256 bin/main.o bin/preprocessing.o bin/fonctions.o