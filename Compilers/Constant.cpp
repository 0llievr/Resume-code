//File: Constant.cpp
//Oliver
#include "Constant.h"

Gpl_type  Constant::type() const 
{ return intrinsic_type; }

const Constant* Constant::evaluate() const
{ return this; }

int Game_attribute_constant::as_int() const{
    if(gop->attribute_type(attribute_name) == INT){
        int rtn;
        gop->read_attribute(attribute_name, rtn);
        return rtn;
    }else{
        throw type();
    }
}

double Game_attribute_constant::as_double() const{
    if(gop->attribute_type(attribute_name) == INT){
        int rtn;
        gop->read_attribute(attribute_name, rtn);
        return rtn;
    }else if(gop->attribute_type(attribute_name) == DOUBLE){
        double rtn;
        gop->read_attribute(attribute_name, rtn);
        return rtn;
    }else{
        throw type();
    }
}

std::string Game_attribute_constant::as_string() const{
    if(gop->attribute_type(attribute_name) == INT){
        int rtn;
        gop->read_attribute(attribute_name, rtn);
        return std::to_string(rtn);
    }else if(gop->attribute_type(attribute_name) == DOUBLE){
        double rtn;
        gop->read_attribute(attribute_name, rtn);
        return std::to_string(rtn);
    }else if(gop->attribute_type(attribute_name) == STRING){
        std::string rtn;
        gop->read_attribute(attribute_name, rtn);
        return rtn;
    }else{
        throw type();
    }
}

const Animation_code* Game_attribute_constant::as_animation_block() const{
    if(gop->attribute_type(attribute_name) == ANIMATION_BLOCK){
          Animation_code* rtn;
          gop->read_attribute(attribute_name, rtn);
          return rtn;
    }else{
          throw(Constant::type());
    }
}




