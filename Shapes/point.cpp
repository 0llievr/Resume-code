//point.cpp
//Olynch
//Oliver Thurston Lynch

#include <iostream>
#include "point.h"
#include "shape.h"


using namespace std;


Point :: Point(int x, int y, char c) : Shape(x,y)
{
  m_c = c;
}

void Point :: draw(Grid &grid)
{
  if (x <= 60 && y <= 24)
  {
    grid.set(x, y, m_c);
  }
}
