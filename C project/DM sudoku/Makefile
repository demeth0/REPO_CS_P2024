all: sudoku

sudoku: main.o sudoku.o 
	gcc -Wall -g -o $@ $^


%.o: %.c
	gcc -Wall -g -c $<

clean: 
	rm -rf *.o 
	rm -rf ./sudoku 
