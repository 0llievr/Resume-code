//Oliver
// updated Mon Apr 15 20:43:21 PDT 2019

#include <memory>
#include "Event_manager.h"
using namespace std;


/* static */ Event_manager&  Event_manager::instance(){
  static Event_manager the_manager;
  return the_manager;
}

Event_manager::~Event_manager(){
    for(vector x : keystroke_list){
        for(const Statement* xx : x){
            //delete xx; //breaks test 2 lol 
        }
    }
}

void Event_manager::add_handler(Window::Keystroke keystroke, const Statement* myStatement){
    keystroke_list[keystroke].push_back(myStatement);
}

void Event_manager::execute_handlers(Window::Keystroke keystroke) const{
    for(const Statement* x : keystroke_list[keystroke]){
            x->execute();
        }
}
