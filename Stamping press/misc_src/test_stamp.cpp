// Version 08/2021
//From this directory: g++ -I.. -std=c++17 ../stamp.cpp test_stamp.cpp

#include <iostream>
#include "stamp.h"
#include <stdexcept>

using namespace stamping_press;

int main()
{
  try{
    insert_plate(9,9);
    set_die('T');
    stamp(5,8);
    set_die('o');
    stamp(6,8);
    set_die('d');
    stamp(7,8);
    stamp(8,8);
    // stamp(9,8); // Uncomment this to throw exception
    eject_plate();
  }
  catch(std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
  return 0; 
}
