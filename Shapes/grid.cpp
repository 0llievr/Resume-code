//grid.cpp
//Olynch
//Oliver Thurston Lynch

#include <iostream>
#include "grid.h"

using namespace std;

Grid :: Grid()
{
  for (int y = 0; y < 24; y++)
  {
    for (int x = 0; x < 60; x++)
    {
      grid[x][y] = ' ';
    }
  }
}

void Grid :: set(int x, int y, char c)
{
  if(x < 0 || x > 60 || y < 0 || y > 23)
  {
    return;
  }
  else
  {
    grid[x][y] = c;
  }
}

void Grid :: print()
{
  for (int y = 0; y < 24; y++)
  {
    for (int x = 0; x< 60; x++)
    {
      cout << grid[x][y];
    }
    cout << endl;
  }
}
