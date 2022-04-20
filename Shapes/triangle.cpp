//triangle.cpp
//Olynch
//Oliver Thurston Lynch

#include <iostream>
#include "triangle.h"


using namespace std;

Triangle :: Triangle(int x, int y) : Shape(x,y)
{

}

void Triangle :: draw(Grid &grid)
{
  for (int i = 0; i < 3; ++i)
  {
    if(i == 0)
    {
      grid.set(x + 2, y, '+');
    }
    else if (i == 1)
    {
      grid.set(x + 1, y + 1, '+');
      grid.set(x + 3, y + 1, '+');
    }
    else if (i == 2)
    {
      for(int i = x; i < x + 5; ++i)
      {
        grid.set(i, y + 2, '+');
      }
    }
  }
}
