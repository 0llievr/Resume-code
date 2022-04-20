//grid.h
//Olynch
//Oliver Thurston Lynch

#ifndef GRID
#define GRID

#include <iostream>
using namespace std;

class Grid
{
private:
  char grid[60][24];

public:
  Grid();
  void set(int x, int y, char c);
  void print();
};

#endif
