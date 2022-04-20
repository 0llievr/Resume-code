// Oliver 
#include "symbol.h"
#include <iostream>


#include"Rectangle.h"
#include"Circle.h"
#include"Triangle.h"
#include"Pixmap.h"
#include"Textbox.h"

using std::endl;

Symbol::Symbol(const std::string& myname, double* mydouble)  //for double variable
    :name(myname), type(DOUBLE), value(mydouble), count(0){}

Symbol::Symbol(const std::string& myname, double* mydouble, int mycount) //for double array
  :name(myname), type(DOUBLE), value(mydouble), count(mycount){}

Symbol::Symbol(const std::string& myname, string* mystring) //for string
  :name(myname), type(STRING), value(mystring), count(0){}

Symbol::Symbol(const std::string& myname, string* mystring, int mycount) //for string array
  :name(myname), type(STRING), value(mystring), count(mycount){}

Symbol::Symbol(const std::string& myname, int* myint) //for int
  :name(myname), type(INT), value(myint), count(0){}

Symbol::Symbol(const std::string& myname, int* myint, int mycount) //for int array
  :name(myname), type(INT), value(myint), count(mycount){}

Symbol::Symbol(const std::string& myname, Rectangle* myrectangle ) //for Rectangle
  :name(myname), type(RECTANGLE), value(myrectangle), count(0){}

Symbol::Symbol(const std::string& myname, Rectangle* myrectangle, int mycount)//for Rectangle array
  :name(myname), type(RECTANGLE), value(myrectangle), count(mycount){}

Symbol::Symbol(const std::string& myname, Circle* mycircle) //for circle
  :name(myname), type(CIRCLE), value(mycircle), count(0){}

Symbol::Symbol(const std::string& myname, Circle* mycircle, int mycount) //for circle array
  :name(myname), type(CIRCLE), value(mycircle), count(mycount){}

Symbol::Symbol(const std::string& myname, Triangle* mytriangle) //for triangle
  :name(myname), type(TRIANGLE), value(mytriangle), count(0){}

Symbol::Symbol(const std::string& myname, Triangle* mytriangle, int mycount)//for triangle array
  :name(myname), type(TRIANGLE), value(mytriangle), count(mycount){}

Symbol::Symbol(const std::string& myname, Pixmap* mypixmap) //for pixmap
  :name(myname), type(PIXMAP), value(mypixmap), count(0){}

Symbol::Symbol(const std::string& myname, Pixmap* mypixmap, int mycount)//for pixmap array
  :name(myname), type(PIXMAP), value(mypixmap), count(mycount){}

Symbol::Symbol(const std::string& myname, Textbox* mytextbox) //for Textbox
  :name(myname), type(TEXTBOX), value(mytextbox), count(0){}

Symbol::Symbol(const std::string& myname, Textbox* mytextbox, int mycount)//for Textbox array
  :name(myname), type(TEXTBOX), value(mytextbox), count(mycount){}

Symbol::Symbol(const std::string& name, Animation_code* myAC) //for animation code
    : name(name), type(ANIMATION_CODE), value(myAC), count(0){}

Symbol::Symbol(const std::string& myname, Gpl_type type, Game_object* argument) //for game objects
    :name(myname), type(type), value(argument), count(0){}

 

Symbol::~Symbol(){
    string tmp = gpl_type_to_string(type);
    if(tmp == "double"){
        if(count == 0){//double
            delete(value.double_ptr);
        }else{//double array
                delete [] value.double_ptr;
        }
    }else if(tmp == "string"){
        if(count == 0){//string
            delete(value.string_ptr);
        }else{//string array
                delete [] value.string_ptr;
        }
    }else if(tmp == "int"){
        if(count == 0){//int
            delete(value.int_ptr);
        }else{//int array
                delete [] value.int_ptr;
        }            
    }else if(tmp == "rectangle"){
        if(count == 0){
            delete(value.rectangle_ptr);
        }else{
                delete [] value.rectangle_ptr;
        }            
    }else if(tmp == "circle"){
        if(count == 0){
            delete(value.circle_ptr);
        }else{
                delete [] value.circle_ptr;
        }            
    }else if(tmp == "triangle"){
        if(count == 0){
            delete(value.triangle_ptr);
        }else{
                delete [] value.triangle_ptr;
        }            
    }else if(tmp == "textbox"){
        if(count == 0){
            delete(value.textbox_ptr);
        }else{
                delete [] value.textbox_ptr;
        }            
    }else if(tmp == "pixmap"){
        if(count == 0){//int
            delete(value.pixmap_ptr);
        }else{
                delete [] value.pixmap_ptr;
        }            
    }else if(tmp == "animation code"){ //throws a warning that it might not work but it does
        if(count == 0){
            delete(value.animation_code_ptr);
        }         
    }else if(tmp == "game object"){
        if(count == 0){
            delete(value.game_object_ptr);
        }           
    }else{
        std::cout << "Symbol destructor: " << tmp << std::endl;
    }
}


std::ostream& operator<<(std::ostream& os, const Symbol& mysymbol){
    
    string tmp = gpl_type_to_string(mysymbol.type);

    if(tmp == "double"){ //double
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name << " = " 
                << *mysymbol.value.double_ptr << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" << " = " 
                    << mysymbol.value.double_ptr[i] << endl;
            }
        } 
    }else if(tmp == "string"){ //string
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name << " = \"" 
                << *mysymbol.value.string_ptr << "\"" << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" << " = \"" 
                    << mysymbol.value.string_ptr[i] << "\"" << endl;
            } 
        }
    }else if(tmp == "int"){ //int
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name << " = " 
                << *mysymbol.value.int_ptr << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" 
                    << " = " << mysymbol.value.int_ptr[i] << endl;
            }
        }
    }else if(tmp == "rectangle"){ //int
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name << *mysymbol.value.rectangle_ptr << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" 
                    << *(mysymbol.value.rectangle_ptr+i) << endl;
            }
        }
    }else if(tmp == "circle"){ //int
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name << *mysymbol.value.circle_ptr << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" 
                    << *(mysymbol.value.circle_ptr+i) << endl;
            }
        }
    }else if(tmp == "triangle"){ //int
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name << *mysymbol.value.triangle_ptr << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" 
                    << *(mysymbol.value.triangle_ptr+i) << endl;
            }
        }
    }else if(tmp == "pixmap"){ //int
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name << *mysymbol.value.pixmap_ptr << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" 
                    << *(mysymbol.value.pixmap_ptr+i) << endl;
            }
        }
    }else if(tmp == "textbox"){ //int
        if(mysymbol.count == 0){
            os << tmp << " " << mysymbol.name  << *mysymbol.value.textbox_ptr << endl;
        }else{
            for(int i = 0; i < mysymbol.count; i++){ //array pointer looper
                os << tmp << " " << mysymbol.name << "[" << i << "]" 
                    << *(mysymbol.value.textbox_ptr+i) << endl;
            }
        }
    }else if(tmp == "animation code"){
        os << tmp << " " << mysymbol.name  << endl;
    }else{
        printf("fuck\n");
    }
    return os;
}

//non-array: int, double, or string
const Constant* Symbol::as_constant() const{
    string tmp = gpl_type_to_string(type);
    if(tmp == "double"){
        return new Double_constant(*value.double_ptr);
    }else if(tmp == "string"){
        return new String_constant(*value.string_ptr);
    }else if(tmp == "int"){
        return new Integer_constant(*value.int_ptr);
    }else if(tmp == "rectangle"){
        return new Game_object_constant(value.triangle_ptr);
    }else if(tmp == "circle"){
        return new Game_object_constant(value.circle_ptr);
    }else if(tmp == "triangle"){
        return new Game_object_constant(value.triangle_ptr);
    }else if(tmp == "pixmap"){
        return new Game_object_constant(value.pixmap_ptr);
    }else if(tmp == "textbox"){
        return new Game_object_constant(value.pixmap_ptr);
    }else if(tmp == "animation code"){
        return new Animation_block_constant(value.animation_code_ptr);
    }else{
        throw type;
    }
}

//array: int, double, or string
const Constant* Symbol::as_constant(int index) const {
    string tmp = gpl_type_to_string(type);
    if(index > count) {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, name, std::to_string(index));
        return nullptr;
    }else if(tmp == "double"){
        return new Double_constant(value.double_ptr[index]);
    }else if(tmp == "string"){
        return new String_constant(value.string_ptr[index]);
    }else if(tmp == "int"){
        return new Integer_constant(value.int_ptr[index]);
    }else if(tmp == "rectangle"){
        return new Game_object_constant(value.triangle_ptr+index);
    }else if(tmp == "circle"){
        return new Game_object_constant(value.circle_ptr+index);
    }else if(tmp == "triangle"){
        return new Game_object_constant(value.triangle_ptr+index);
    }else if(tmp == "pixmap"){
        return new Game_object_constant(value.pixmap_ptr+index);
    }else if(tmp == "textbox"){
        return new Game_object_constant(value.pixmap_ptr+index);
    }else{
        throw type;
    }
}

// non-arrays: game objects
const Constant* Symbol::as_constant(const std::string attribute_name) const{
   string tmp = gpl_type_to_string(type);
   
   if(tmp == "rectangle"){
       return new Game_attribute_constant(value.rectangle_ptr, attribute_name);
   }else if(tmp == "circle"){
       return new Game_attribute_constant(value.circle_ptr, attribute_name);
   }else if(tmp == "triangle"){
       return new Game_attribute_constant(value.triangle_ptr, attribute_name);
   }else if (tmp == "pixmap"){
       return new Game_attribute_constant(value.pixmap_ptr, attribute_name);
   }else if(tmp == "textbox"){
       return new Game_attribute_constant(value.textbox_ptr, attribute_name);
   }else{
       throw type;
   }
}

//array: game objects
const Constant* Symbol::as_constant(int index, const std::string attribute_name) const{
   string tmp = gpl_type_to_string(type);
   
   if(index > count || index < 0) {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, name, std::to_string(index));
        return nullptr;
   }else if(tmp == "rectangle"){
       return new Game_attribute_constant(value.rectangle_ptr+index, attribute_name);
   }else if(tmp == "circle"){
       return new Game_attribute_constant(value.circle_ptr+index, attribute_name);
   }else if(tmp == "triangle"){
       return new Game_attribute_constant(value.triangle_ptr+index, attribute_name);
   }else if (tmp == "pixmap"){
       return new Game_attribute_constant(value.pixmap_ptr+index, attribute_name);
   }else if(tmp == "textbox"){
       return new Game_attribute_constant(value.textbox_ptr+index, attribute_name);
   }else{
       throw type;
   }
} 

//non-array: int, double, or string
std::shared_ptr<Locator> Symbol::as_lvalue(){
   string tmp = gpl_type_to_string(type);
    if(tmp == "int"){
			return std::make_shared<Integer_locator>(*value.int_ptr);
    }else if(tmp == "double"){
			return std::make_shared<Double_locator>(*value.double_ptr);
    }else if(tmp == "string"){
			return std::make_shared<String_locator>(*value.string_ptr);
    }else if(tmp == "animation code"){
        return std::make_shared<Animation_block_locator>(value.animation_code_ptr);
    }else{
        throw type;
    }
}

//array: int, double, or string
std::shared_ptr<Locator> Symbol::as_lvalue(int index){
   string tmp = gpl_type_to_string(type);
    if(index >= count || index < 0) {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS,
                name, std::to_string(index));
        return nullptr;
    }else if(tmp == "int"){
            return std::make_shared<Integer_locator>(value.int_ptr[index]);
    }else if(tmp == "double"){
            return std::make_shared<Double_locator>(value.double_ptr[index]);
    }else if(tmp == "string"){
            return std::make_shared<String_locator>(value.string_ptr[index]);
    }else{
        throw type;
    }
}

//non-array: game object
std::shared_ptr<Locator> Symbol::as_lvalue(const std::string& attribute_name){
    string tmp = gpl_type_to_string(type);
    if(tmp == "rectangle"){
			return std::make_shared<Game_attribute_locator>
                (value.rectangle_ptr, attribute_name);
    }else if(tmp == "circle"){
			return std::make_shared<Game_attribute_locator>
                (value.circle_ptr, attribute_name);
    }else if(tmp == "triangle"){
			return std::make_shared<Game_attribute_locator>
                (value.triangle_ptr, attribute_name);
    }else if(tmp == "pixmap"){
			return std::make_shared<Game_attribute_locator>
                (value.pixmap_ptr, attribute_name);
    }else if(tmp ==  "textbox"){
			return std::make_shared<Game_attribute_locator>
                (value.textbox_ptr, attribute_name);
    }else if(tmp ==  "Animation"){
			return std::make_shared<Game_attribute_locator>
                (value.textbox_ptr, attribute_name);
    }else{
        throw type;
    }
}

//array: game object
std::shared_ptr<Locator> Symbol::as_lvalue(int index, const std::string& attribute_name){
    string tmp = gpl_type_to_string(type);
    if(index >= count || index < 0) {
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS,
                name, std::to_string(index));
        return nullptr;
    }else if(tmp == "rectangle"){
            return std::make_shared<Game_attribute_locator>
                (value.rectangle_ptr+index, attribute_name);
    }else if(tmp == "circle"){
            return std::make_shared<Game_attribute_locator>
                (value.circle_ptr+index, attribute_name);
    }else if(tmp == "triangle"){
            return std::make_shared<Game_attribute_locator>
                (value.triangle_ptr+index, attribute_name);
    }else if(tmp == "pixmap"){
            return std::make_shared<Game_attribute_locator>
                (value.pixmap_ptr+index, attribute_name);
    }else if(tmp == "textbox"){
            return std::make_shared<Game_attribute_locator>
                (value.textbox_ptr+index, attribute_name);
    }else{
        throw type;
    }
}


















/*
using std::cout;
int main() // to compile g++ symbol.cpp gpl_type.cpp
{    
//test doubles
  double* doneofem=new double(3.141592);
  double* dbunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  Symbol one("pi", doneofem);
  Symbol two("racetimes", dbunchofem, 4);
  cout << one << endl;
  cout << two << endl;
//test strings
  string* soneofem=new string("benis");
  string* sbunchofem=new string[4] {"wenis", "femis", "squeemish", "coc"};
  Symbol three("penis", soneofem);
  Symbol four("peni", sbunchofem, 4);
  cout << three << endl;
  cout << four << endl;
//test int
  int* ioneofem=new int(420);
  int* ibunchofem=new int[4] {69, 666, 710, 64209};
  Symbol five("fourtwenty", ioneofem);
  Symbol six("memenumb",ibunchofem, 4);
  cout << five << endl;
  cout << six << endl;
}
*/






