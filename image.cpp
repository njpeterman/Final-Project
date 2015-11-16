#include <cstdint>
#include "image.h"

using std::uint8_t;

void Image::flipleft()
{
  RGBAPixel * left; RGBAPixel * right; RGBAPixel * temp = new RGBAPixel;
  int x, y;

  for(y = 0; y < (int) this->height(); y++)
    {
      for(x = 0; x < (int) this->width()/2; x++)
	{
	  left = (*this)(x, y);
	  right = (*this)( (int) this->width() - x - 1, y);
	  temp->red = right->red;
	  temp->green = right->green;
	  temp->blue = right->blue;
	  

	  right->red = left->red;
	  right->blue = left->blue;
	  right->green = left->green;

	  left->red = temp->red;
	  left->green = temp->green;
	  left->blue = temp->blue;
	}
    }
  delete temp;
  temp = NULL; 
  
}

void Image::adjustbrightness(int r, int g, int b)
{
  RGBAPixel * curr; int x; int y;

  for(y = 0; y < (int) this->height(); y++)
    {
      for(x = 0; x < (int) this->width(); x++)
	{
	  curr = (*this)(x, y);
	  int red = (int) r + curr->red;
	  int green = (int) g + curr->green;
	  int blue = (int) b + curr->blue;

	  if(red > 255) { red = 255; }
	  if(green > 255) { green = 255;}
	  if(blue > 255) { blue = 255;}
	  if(red < 0) { red = 0; }
	  if(green < 0) { green = 0;}
	  if(blue < 0) { blue = 0;}

	  curr->red = red; curr->green = green; curr->blue = blue;
	  (*this)(x,y)->red = red;
	  (*this)(x,y)->green = green;
	  (*this)(x,y)->blue = blue; 
	}
    }
  
  
}

void Image::invertcolors()
{
  RGBAPixel * curr; int x; int y;

  for(y = 0; y < (int) this->height(); y++)
    {
      for(x = 0; x < (int) this->width(); x++)
	{
	  curr = (*this)(x, y);
	  curr->red = 255 - curr->red;
	  curr->green = 255 - curr->green;
	  curr->blue = 255 - curr->blue;
	}
    }
 
}
