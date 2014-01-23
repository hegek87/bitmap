#include "bitmap.hpp"

const static int RED = 0xFF0000;
const static int BLACK = 0x000000;
const static int WHITE = 0xFFFFFF;
const static int BLUE = 0x0000FF;
const static int GREEN = 0x00FF00;

int main(int argc, char **argv){
	char *fileName;
	if(argc != 2){
		fileName = (char *)"primes.bmp";
	}
	else{
		fileName = argv[1];
	}
	
	std::ofstream writeFile;
	setupBMP(writeFile, fileName, WIDTH, HEIGHT);
	for(int i = WIDTH-1; i >= 0; --i){
		for(int j = HEIGHT-1; j >= 0; --j){
			int temp = i*WIDTH+j;
			if(isPrime(temp)){
				writeFile.write((char *)&RED, 3);
			}
			else{
				if((temp % 9) == 0){
					writeFile.write((char *)&BLUE, 3);
				}
				else if((temp % 5) == 0){
					writeFile.write((char *)&GREEN, 3);
				}
				else if ((temp % 7) == 0){
					writeFile.write((char *)&WHITE, 3);
				}
				else{
					writeFile.write((char *)&BLACK, 3);
				}
			}
		}
	}
	
	writeFile.close();
	
	return 0;
}
