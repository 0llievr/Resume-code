//Oliver Lynch
#include"stampstream.h"

ostream& endrow(ostream& os){
    os.flush(); //clear the buffer before advancing the new line
    static_cast<stampbuf*>( os.rdbuf())->incremnet_row();
    return os;
}

row::row(int r)
    :row_numb(r)
{}


ostream& operator<<(ostream& os, const row& myrow){
    os.flush(); //clear the buffer before advancing the new line
    static_cast<stampbuf*>( os.rdbuf())->set_row(myrow.row_numb);
    return os;
}

stampstream::stampstream(int x, int y)
    : sbp(new stampbuf(x,y))
{ rdbuf(sbp); }

stampstream::~stampstream(){
    delete sbp;
}

 