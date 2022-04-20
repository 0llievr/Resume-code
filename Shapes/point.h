//point.h
//Olynch
//Oliver Thurston Lynch

#ifndef POINT
#define POINT

#include <iostream>
#include "grid.h"
#include "shape.h"
using namespace std;

class Point : public Shape
{
 private:
   char m_c;
 public:
   Point(int x, int y, char c);
   virtual void draw(Grid &grid);

};
#endif
