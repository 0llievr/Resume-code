//square.h
//Olynch
//Oliver Thurston Lynch

#ifndef SQUARE
#define SQUARE

#include <iostream>
#include "grid.h"
#include "shape.h"

using namespace std;

class Square : public Shape
{
 private:
   int m_size;

 public:
   Square(int x, int y, int size);
   virtual void draw(Grid &grid);

};

#endif
