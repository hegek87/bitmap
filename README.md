Overview
========
Represents a bitmap file for images. A default constructor provides no compression, 24 bits per pixel, and WIDTH, HEIGHT based on the macros in bitmap.hpp. There is also a constructor which allows a custom bitmap header and bitmap info header. This allows the user to specify the exact details of the bitmap. The user can create a bitmap based on already supplied image data, and they can specify the color of each individual pixel. The user can specify a file for bmp_main.cpp to write a file to, but the file name is optional. If no file name is specified we will write to primes.bmp. See below for a few screenshots.

Creating a bitmap
-----------------
After constructing the bitmap, the user has two options, either create the bitmap with the default data, or set the pixels in the image, then create the bitmap.

Setting a pixel
---------------
The setPixel method has as a signature bool Bitmap::setPixel(int x, int y, Color rgb). This method will set the pixel at (x,y) to be color rgb.

Screenshot
----------
The screenshot below paints the pixels based on the value of the current position. Let (i,j) be an ordered pair in {1,2,...WIDTH}x{1,2,...,HEIGHT}. Let temp = i*WIDTH+j, if temp is prime, color the pixel at (i,j) red. Depending on if temp is divisible by 9,5,7, we color the pixel (i,j) blue, green, white respectively. Otherwise we set the pixel to black. The class is simple enough to allow the user to create arbitrary bitmaps (and it is used in the mandelbrot set, and will be used in the raytracer that I plan to develop).

![Alt text](primes.bmp)
![Alt text](wp2.bmp)
![Alt text](wp3.bmp)
