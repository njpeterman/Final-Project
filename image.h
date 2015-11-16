#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <ostream>
#include <png.h>
#include "png.h"


using std::uint8_t;


class Image : public PNG
{
 public:
  void flipleft();
  void adjustbrightness(int r, int g, int b);
  void invertcolors();
  
 private:
  
  
};

#endif
