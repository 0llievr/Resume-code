//square.cpp
//Olynch
//Oliver Thurston Lynch

#include "square.h"


using namespace std;



Square :: Square(int x, int y, int size) : Shape(x,y)
{
  m_size = size;
}

void Square ::  draw(Grid &grid)
{
  int tmpy = y;

  for(int i = 0; i < m_size; ++i)
  {
    if(tmpy < 0){
      ++tmpy;
  }

  for(int tmpx = x; tmpx <= x + m_size - 1; ++tmpx)
  {
    if(i == 0 || i == m_size - 1 || tmpx == x || tmpx == x + m_size - 1)
    {
      grid.set(tmpx, tmpy, '*');
    }
  }
    ++tmpy;
  }

}
