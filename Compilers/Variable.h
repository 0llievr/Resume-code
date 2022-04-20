//Oliver
#ifndef VAARIABLE_H_
#define VAARIABLE_H_

#include <memory>
#include "Expression.h"
#include "Table_handler.h"
#include "Symbol.h"
#include "Locator.h"

class Variable : public Expression {
  public:
    // initialize unused array_index_expression to nullptr
    Variable(const std::string& symbol_name);

    // initialize array_index_expression to index_expr
    Variable(const std::string& symbol_name, Expression* index_expr);

    virtual const Constant* evaluate() const;
    virtual const shared_ptr<Locator> modify() const; //my function
    virtual Gpl_type type() const;
    virtual string get_name() const { return symbol_name; }
    virtual ~Variable();

    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;
  protected: //allow derived class access

    std::string symbol_name;
    Expression* array_index_expression;

    //The symbol() function eases access to the symbol
    //use it within Variable's member functions
    std::shared_ptr<Symbol> symbol()
    { return Table_handler::instance().lookup(symbol_name); }
    std::shared_ptr<Symbol> symbol() const
    { return Table_handler::instance().lookup(symbol_name); }
};

class Member_variable : public Variable{
  public:
    // initialize unused array_index_expression to nullptr
    Member_variable(const std::string& symbol_name, const std::string& addribute_name);
    // initialize array_index_expression to index_expr
    Member_variable(const std::string& symbol_name, const std::string& addribute_name, Expression* index_expr);
    virtual const Constant* evaluate() const override;
    virtual const shared_ptr<Locator> modify() const override;
    virtual Gpl_type type() const override;
    virtual string get_name() const override { return symbol_name + "." + attribute; }

    Member_variable(const Variable&) = delete;
    Member_variable& operator=(const Variable&) = delete;
  private:
    std::string attribute;
};


#endif
