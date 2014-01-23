all:
	g++ -c -g -Wall -o bin/bitmap.o bitmap.cpp
	g++ -c -g -Wall -o bin/bmp_main.o bmp_main.cpp
	
	g++ -o bin/bitmap bin/*.o
