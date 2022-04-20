#include "stampstream.h"

int main()
{
  stampstream s(30,10);

  s << "!@#$%^&*()_+{}[]\\|"
    << ";':\",./<>?";
  return 0;
}
