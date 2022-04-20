#include "../stampstream.h"

int main()
{
  stampstream s(30,10);
  s << 'a' << endrow << 'e' << endrow << 
       'i' << endrow << 'o' << endrow << 'u';
  return 0;
}
