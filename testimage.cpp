/**********************************************************
 * testimage.cpp -- part of CS225 MP2
 *
 * This file performs some basic tests of the Image class.
 * It is not intended to catch every possible error.You may 
 * modifty this or write your own testimage.cpp to perform 
 * additional tests.
 *
 *   Author: Jonathan Ray
 *   Date: 02 Feb 2007
 */

#include "image.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
  /*Image* myImage = new Image();
	myImage->readFromFile("in_01.png");
	myImage->invertcolors();
	myImage->writeToFile("inverted.png");

	myImage->flipleft();
	myImage->writeToFile("flipped.png");
	
	myImage->adjustbrightness(20, 20, -40);
	myImage->writeToFile("brightened.png");

	delete myImage;*/


  int numLevels = 1;
  for(int i = 0; i < numLevels; i++)
    {
      PNG * myImage = new PNG();
      string filename;
      //std::cout << "Enter a file name to read: ";
      std::getline(cin, filename);
      myImage->readFromFile(filename);
      //std::cout << myImage->width();
      //std::cout << myImage->height();
      //return 1;
  
      PNG * outImage = new PNG(640, 480);
      bool isPlatform[640][480] = {false};
      int r, g, b;

      int avg_red[80][60];
      int avg_green[80][60];
      int avg_blue[80][60];

      int x, y, x_block, y_block;
      // calculate average pixel values
      for(x = 0; x < 80; x++)
	{
	  for(y = 0; y < 60; y++)
	    {
	      r = 0; g = 0; b = 0; 
	      for(x_block = 8*x; x_block < 8*x + 8; x_block++)
		{
		  for(y_block = 8*y; y_block < (8*y + 8); y_block++)
		    {
		      //std::cout << "x_block: " << x_block << "y block: " << y_block << std::endl;
		      r += (*myImage) (x_block, y_block)->red;
		      g += (*myImage) (x_block, y_block)->green;
		      b += (*myImage) (x_block, y_block)->blue;
		    }
		}
	      r = (int) r / 64;
	      g = (int) g / 64;
	      b = (int) b / 64;
	      avg_red[x][y] = r;
	      avg_green[x][y] = g;
	      avg_blue[x][y] = b;
	    }
	}
  

      for(x = 0; x < 640; x++)
	{
	  for(y = 0; y < 480; y++)
	    {
	      (*outImage) (x, y)->red = (uint8_t) avg_red[ (int) x/8][ (int) y/8 ];
	      (*outImage) (x, y)->green = (uint8_t) avg_green[ (int) x/8][ (int) y/8 ];
	      (*outImage) (x, y)->blue = (uint8_t) avg_blue[ (int) x/8][ (int) y/8 ];
	    }
	}

      outImage->writeToFile("out.png");


      //creates isPlatform that tells us whether a pixel is a wall/obstacle or movable region
      for(x = 0; x < 640; x++)
	{
	  for(y = 0; y < 480; y++)
	    {	
	      //177 is 'b1' in hex, and 191 is 'bf' in hex
	      //This is the range of red values that determines a brown wall/obstacle
	      if( ((int)(*outImage) (x, y)->red) == 32 ||  ((int)(*outImage) (x, y)->red) == 96 ){ 
		isPlatform[x][y] = true;
		//(*testImage) (x, y)->red = 195;
	      }
	    }
	}
  
      //testImage->writeToFile("test.png");
      
      /*
      // Memory pixel printing
      int counter = 1;
      for(y = 0; y < 60; y++)
	{
	  for(x = 0; x < 80; x++)
	    {
	      // Printing pixels for memory
	      int pixel = ((avg_red[x][y]/8) << 10) + ((avg_green[x][y]/8) << 5) + (avg_blue[x][y]/8);
	      std::cout << std::setfill('0') << std::setw(4) << std::hex << pixel;
	    }
	    } */


      // 2D boolean array printing
      for(x = 0; x < 640; x++)
	{
	  std::cout << "{";
	  for(y = 0; y < 480; y++)
	    {
	      int platform;
	      if(isPlatform[x][y])
		platform = 1;
	      else
		platform = 0;
	      
	      if(y == 479)
		{
		  std::cout << platform << "}," << std::endl;
		} else
		{
		  std::cout << platform << ", ";
		}
	    }

	}




      
    }  
	
	return 0;
}

