#include "bitmap.hpp"

int main(int argc, char **argv){
	char *fileName;
	if(argc != 2){
		fileName = (char *)"primes.bmp";
	}
	else{
		fileName = argv[1];
	}
	
	Bitmap bmp(WIDTH, HEIGHT);
	/*
	for(int i = 0; i < WIDTH; ++i){
		for(int j = 0; j < HEIGHT; ++j){
			bmp.setPixel(i, j, Color(YELLOW));
		}
	}
	if(!bmp.createBMP(fileName)){
		std::cout << "FAILED TO CREATE";
		return -1;
	}*/
	
	for(int i = 0; i < WIDTH; ++i){
		for(int j = 0; j < HEIGHT; ++j){
			int temp = i*WIDTH+j;
			if(isPrime(temp)){
				bmp.setPixel(j, i, Color(RED));
			}
			else{
				if((temp % 9) == 0){
					bmp.setPixel(j, i, Color(BLUE));
				}
				else if((temp % 5) == 0){
					bmp.setPixel(j, i, Color(GREEN));
				}
				else if ((temp % 7) == 0){
					bmp.setPixel(j, i, Color(WHITE));
				}
				else{
					bmp.setPixel(j, i, Color(BLACK));
				}
			}
		}
	}
	if(!bmp.createBMP(fileName)){
		std::cout << "FAILED TO CREATE" << std::endl;
		return -1;
	}
	return 0;
}
