CC = gcc
CFLAGS = -std=c99 -Wall -O2 -Werror=implicit-function-declaration 
OBJ = raytracer.x
O_FILES = ppm.o 

all: ppm.o main.o
	$(CC) $(CFLAGS) main.o ppm.o -o $(OBJ)
	make clean

ppm.o: ppm.c
	$(CC) -c $(CFLAGS) ppm.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c


exec:
	./$(OBJ)

clean:
	rm *.o
