//Oliver
#ifndef SYMBOL_H
#define SYMBOL_H


#include "Constant.h"
#include "gpl_type.h"
#include "error.h"
#include <string>
//p4
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Pixmap.h"
#include "Textbox.h"
#include "Locator.h"


using std::string;

class Rectangle;
class Circle;
class Triangle;
class Pixmap;
class Textbox;

class Symbol{
    protected:
        union symbol_type{
            //value pointers
            double *double_ptr;
            int *int_ptr;
            string *string_ptr;
            Rectangle *rectangle_ptr;
            Circle *circle_ptr;
            Triangle *triangle_ptr;
            Pixmap *pixmap_ptr;
            Textbox *textbox_ptr;
            Animation_code *animation_code_ptr;
            Game_object *game_object_ptr;

            //constructors for symbol type
            symbol_type(double *val) : double_ptr(val){};
            symbol_type(int *val) : int_ptr(val){};
            symbol_type(string *val) : string_ptr(val){};
            symbol_type(Rectangle *val) : rectangle_ptr(val){};
            symbol_type(Circle *val) : circle_ptr(val){};
            symbol_type(Triangle*val) : triangle_ptr(val){};
            symbol_type(Pixmap *val) : pixmap_ptr(val){};
            symbol_type(Textbox *val) : textbox_ptr(val){};
            symbol_type(Animation_code* val) : animation_code_ptr(val) {}
            symbol_type(Game_object* val) : game_object_ptr(val) {}

        };
        
        // private values
        std::string name; //the name of the variable
        Gpl_type type;  //the type of the variable. See gpl_type.h
        symbol_type value; //the contents of the variable (above)(int, double, or string) or array of same
        int count; //used to store the size if the variable is an array

    public:
        //symbol constructors
        Symbol(const std::string& myname, double* mydouble); //for double variable
        Symbol(const std::string& myname, double* mydouble, int mycount); //for double array

        Symbol(const std::string& myname, string* mystring); //for string
        Symbol(const std::string& myname, string* mystring, int mycount); //for string array

        Symbol(const std::string& myname, int* myint); //for int
        Symbol(const std::string& myname, int* myint, int mycount);//for int array

        Symbol(const std::string& myname, Rectangle* myrectangle ); //for Rectangle
        Symbol(const std::string& myname, Rectangle* myrectangle, int mycount);//for Rectangle array

        Symbol(const std::string& myname, Circle* mycircle); //for circle
        Symbol(const std::string& myname, Circle* mycircle, int mycount);//for circle array

        Symbol(const std::string& myname, Triangle* mytriangle); //for triangle
        Symbol(const std::string& myname, Triangle* mytriangle, int mycount);//for triangle array

        Symbol(const std::string& myname, Pixmap* mypixmap); //for pixmap
        Symbol(const std::string& myname, Pixmap* mypixmap, int mycount);//for pixmap array

        Symbol(const std::string& myname, Textbox* mytextbox); //for Textbox
        Symbol(const std::string& myname, Textbox* mytextbox, int mycount);//for Textbox array

        Symbol(const std::string& name, Animation_code* value); //for animation code

        Symbol(const std::string& name, Gpl_type type, Game_object* argument); //for game object

        //public functions
        Gpl_type get_type() const{return type;};
        std::string get_name() const{return name;};
        int get_count(){return count;};
        virtual ~Symbol();
        friend std::ostream& operator<<(std::ostream& os, const Symbol&);

        //P3
        const Constant* as_constant() const; //Symbol
        const Constant* as_constant(int index) const; //Symbol array

        //P4
        const Constant* as_constant(const std::string attribute_name) const; // non-arrays
        const Constant* as_constant(int index, const std::string attribute_name) const; // arrays

        //P5
        std::shared_ptr<Locator> as_lvalue();//non-array: object
        std::shared_ptr<Locator> as_lvalue(int index); //array object
        std::shared_ptr<Locator> as_lvalue(const std::string& attribute_name); //non-array gmae object
        std::shared_ptr<Locator> as_lvalue(int index, const std::string& attribute_name); //array game object

        //prevent compiler from generating these functions
        Symbol(const Symbol&) = delete;
        Symbol& operator=(const Symbol&) = delete;
    
};

class Reference : public Symbol {
  public:
    Reference(const std::string& parameter_name,
              Gpl_type           parameter_type,
              Game_object*       gop)
    : Symbol(parameter_name, parameter_type, gop) {}
    virtual ~Reference() { value.game_object_ptr=nullptr; }
};

#endif
