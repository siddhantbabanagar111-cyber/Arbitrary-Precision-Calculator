apc: main.o basicfun.o addition.o subtraction.o multiplication.o division.o
	gcc -o apc main.o basicfun.o addition.o subtraction.o multiplication.o division.o

main.o: main.c
	gcc -c main.c

basicfun.o: basicfun.c
	gcc -c basicfun.c

addition.o: addition.c
	gcc -c addition.c

subtraction.o: subtraction.c
	gcc -c subtraction.c

multiplication.o: multiplication.c
	gcc -c multiplication.c

division.o: division.c
	gcc -c division.c

clean:
	rm -f *.o apc
