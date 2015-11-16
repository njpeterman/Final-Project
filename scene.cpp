#include <cstdint>
#include "scene.h"

using std::uint8_t;

Scene::Scene(int max1)
{
  max = max1;
  images = new Image*[max1];
  int i;
  for(i = 0; i < max1; i++)
    {
      images[i] = NULL;
    }
  x = new int[max1];
  y = new int[max1];
}

Scene::~Scene()
{
  delete []x; x = NULL;
  delete []y; y = NULL;
  int i;
  for(i = 0; i < max; i++)
    {
      delete images[i];
    }
  delete []images;
  images = NULL;
}

Scene::Scene (const Scene & source)
{
  // copy constructor
  max = source.max;
  x = new int[source.max];
  y = new int[source.max];
  images = new Image*[source.max];
  int i;
  for(i = 0; i < source.max; i++)
    {
      if(source.images[i] == NULL)
	{
	  images[i] = NULL;
	} else
	{
	  x[i] = source.x[i];
	  y[i] = source.y[i];
	  //Image temp;
	  //Image temp1;
	  // copy each pixel of the images over into new images
	  images[i] = new Image;
	  *(images[i]) = *(source.images[i]);

	}
    }  
}


//Reassigning the '=' operator
const Scene & Scene::operator= 	(const Scene & source)
{
  // check for self assignment
  int i;
  if(this == &source) { return *this; }

  // else, this is not self assignment
  delete []x;
  delete []y;
  for(i = 0; i < max; i++)
    {
      delete images[i];
    }
  delete []images;

  max = source.max;
  x = new int[source.max];
  y = new int[source.max];
  images = new Image*[source.max];

  for(i = 0; i < source.max; i++)
    {
      if(source.images[i] == NULL)
	{
	  images[i] = NULL;
	} else
	{
	  x[i] = source.x[i];
	  y[i] = source.y[i];
	  // copy each pixel of the images over into new images
	  images[i] = new Image;
	  *(images[i]) = *(source.images[i]);

	}
    }  

  return *this;
  
}

void Scene::changemaxlayers(int newmax)
{
  int i; 
  if(newmax == max)
    {
      return;
    }

  if(newmax < max)
    {
      for(i = newmax; i < max; i++)
	{
	  if(images[i] != NULL)
	    {
	      std::cout << "invalid newmax" << endl; 
	      return;
	    }
	}
    }

  // else, we have to change the array size

  int temp_max = std::min(newmax, max);
  

  Image ** newArray = new Image*[newmax];
  int * new_x = new int[newmax];
  int * new_y = new int[newmax];
  for(i = 0; i < temp_max; i++)
    {
      if(images[i] == NULL) 
	{
	  newArray[i] = NULL;
	  new_x[i] = 0; 
	  new_y[i] = 0; 
	} else
	{
	  newArray[i] = images[i];
	  new_x[i] = x[i];
	  new_y[i] = y[i];
	}
    }

  if(newmax > max)
    {
      for(i = max; i < newmax; i++)
	{
	  newArray[i] = NULL; 
	  new_x[i] = 0;
	  new_y[i] = 0;
	}
    }

  // free the current image array

  for(i = 0; i < max; i++)
    {
      delete images[i];
    }
  delete []images;

  delete []x;
  delete []y;

  max = newmax;

  //reassign
  images = newArray;
  x = new_x;
  y = new_y;
}

void Scene::addpicture(const char* FileName,
		       int index,
		       int x1, int y1)
{
  if(index > (max-1) || index < 0)
    {
      std::cout << "index out of bounds" << endl; 
      return;
    }


  // else, we need to add the new image
  x[index] = x1;
  y[index] = y1;
  images[index] = new Image; 
  (*images[index]).readFromFile(FileName);
  /*Image newImage;
  newImage.readFromFile(FileName);
  images[index]->resize(newImage.width(), newImage.height());
  int i,j;
  //Image temp;
  for(i = 0; i < newImage.width(); i++)
    {
      for(j = 0; j < newImage.height(); j++)
	{
	  //temp = *(images[i]);
	  (*(images[i]))(i, j)->red = newImage(i, j)->red;
	  (*(images[i]))(i, j)->green = newImage(i, j)->green;
	  (*(images[i]))(i, j)->blue = newImage(i, j)->blue;
	}
	}*/
  
  return; 
}

void Scene::changelayer(int index, int newindex)
{
  if(index == newindex)
    {
      return;
    }

  if(index < 0 || newindex < 0 || index > (max-1) || newindex > (max-1))
    {
      std::cout << "invalid index" << endl; return;
    }

  if(images[newindex] != NULL)
    {
      delete images[newindex];
      images[newindex] = NULL; 
    }

  // now that the image has been deleted (or was NULL), let's move the
  // image
  images[newindex] = images[index];
  images[index] = NULL;
  x[newindex] = x[index];
  y[newindex] = y[index];
  
}

void Scene::translate(int index, int xcoord, int ycoord)
{
  if(index < 0 || index > (max-1))
    {
      std::cout << "invalid index" << endl;
    } else
    {
      x[index] = xcoord;
      y[index] = ycoord;
    } 
}

void Scene::deletepicture(int index)
{
  if(index < 0 || index > (max-1) || images[index] == NULL)
    {
      std::cout << "invalid index" << endl;
    } else
    {
      delete images[index];
      images[index] = NULL;
    }
}

Image * Scene::getpicture(int index) const
{
  if(index < 0 || index > (max-1))
    {
      std::cout << "invalid index" << endl;
      return NULL;
    } else
    {
      return images[index];
    }
}

Image Scene::drawscene() const
{
  int width = 0;
  int height = 0;
  int i, x1, y1, j, k;
  
  // dimensions of newimage
  for(i = 0; i < max; i++)
    {
      if(images[i] != NULL)
	{
	  x1 = x[i] + images[i]->width();
	  y1 = y[i] + images[i]->height();

	  if(x1 > width) {width = x1;}
	  if(y1 > height) {height = y1;}
	}
    }


  Image newImage;
  newImage.resize((size_t) width, (size_t) height);

  
  
  //loop through every image
  for(i = 0; i < max; i++)
    {
      if(images[i] != NULL)
	{
	  for(k = 0; k < (int) images[i]->height(); k++)
	    {
	      for(j = 0; j < (int) images[i]->width(); j++)
		{ 
		  *(newImage(j+x[i],k+y[i])) = *((*(images[i]))(j, k));
		}
	    }
	}
    }
  
  return newImage;
}
