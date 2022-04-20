#include "../stampstream.h"

int main()
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
