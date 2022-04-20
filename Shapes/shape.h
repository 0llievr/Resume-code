//shape.h
//Olynch
//Oliver Thurston Lynch

#ifndef SHAPE
#define SHAPE

#include <iostream>
#include "grid.h"
using namespace std;

class Shape
{
protected:
  int x;
  int y;

public:
  Shape(int, int);
  virtual void draw(Grid &grid) = 0;


};

#endif
