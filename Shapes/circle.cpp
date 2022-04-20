//circle.cpp
//Olynch
//Oliver Thurston Lynch

#include <iostream>
#include "circle.h"
#include "shape.h"

using namespace std;

Circle :: Circle(int x, int y) : Shape(x,y)
{
}

void Circle :: draw(Grid &grid)
{
  for(int i = 0; i < 4; ++i)
  {
    if(i == 0 || i == 3)
    {
      grid.set(x + 1, y + i, 'o');
      grid.set(x + 2, y + i, 'o');
    }
    else if(i == 1 || i == 2)
    {
      grid.set(x, y + i, 'o');
      grid.set(x + 3, y + i, 'o');
    }
  }
}
