#include "../stampstream.h"

int main()
{
  stampstream s(30,10);
  s << row(4) << 'a' << row(3) << 'e' << 
       row(2) << 'i' << row(1) << 'o' << 
       row(0) << 'u';
  return 0;
}
