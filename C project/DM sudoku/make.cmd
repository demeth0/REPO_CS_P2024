@echo off

::clear .o files
del bin\object\*.o 2>log.txt
::compile main file
gcc -c main.c -o bin/object/main.o 2>>log.txt
gcc -c sudoku.c -o bin/object/sudoku.o 2>>log.txt

gcc -o main bin/object/*.o 2>>log.txt

more log.txt