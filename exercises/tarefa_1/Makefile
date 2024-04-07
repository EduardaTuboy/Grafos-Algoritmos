all: graph main
	gcc -I. *.o -o main.out -std=c99 -Wall
	rm -f *.o
 
main:
	gcc -c main.c -o main.o

graph:
	gcc -c ./graph.c -o graph.o

clean:
	rm -f *.o *.out *.zip

run:
	./main.out

test:
	./main.out < ./tests/caso1.in
	
zip:
	zip -R grafo.zip . '*.c' '*.h' 'Makefile' '*.in' '*.txt'
