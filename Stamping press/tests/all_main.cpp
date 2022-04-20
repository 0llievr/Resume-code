//File: all_tests.cpp
#include "stampstream.h"

int main()
{
  {
    stampstream s(30,10);
    s << "hi";
  }
  {
    stampstream s(30,10);
    s << "HiThereThisIsAVeryLongSentenceThatRunsOffTheEdge" << endrow;
    s << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endrow;
    s << "BBBBBBBBBBBBBBBBBBBBBBBBBBB 27" << endrow;
    s << "CCCCCCCCCCCCCCCCCCCCCCCC 24" << endrow;
    s << "DDDDDDDDDDDDDDDDDDDDD 21" << endrow;
    s << "EEEEEEEEEEEEEEEEEE 18" << endrow;
    s << "FFFFFFFFFFFFFFF 15" << endrow;
    s << "GGGGGGGGGGGG 12" << endrow;
    s << "HHHHHHHHH 9" << endrow;
    s << "IIIIII 6" << endrow;
  }
  {
    stampstream s(30,10);
    s << 'a' << endrow << 'e' << endrow << 
      'i' << endrow << 'o' << endrow << 'u';
  }
  {
    stampstream s(30,10);
    s << row(4) << 'a' << row(3) << 'e' << 
      row(2) << 'i' << row(1) << 'o' << 
      row(0) << 'u';
  }
  {
    stampstream s(30,10);
    s << row(4) << row(3) << "ae" << 
      row(2) << row(1) << "io" << 
      row(0) << 'u' << " and sometimes 'y'";
  }
  {
    stampstream s(30,10);

    for(int i=0; i<10; ++i)
    {
      for(int j=0; j<30; ++j)
        s << j%10;
      s << endrow;
    }
  }
  {
    stampstream s(30,10);

    s << row(-5);
    s << "DOES NOT COMPUTE!";
    s << row(5);
    s << "-->COMPUTES WITH STYLE!<--";
  }
  {
    stampstream s(30,10);

    s << "!@#$%^&*()_+{}[]\\|"
      << ";':\",./<>?";
  }
  {
    stampstream s(30,10);

    s << "abcdefgh" << endrow;
    s << "abcdefghi" << endrow;
    s << "abcdefghij" << endrow;
    s << "abcdefghijk" << endrow;
    s << "abcdefghijkl" << endrow;
    s << "abcdefghijklm" << endrow;
    s << "abcdefghijklmn" << endrow;
    s << "abcdefghijklmno" << endrow;
    s << "abcdefghijklmnop" << endrow;
    s << "abcdefghijklmnopq" << endrow;
  }
  {
    stampstream s(30,10);

    s << "                      abcdefgh" << endrow;
    s << "                     abcdefghi" << endrow;
    s << "                    abcdefghij" << endrow;
    s << "                   abcdefghijk" << endrow;
    s << "                  abcdefghijkl" << endrow;
    s << "                 abcdefghijklm" << endrow;
    s << "                abcdefghijklmn" << endrow;
    s << "               abcdefghijklmno" << endrow;
    s << "              abcdefghijklmnop" << endrow;
    s << "             abcdefghijklmnopq" << endrow;
  }
  return 0;
}
