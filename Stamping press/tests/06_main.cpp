#include "stampstream.h"

int main()
{
  stampstream s(30,10);

  for(int i=0; i<10; ++i)
  {
    for(int j=0; j<30; ++j)
      s << j%10;
    s << endrow;
  }
  return 0;
}
