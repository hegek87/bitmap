#include "bitmap.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>

const static int RED = 0xFF0000;
const static int BLACK = 0x000000;

bool isPrime(int p){
	if(p == 2){ return true; }
	if(p < 0){ return false; }
	for(int i = 2; i*i < p; ++i){
		if((p%i) == 0){
			return false;
		}
	}
	return true;
}

int createBMP(char *fileName, char *imageData, int width, int height){
	bmpInfoHeader iHeader;
	iHeader.iHSize = 40;
	iHeader.width = width;
	iHeader.height = height;
	iHeader.colorPlanes = 1;
	iHeader.bPerPixel = 24;
	iHeader.compression = 0;
	
	short int rowSize = (((iHeader.bPerPixel*iHeader.width)+31)/32)*4;
	short int pixelArraySize = rowSize * std::abs(iHeader.height);
	iHeader.imageSize = pixelArraySize;
	iHeader.horizRes = 2835;
	iHeader.vertRes = 2835;
	iHeader.colorPallette = 0;
	iHeader.importantColors = 0;
	
	bmpHeader header;
	header.magic1 = 'B';
	header.magic2 = 'M';
	header.size = 54 + pixelArraySize;
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.offset = 54;
	std::cout << header.size << std::endl;
	std::cout << sizeof(char) << std::endl;
	std::cout << sizeof(short int) << std::endl;
	std::cout << sizeof(int) << std::endl;
	std::cout << sizeof(long) << std::endl;
	
	//write bmpHeader
	std::ofstream writeFile;
	writeFile.open(fileName);
	writeFile << header.magic1;				// 1 byte
	writeFile << header.magic2;				// 1 byte
	writeFile.write((char *)&header.size, 4);		// 4 bytes
	writeFile.write((char *)&header.reserved1, 2);	// 2 bytes
	writeFile.write((char *)&header.reserved2, 2);	// 2 bytes
	writeFile.write((char *)&header.offset, 4);	// 4 bytes
									// 14 bytes written
	
	//write bmpInfoHeader
	writeFile.write((char *)&iHeader.iHSize, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.width, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.height, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.colorPlanes, 2);	// 2 bytes
	writeFile.write((char *)&iHeader.bPerPixel, 2);		// 2 bytes
	writeFile.write((char *)&iHeader.compression, 4);	// 4 bytes
	writeFile.write((char *)&iHeader.imageSize, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.horizRes, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.vertRes, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.colorPallette, 4);	// 4 bytes
	writeFile.write((char *)&iHeader.importantColors, 4);	// 4 bytes
									// 40 bytes written
	char *p = imageData;
	while(*p != '\0'){
		writeFile.write(p, 3);
		p+=3;
	}
	return 1;
}

int main(int argc, char **argv){
	char *fileName;
	if(argc != 2){
		fileName = "primes.bmp";
	}
	else{
		std::cout << "Custom file name" << std::endl;
		fileName = argv[1];
	}
	bmpInfoHeader iHeader;
	iHeader.iHSize = 40;
	iHeader.width = 500;
	iHeader.height = 500;
	iHeader.colorPlanes = 1;
	iHeader.bPerPixel = 24;
	iHeader.compression = 0;
	
	short int rowSize = (((iHeader.bPerPixel*iHeader.width)+31)/32)*4;
	short int pixelArraySize = rowSize * std::abs(iHeader.height);
	iHeader.imageSize = pixelArraySize;
	iHeader.horizRes = 2835;
	iHeader.vertRes = 2835;
	iHeader.colorPallette = 0;
	iHeader.importantColors = 0;
	
	bmpHeader header;
	header.magic1 = 'B';
	header.magic2 = 'M';
	header.size = 54 + pixelArraySize;
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.offset = 54;
	std::cout << header.size << std::endl;
	std::cout << sizeof(char) << std::endl;
	std::cout << sizeof(short int) << std::endl;
	std::cout << sizeof(int) << std::endl;
	std::cout << sizeof(long) << std::endl;
	
	//write bmpHeader
	std::ofstream writeFile;
	writeFile.open(fileName);
	writeFile << header.magic1;				// 1 byte
	writeFile << header.magic2;				// 1 byte
	writeFile.write((char *)&header.size, 4);		// 4 bytes
	writeFile.write((char *)&header.reserved1, 2);	// 2 bytes
	writeFile.write((char *)&header.reserved2, 2);	// 2 bytes
	writeFile.write((char *)&header.offset, 4);	// 4 bytes
									// 14 bytes written
	
	//write bmpInfoHeader
	writeFile.write((char *)&iHeader.iHSize, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.width, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.height, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.colorPlanes, 2);	// 2 bytes
	writeFile.write((char *)&iHeader.bPerPixel, 2);		// 2 bytes
	writeFile.write((char *)&iHeader.compression, 4);	// 4 bytes
	writeFile.write((char *)&iHeader.imageSize, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.horizRes, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.vertRes, 4);		// 4 bytes
	writeFile.write((char *)&iHeader.colorPallette, 4);	// 4 bytes
	writeFile.write((char *)&iHeader.importantColors, 4);	// 4 bytes
									// 40 bytes written
	
	for(int i = iHeader.width-1; i >= 0; --i){
		for(int j = iHeader.height-1; j >= 0; --j){
			if(isPrime(i*iHeader.width+j)){
				writeFile.write((char *)&RED, 3);
			}
			else{
				writeFile.write((char *)&BLACK, 3);
			}
		}
	}
	
	writeFile.close();
	
	std::cout << isPrime(10) << std::endl;
	std::cout << isPrime(11) << std::endl;
	return 0;
}
