#ifndef BITMAP_H
#define BITMAP_H
#include <fstream>

#define WIDTH 15000
#define HEIGHT 15000
/*
* char is 1 byte
* short int is 2 bytes
* long is 4 bytes
*/
// 14 bytes
struct bmpHeader{
	char magic1;		// 'B' - magic number
	char magic2;		// 'M' - magic number
	long size;			// file size
	short int reserved1;	// Just reserved space, because of the
	short int reserved2;	// reserved, size can be 8 bytes
	int offset;		// 14+40 - distance from start to image data
};

// 40 bytes
struct bmpInfoHeader{
	long iHSize;		// 40
	long width;			// image width
	long height;		// image height
	short int colorPlanes;	// 1
	short int bPerPixel; 	// 24 - number of bits per pixel
	long compression; 	// 0 - not used
	long imageSize;		// image data, not file size
	long horizRes;		// horizontal resolution - pixels per meter
	long vertRes;		// vertical resolution - pixels per meter
	long colorPallette;	// 0 (2^n) - number of colors available
	long importantColors;	// 0 - all colors are important
};

bool isPrime(int);
bool setupBMP(std::ofstream&, char *, int, int);
bool createBMP(std::ofstream&, char *, char *, int, int);
#endif
