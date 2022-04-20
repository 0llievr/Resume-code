// File: Expression.cpp
//Oliver
#include "Expression.h"
#include "Constant.h"
#include<string>
#include <time.h>
#include <cmath>
using std::string;

Expression::~Expression(){delete evaluated_constant;}

// This wrapper ensures that Constant objects created by evaluate() are
// properly released when a subsequent call to evaluate() will otherwise
// overwrite the pointer.
const Constant* Expression::ret(const Constant* new_evald_constant) const
{
  delete evaluated_constant;
  return evaluated_constant=new_evald_constant;
}
/**********************************************/
/************* Other operators ****************/
/**********************************************/
#include "error.h"
#include "error.h"

const Constant* Plus::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new String_constant(lhs_constant->as_string() + rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() + rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() + rhs_constant->as_int()));
}

Gpl_type Plus::type() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==STRING || rht==STRING)
    return STRING;
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Multiply::evaluate() const{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() * rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() * rhs_constant->as_int()));
}

Gpl_type Multiply::type() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}





//~~~~~~~~~~~~~~~~~~~Not Given~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


const Constant* Or::evaluate() const{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lhs->type()==DOUBLE || rhs->type()==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() || rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() || rhs_constant->as_int()));
}

Gpl_type Or::type() const{    
  return INT;
}

const Constant* And::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() && rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() && rhs_constant->as_int()));
}

Gpl_type And::type() const{
  return INT;
}

const Constant* Less_equal::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new Integer_constant(lhs_constant->as_string() <= rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() <= rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() <= rhs_constant->as_int()));
}

Gpl_type Less_equal::type() const{
  return INT;
}

const Constant* Greater_equal::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new Integer_constant(lhs_constant->as_string() >= rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() >= rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() >= rhs_constant->as_int()));
}

Gpl_type Greater_equal::type() const{
  return INT;
}

const Constant* Less::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new Integer_constant(lhs_constant->as_string() < rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() < rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() < rhs_constant->as_int()));
}

Gpl_type Less::type() const{
  return INT;
}

const Constant* Greater::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new Integer_constant(lhs_constant->as_string() > rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() > rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() > rhs_constant->as_int()));
}

Gpl_type Greater::type() const{
  return INT;
}

const Constant* Equal::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new Integer_constant(lhs_constant->as_string() == rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() == rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() == rhs_constant->as_int()));
}

Gpl_type Equal::type() const{
  return INT;
}

const Constant* Not_equal::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==STRING || rht==STRING)
    return ret(new Integer_constant(lhs_constant->as_string() != rhs_constant->as_string()));
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Integer_constant(lhs_constant->as_double() != rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() != rhs_constant->as_int()));
}

Gpl_type Not_equal::type() const{
  return INT;
}

const Constant* Minus::evaluate() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==DOUBLE || rht==DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() - rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() - rhs_constant->as_int()));
}

Gpl_type Minus::type() const{
  Gpl_type lht=lhs->type();
  Gpl_type rht=rhs->type();
  if(lht==DOUBLE || rht==DOUBLE)
    return DOUBLE;
  return INT;
}

const Constant* Divide::evaluate() const
{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  
  double rhs_val=rhs_constant->as_double();
  if(!Error::runtime() && rhs_val==0.0){
    Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
    return ret(new Integer_constant(0));
  }else if(lhs->type()==DOUBLE || rhs->type()==DOUBLE){ //if double
    return ret(new Double_constant(lhs_constant->as_double() / rhs_constant->as_double()));
  } //if int
  return ret(new Integer_constant(lhs_constant->as_int() / rhs_constant->as_int()));
}

Gpl_type Divide::type() const{
    Gpl_type lht=lhs->type();
    Gpl_type rht=rhs->type();
    if(lht==DOUBLE || rht==DOUBLE)
        return DOUBLE;
    return INT;
}

const Constant* Mod::evaluate() const{
  const Constant* lhs_constant = lhs->evaluate();
  const Constant* rhs_constant = rhs->evaluate();
  int rhs_int = rhs_constant->as_int();
  
  if(rhs_int == 0){
    Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
    return ret(new Integer_constant(0));
  }
  return ret(new Integer_constant(lhs_constant->as_int() % rhs_constant->as_int()));
}

Gpl_type Mod::type() const{
    Gpl_type lht=lhs->type();
    Gpl_type rht=rhs->type();
    if(lht==DOUBLE || rht==DOUBLE)
        return DOUBLE;
    return INT;
}

const Constant* Unary_minus::evaluate() const{
    const Constant* opc = op->evaluate();
    if(op->type() == DOUBLE)
        return ret(new Double_constant(-1*(opc->as_double())));
    return ret(new Integer_constant(-1*(opc->as_int())));
}

Gpl_type Unary_minus::type() const{
    Gpl_type oppp = op->type();
    if(oppp == DOUBLE)
        return DOUBLE;
    return INT;
}

const Constant* Not::evaluate() const{
  const Constant* opc = op->evaluate();
  if(op->type() == DOUBLE)
    return ret(new Integer_constant(opc->as_double() == 0));
  return ret(new Integer_constant(opc->as_int() == 0));
}

Gpl_type Not::type() const{
  return INT;
}

const Constant* Sin::evaluate() const{
  const Constant* opc = op->evaluate();
  return ret(new Double_constant(std::sin(opc->as_double()*M_PI / 180)));
}

Gpl_type Sin::type() const{
  return DOUBLE;
}

const Constant* Cos::evaluate() const{
    const Constant* opc = op->evaluate();
    return ret(new Double_constant(std::cos(opc->as_double()*M_PI / 180)));
}

Gpl_type Cos::type() const{
    return DOUBLE;
}

const Constant* Tan::evaluate() const{
    const Constant* opc = op->evaluate();
    return ret(new Double_constant(std::tan(opc->as_double()*M_PI / 180)));
}

Gpl_type Tan::type() const{
    return DOUBLE;
}

const Constant* Arcsin::evaluate() const{
    const Constant* opc = op->evaluate();
    return ret(new Double_constant(std::asin(opc->as_double())*180 / M_PI));
}

Gpl_type Arcsin::type() const{
    return DOUBLE;
}

const Constant* Arccos::evaluate() const{
    const Constant* opc = op->evaluate();
    return ret(new Double_constant(std::acos(opc->as_double())*180 / M_PI ));
}

Gpl_type Arccos::type() const{
    return DOUBLE;
}

const Constant* Arctan::evaluate() const{
    const Constant* opc = op->evaluate();
    return ret(new Double_constant(atan(opc->as_double())*180 / M_PI));
}

Gpl_type Arctan::type() const{
    return DOUBLE;
}

const Constant* Square_root::evaluate() const{
    const Constant* opc = op->evaluate();
    if(op->type() == DOUBLE)
        return ret(new Double_constant(sqrt(opc->as_double())));
    return ret(new Double_constant(sqrt(opc->as_int())));
}

Gpl_type Square_root::type() const{
    return DOUBLE;
}
//------------------------------------------
const Constant* Floor::evaluate() const{
  const Constant* opc = op->evaluate();
  if(op->type() == DOUBLE)
    return ret(new Integer_constant((int)floor(opc->as_double())));
  return ret(new Integer_constant((int)floor(opc->as_int())));
}

Gpl_type Floor::type() const{
  return INT;
}

const Constant* Absolute_value::evaluate() const{
  const Constant* opc = op->evaluate();
  if(op->type() == DOUBLE)
    return ret(new Double_constant(fabs(opc->as_double())));
  return ret(new Integer_constant(fabs(opc->as_int())));
}

Gpl_type Absolute_value::type() const{
    Gpl_type opt = op->type();
    if(opt == DOUBLE)
        return DOUBLE;
    return INT;
}

const Constant* Random::evaluate() const{
  const Constant* opc = op->evaluate();
  Gpl_type opt = op->type();
  int max;

  if(opt == INT){
    max = opc->as_int();
    if(max < 1){
      Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, std::to_string(max));
      max = 2;
    }
  }else{
    max = static_cast<int>(floor(opc->as_double()));
      if(max < 1){
          Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, std::to_string(opc->as_double()));
          max = 2;
      }
  }
    return ret(new Integer_constant(rand()%max));

}

Gpl_type Random::type() const{
  return INT;
}


Gpl_type Near::type() const{
  return INT;
}

const Constant* Near::evaluate() const{
  const Game_object* myrhs = rhs->evaluate()->as_game_object();
  return new Integer_constant(lhs->evaluate()->as_game_object()->near(myrhs));
}

Gpl_type Touches::type() const{
  return INT;
}

const Constant* Touches::evaluate() const{
  const Game_object* myrhs = rhs->evaluate()->as_game_object();
  return new Integer_constant(lhs->evaluate()->as_game_object()->touches(myrhs));
}








