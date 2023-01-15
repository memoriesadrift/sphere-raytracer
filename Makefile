# ROOT/MAKEFILE
CC = gcc
CFLAGS = -Wall -O2 -Werror=implicit-function-declaration 
OBJ = raytracer.x
O_FILES = ppm.o 

all: build/ppm.o build/vector.o build/render.o build/libxml.o build/xml.o build/objects.o build/main.o
	$(CC) $(CFLAGS) build/main.o build/libxml.o build/xml.o build/objects.o build/ppm.o build/vector.o build/render.o -o $(OBJ) -lm

build/ppm.o: src/ppm.c
	$(CC) -c $(CFLAGS) src/ppm.c -o build/ppm.o

build/vector.o: src/vector.c
	$(CC) -c $(CFLAGS) src/vector.c -o build/vector.o

build/render.o: src/render.c
	$(CC) -c $(CFLAGS) src/render.c -o build/render.o

build/xml.o: src/xml.c
	$(CC) -c $(CFLAGS) src/xml.c -o build/xml.o

build/objects.o: src/objects.c
	$(CC) -c $(CFLAGS) src/objects.c -o build/objects.o

# External library code for working with XML files
build/libxml.o: lib/xml/src/xml.c
	$(CC) -c $(CFLAGS) lib/xml/src/xml.c -o build/libxml.o

build/main.o: src/main.c
	$(CC) -c $(CFLAGS) src/main.c -o build/main.o

exec:
	./$(OBJ) -f scenes/example1.xml
	./$(OBJ) -f scenes/example2.xml
	./$(OBJ) -f scenes/example3.xml

clean:
	rm build/*.o

clean-artifacts:
	rm *.x
	rm *.ppm

full-clean:
	make clean
	make clean-artifacts
