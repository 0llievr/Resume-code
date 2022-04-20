//Oliver Lynch
#include"stampbuf.h"


stampbuf::stampbuf(int x, int y)
    :plate_x(x), plate_y(y), cur_x(0), cur_y(0)
{ 
    stamping_press::insert_plate(plate_x,plate_y);
    setp(buf, &buf[BUFSIZE-1]);
}

stampbuf::~stampbuf(){
    sync(); //get final buffer out
    stamping_press::eject_plate();
}


int stampbuf::sync(){
    //empty char array? -todd notes
    for(char* tmp = pbase(); tmp < pptr(); tmp++ ){ //Loop char in buffer
        //get dye
        try{/*
            if(isspace(*tmp)){ 
            //if its a space advance a space forward
                cur_x++;
            }*/
            if(stamping_press::get_die() != *tmp){
            //set dye if not correct
                stamping_press::set_die(*tmp);
            }
            //stamp
            stamping_press::stamp(cur_x,cur_y);
        }catch(...){}
        cur_x++;//advances a space for when a char is not alowed 
    }
    setp(pbase(), epptr()); //reset buffer boundr to full size of myarray
    return 0;
}

int stampbuf::overflow(int_type c){
    *pptr() = (char)c;
    pbump(1);
    sync();
    return c;
}
void stampbuf::incremnet_row(){
    cur_x = 0;
    cur_y++;
}

void stampbuf::set_row(int row){
    cur_x = 0;
    cur_y = row;
}