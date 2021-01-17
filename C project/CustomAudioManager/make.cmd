@echo off

::clear .o files
del bin\object\*.o 2>log.txt
::compile main file
gcc -c main.c -o bin/object/main.o 2>>log.txt
gcc -c AudioUtils.c -o bin/object/AudioUtils.o 2>>log.txt
gcc -c CustomWavDecoder.c -o bin/object/CustomWavDecoder.o 2>>log.txt

gcc -o main bin/object/*.o -lwinmm 2>>log.txt

more log.txt