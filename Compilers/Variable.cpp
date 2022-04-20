//Oliver
#include "Variable.h"
#include <assert.h>

//Variable ---------------------------------------------------------------------------------
Variable::Variable(const std::string& symbol_name)
    :symbol_name(symbol_name), array_index_expression(nullptr){}
Variable::Variable(const std::string& symbol_name, Expression* index_expr)
    :symbol_name(symbol_name), array_index_expression(index_expr){}
    
const Constant* Variable::evaluate() const {
    if(!array_index_expression){
        if(!symbol()){
            return ret(new Integer_constant(0));
        }else{
            return ret(symbol()->as_constant());
        }
    }

    int index = array_index_expression->evaluate()->as_int();
    const Constant* myconst = symbol()->as_constant(index);

    if(myconst) {
        return ret(myconst);
    }else{
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(index));
        return ret(new Integer_constant(0));
    }
    
}

const shared_ptr<Locator> Variable::modify() const {
    
    if(!array_index_expression){
        return symbol()->as_lvalue();
    }
    int index = array_index_expression->evaluate()->as_int();
    shared_ptr<Locator> lval = symbol()->as_lvalue(index);
    if(lval){
        return lval;
    }else{
        return symbol()->as_lvalue(0);
    }
}

Gpl_type Variable::type() const {
    if(symbol_name == ""){
        return INT;
    }else{
        return symbol()->get_type();
    }
}

Variable::~Variable() {
    delete array_index_expression;
}

//Member_variable ---------------------------------------------------------------------------------
Member_variable::Member_variable(const std::string& symbol_name, const std::string& attribute)
    :Variable(symbol_name), attribute(attribute) {}
Member_variable::Member_variable(const std::string& symbol_name, const std::string& attribute, Expression* index_expr)
    :Variable(symbol_name, index_expr), attribute(attribute) {}

const Constant* Member_variable::evaluate() const {
    if(!array_index_expression){
        return ret(symbol()->as_constant(attribute));
    }
    int index = array_index_expression->evaluate()->as_int();
    const Constant* myconst = symbol()->as_constant(index, attribute);
    if(myconst){
        return ret(myconst); 
    }else{
        Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, symbol_name, std::to_string(index));
        return symbol()->as_constant(0, attribute);
    }
}

const shared_ptr<Locator> Member_variable::modify() const {
    if(!array_index_expression){
        return symbol()->as_lvalue(attribute);
    } 
    int index = array_index_expression->evaluate()->as_int();
    shared_ptr<Locator> myconst = symbol()->as_lvalue(index, attribute);
    if(myconst){
        return myconst;
    }else{
        return symbol()->as_lvalue(0, attribute);
    }
}

Gpl_type Member_variable::type() const {
    const Constant* myconst = nullptr;
    if(array_index_expression == nullptr){
        myconst=symbol()->as_constant(attribute);
    }else{
        myconst=symbol()->as_constant(0, attribute);
    }
    Gpl_type ret_type = myconst->type();
    delete myconst;
    return ret_type;
}
