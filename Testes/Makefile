all: exe

exe: main.o RBT.o
		gcc -g -o exe main.o .o

main.o: RBT.h
		gcc -g -c main.c -Wall

rubro.o: RBT.h
		gcc -g -c RBT.c -Wall
	
clean:
		rm *.o exe