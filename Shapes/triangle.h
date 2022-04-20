//triangle.h
//Olynch
//Oliver Thurston Lynch

#ifndef TRIANGLE
#define TRIANGLE

#include <iostream>
#include "grid.h"
#include "shape.h"
using namespace std;

class Triangle : public Shape
{
 private:
 public:
   Triangle(int x, int y);
   virtual void draw(Grid &grid);

};

#endif
