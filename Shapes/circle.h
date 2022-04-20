//circle.h
//Olynch
//Oliver Thurston Lynch

#ifndef CIRCLE
#define CIRCLE

#include <iostream>
#include "grid.h"
#include "shape.h"
using namespace std;

class Circle : public Shape
{
 private:

 public:
   Circle(int x, int y);
   virtual void draw(Grid &grid);

};

#endif
