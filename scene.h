#ifndef SCENE_H
#define SCENE_H

#include <cstdint>
#include <ostream>
#include "image.h"
#include "image.h"

using std::uint8_t;

class Scene
{
 public:
  Image ** images;
  int * x;
  int * y;
  int max;

  Scene(int max);
  Scene(const Scene & source);
  ~Scene();
  const Scene & operator=(const Scene & source);
  void changemaxlayers(int newmax);
  void addpicture(const char * FileName, int index, int x, int y);
  void changelayer(int index, int newindex);
  void translate(int index, int xcoord, int ycoord);
  void deletepicture(int index);
  Image * getpicture(int index) const;
  Image drawscene() const;

 private:

  
};
#endif
