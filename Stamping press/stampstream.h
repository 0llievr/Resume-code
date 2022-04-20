//Oliver Lynch
#include<iostream>
#include"stampbuf.h"
using namespace std;


ostream& endrow(ostream& os);

#ifndef ROW_H 
#define ROW_H

class row{
    public:
        row(int);
        friend ostream& operator<<(ostream& os, const row& myrow);
    private:
        int row_numb;
};

#endif



#ifndef STAMPS_H 
#define STAMPS_H

class stampstream : public ostream{
    public:
        stampstream(int x, int y);
        ~stampstream();
    private:
        stampbuf* sbp;
        row* myrow;
};

#endif



