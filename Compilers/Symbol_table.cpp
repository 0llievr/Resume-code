//Oliver
#include"Symbol_table.h"
#include <vector>
#include <algorithm>// std::sort

std::shared_ptr<Symbol> Symbol_table::lookup(const std::string& name) {    //Return the named Symbol object if it is found in the unordered_map, and nullptr otherwise.
    //Note that unordered_map::find() should be used to search the keys for the symbol’s name.
    auto search = symbols.find(name);
    if(search != symbols.end()){
        return(search->second); //return the shared ptr in the map
    }else{ //not found
        return nullptr;
    }
}

bool Symbol_table :: insert(std::shared_ptr<Symbol> sym){
    //If the Symbol input parameter already exists in the unordered_map return false. Otherwise add the Symbol to the map and return true.
   /*
    string name = sym->get_name();
    
    if(symbols.find(name)){
        return false;
    }else{
        pair<string, shared_ptr<Symbol>> myinsert (name, sym);
        symbols.insert(myinsert);
        return true;
    }
*/
    return symbols.insert(std::make_pair(sym->get_name(), sym)).second;


}

std::ostream& operator<<(std::ostream& os, const Symbol_table& table){
    //print out values sorted by name

    std::vector<string> keys; // for alphabetical order
    for(auto i : table.symbols){ // = table.begin(); i != table.end(); i++){ //go though table
        keys.push_back(i.first); //add symbol lines to vesctor
    }

    std::sort(keys.begin(), keys.end()); //alphabetical order
    
    for(size_t i=0; i<keys.size(); i++){
        os << *table.symbols.at(keys[i]); 
    }

    return os;
}
/*
#include<iostream>
using namespace std;

int main()
{
  Symbol_table symtab;

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

  cout << symtab << endl;
  return 0;
}
*/
