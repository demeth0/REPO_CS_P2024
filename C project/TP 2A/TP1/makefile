compile: clean compile_fonctions compile_main
	gcc -o main bin/main.o bin/fonctions.o

compile_fonctions:
	gcc -c fonctions.c -o bin/fonctions.o -Wall -Wextra -pedantic
compile_main:
	gcc -c main.c -o bin/main.o -Wall -Wextra -pedantic
clean:
	rm bin/*.o -f
