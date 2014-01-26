CC=g++
OBJECTS=	bin/bitmap.o bin/bmp_main.o bin/color.o
CFLAGS = -c -g -Wall

all: bitmap

bitmap: $(OBJECTS)
	$(CC) $(OBJECTS) -o bin/bitmap
	
bin/bitmap.o:
	$(CC) $(CFLAGS) -o bin/bitmap.o bitmap.cpp
	
bin/bmp_main.o:
	$(CC) $(CFLAGS) -o bin/bmp_main.o bmp_main.cpp
	
bin/color.o:
	$(CC) $(CFLAGS) -o bin/color.o ../color/color.cpp
	
clean:
	rm -f ./bin/*
