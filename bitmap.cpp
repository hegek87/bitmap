#include "bitmap.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

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
/*
* Prepares a bitmap file with default header and info header which is of
* size width x height. The image data is initially empty.
*/
Bitmap::Bitmap(int width, int height){
	// create info header
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
	
	// create bitmap header
	bmpHeader header;
	header.magic1 = 'B';
	header.magic2 = 'M';
	header.size = 54 + pixelArraySize;
	header.reserved1 = 0;
	header.reserved2 = 0;
	header.offset = 54;
	this->header = header;
	this->iHeader = iHeader;
	this->image.reserve(width*height);
}

Bitmap::Bitmap(bmpHeader head, bmpInfoHeader iHead){
	this->header = head;
	this->iHeader = iHead;
	int pixelCount = this->iHeader.width * this->iHeader.height;
	this->image.reserve(pixelCount);
}

/*
* Assumes image contains all data that should be written to the bmp
*/
bool Bitmap::createBMP(char *fileName){
	std::ofstream writeFile;
	writeFile.open(fileName);
	if(!writeFile.is_open()){
		return false;
	}
	//write bmpHeader
	writeFile << header.magic1;					// 1 byte
	writeFile << header.magic2;					// 1 byte
	writeFile.write((char *)&header.size, 4);			// 4 bytes
	writeFile.write((char *)&header.reserved1, 2);		// 2 bytes
	writeFile.write((char *)&header.reserved2, 2);		// 2 bytes
	writeFile.write((char *)&header.offset, 4);		// 4 bytes
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
	//write image data
	for(int i = 0; i < iHeader.width*iHeader.height; ++i){
		image[i].writeColor(writeFile);
	}
	writeFile.close();
	return true;
}
	
/*
* Plots Color rgb to the (x,y) pair on the coordinate axes, 
* assuming the bottom left is the point (0,0).
*/
bool Bitmap::setPixel(int x, int y, Color rgb){
	image[y*iHeader.width + x] = rgb;
	return true;
}

const bmpHeader& Bitmap::getHeader(){ return this->header; }
const bmpInfoHeader& Bitmap::getIHeader(){ return this->iHeader; }
