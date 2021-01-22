make: clean compile
	gcc -o main ./main.o ./AlgoGenetique.o
	gcc -o test_unitaires_calcul ./test_unitaires_calcul.o

compile:
	gcc -c main.c -o main.o -Wall -Wextra -pedantic
	gcc -c AlgoGenetique.c -o AlgoGenetique.o -Wall -Wextra -pedantic
	gcc -c test_unitaires_calcul.c -o test_unitaires_calcul.o -Wall -Wextra -pedantic
clean:
	rm *.o -f
