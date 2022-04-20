//Oliver Lynch
#include<iostream>
#include <ctype.h>
#include <stdio.h>

#include"stamp.h"

using namespace std;

#ifndef STAMPBUF_H 
#define STAMPBUF_H 

#define BUFSIZE 10

class stampbuf : public streambuf{
    public:
        stampbuf(int, int);
        ~stampbuf();
        int_type sync();
        int_type overflow(int_type);
        void incremnet_row();
        void set_row(int);
    private:
        int plate_x;
        int plate_y;
        int cur_x;
        int cur_y;
        char buf[BUFSIZE];
};

#endif