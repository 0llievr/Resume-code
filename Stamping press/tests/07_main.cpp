#include "stampstream.h"

int main()
{
  stampstream s(30,10);

  s << row(-5);
  s << "DOES NOT COMPUTE!";
  s << row(5);
  s << "-->COMPUTES WITH STYLE!<--";
  return 0;
}
