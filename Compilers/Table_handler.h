//Oliver
#ifndef TABLE_HANDLER_H
#define TABLE_HANDLER_H

#include<vector>
#include<stdexcept>
#include"Symbol_table.h"
#include"Symbol.h"

class Table_handler{
  public:
    // This function retrieves the Sample_singleton instance. 
    // It is a static member function--it is not associated with 
    // an instance (an object) of the class. 
    // Think of it as a "Traditional, C-style" function that is in the
    // Sample_singleton namespace
    static Table_handler& instance(); //Return the singleton instance.
    void push_table(); //Create a new Symbol_table and push_back onto the vector.
    void pop_table(); //If more than one table is on the vector pop_back() to remove it. If there is only one table on the vector, throw an exception:
    bool insert(std::shared_ptr<Symbol> sym); //Add a symbol to the top/last/back table in the vector via a call to Symbol_table::insert. Return the value that Symbol_table::insert returns.
    std::shared_ptr<Symbol> lookup(const std::string& name); //Iterate through the symbol table vector from back to front, calling Symbol_table::lookup on each. Return the first match found. Return nullptr if the symbol is undefined.
    bool defined_in_current_scope(const std::string& name); //Search the top/last/back table for the named symbol. Return true if it is defined, false otherwise. Used to check for variable redefinition errors.
    friend std::ostream& operator<<(std::ostream& os, const Table_handler& sh); //Iterate through the symbol tables from back to front, printing each
    void erase(const std::string& name);
    
    //The copy constructor and assignment operator are compiler-generated
    //functions. Here the compiler is instructed not to generate these
    //functions.  This is useful for all classes that don't explicitly 
    //require these functions (not just singletons).
    Table_handler(const Table_handler&) = delete;
    Table_handler& operator=(const Table_handler&) = delete;

  private:

    //The Table_handler default constructor should simply call push_table(). This pushes an initial Symbol_table object onto the vector, representing the global namespace (to hold global variables).
    //Any private data you require for your class
    std::vector< std::shared_ptr<Symbol_table> > tables;

    //Make the default constructor private. Only the static
    //variable object (See Sample_singleton::instance() function) 
    //has access to this private function, allowing it to be constructed.
    Table_handler(); // {push_table();}
};

#endif
