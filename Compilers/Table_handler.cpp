//Oliver
#include"table_handler.h"


Table_handler& Table_handler::instance(){
  //Making this variable static gives it global scope
  //with visibility local to this function
  static Table_handler the_instance;
  return the_instance;
}

void Table_handler::push_table(){ 
//Create a new Symbol_table and push_back onto the vector.
    tables.push_back(std::shared_ptr<Symbol_table>(new Symbol_table()));
}

void Table_handler::pop_table(){ 
//If more than one table is on the vector pop_back() to remove it. If there is only one table on the vector, throw an exception
    if(tables.size() > 1){
        tables.pop_back();
    }else if(tables.size() == 1){
        throw std::underflow_error("Can't pop global symbol table");
    }else{
        printf("getfucked\n");
    }
    
}

bool Table_handler::insert(std::shared_ptr<Symbol> sym){ 
//Add a symbol to the top/last/back table in the vector via a call to Symbol_table::insert. Return the value that Symbol_table::insert returns.
//You're just supposed to call the function insert() onto the last table in the vector of tables in the Table_handler class and return whatever that function call returns because it will return whether or not the insert was successful.
    return tables.back()->insert(sym);
}

std::shared_ptr<Symbol> Table_handler::lookup(const std::string& name){ 
//Iterate through the symbol table vector from back to front, calling Symbol_table::lookup on each. 
//Return the first match found. Return nullptr if the symbol is undefined.

    for(int i = tables.size(); i > 0; i-- ){ //iterate though table
        auto rtn = tables[i-1]->lookup(name); //lookup in symbol table
        if(rtn != nullptr){ //if not exist then check next
            return rtn;
        }
    }
    return nullptr; //if not found return null

}

bool Table_handler::defined_in_current_scope(const std::string& name){ 
//Search the top/last/back table for the named symbol. 
//Return true if it is defined, false otherwise. Used to check for variable redefinition errors.

    if(tables.back()->lookup(name) != nullptr){
        return true;
    }else{
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const Table_handler& sh){ 
//Iterate through the symbol tables from back to front, printing each
    for(int i = sh.tables.size(); i-- > 0;){
        os << *sh.tables[i]; //use symbol.cpp print
    }
    return os;
}

Table_handler::Table_handler(){
    push_table();
}

void Table_handler::erase(const std::string& name){
    for (auto mytable = tables.rbegin(); mytable != tables.rend(); mytable++){
        if((*mytable)->lookup(name)){
            (*mytable)->erase(name);
            return;
        }
    }
}

/*
#include<iostream>
using namespace std;

int main(){
  Table_handler& symtab = Table_handler::instance();

  double* double_oneofem=new double(3.141592);
  double* double_bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  string* string_oneofem=new string("hi there");
  string* string_bunchofem=new string[4]
    {"one", "two two", "three three three", "fo fo fo fo"};
  int* int_oneofem=new int(321);
  int* int_bunchofem=new int[4] {12, 34, 56, 78};

  symtab.insert(std::make_shared<Symbol>("alpha", string_oneofem));
  symtab.insert(std::make_shared<Symbol>("gamma", string_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("beta", double_oneofem));
  symtab.insert(std::make_shared<Symbol>("delta", double_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("zeta", int_oneofem));
  symtab.insert(std::make_shared<Symbol>("eta", int_bunchofem, 4));

//breaks here
  cout << symtab << endl;
  
  return 0;
}
*/

