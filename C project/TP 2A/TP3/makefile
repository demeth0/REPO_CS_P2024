compile: clean make_object
	gcc -o fat fat.o 
	gcc -o exoListeChaine exoListeChaine.c

make_object:
	gcc -c fat.c -o fat.o -g -Wall
	gcc -c exoListeChaine.c -o exoListeChaine.o -g -Wall

clean:
	rm *.o -f
