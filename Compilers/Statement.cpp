//Oliver
#include<iostream>
#include <cstdlib>
#include "Statement.h"
#include "Constant.h"
#ifdef P5
#include "Locator.h"
#endif
#include "Variable.h"
#include "Window.h"
#include "Event_manager.h"

void Statement::append_statement(Statement* atend){
  Statement* current=this;
  while(current->next)
    current=current->next;
  current->next=atend;
}

void Print::execute() const{
        std::cout << "print[" << line_number << "]: "
            << argument->evaluate()->as_string() << std::endl;
    if(next) next->execute(); 
}

void Assign::execute() const {
    const Constant* myconst = rhs->evaluate();
    Gpl_type mytype = lhs->type();
    if(mytype == INT){ 
        lhs->modify()->mutate(myconst->as_int());
    }else if(mytype == DOUBLE){ 
        lhs->modify()->mutate(myconst->as_double());
    }else if(mytype == STRING){
        lhs->modify()->mutate(myconst->as_string());
    }else if(mytype == ANIMATION_BLOCK){
        lhs->modify()->mutate(myconst->as_animation_block());
        //lhs->mutate(myconst->as_animation_block());

    }
    if(next) next->execute();
}

void If::execute() const {
    if(expression_Ptr->evaluate()->as_int()){
        ifClause->execute();
    }else if(elseClause){
        elseClause->execute();
    }
    if(next) next->execute();
}

void For::execute() const {
  for(init->execute(); condition->evaluate()->as_int(); inc->execute()){
    body->execute();
  }
  if(next) next->execute();
}

void Exit::execute() const {
    Event_manager::instance().execute_handlers(Window::TERMINATE);
    int mystat = status->evaluate()->as_int();
    std::cout << "gpl[" << line_numb << "]: exit(" << mystat << ")" << std::endl;
    exit(mystat);
    if(next) next->execute();
}