//Oliver
#ifndef STATEMENT_H
#define STATEMENT_H

class Expression;
class Variable;
class Statement {
  public:
    void append_statement(Statement* atend);
    Statement():next(nullptr) {}
    virtual void execute() const=0;
    virtual ~Statement(){}
  protected:
    Statement* next;
};

class Print : public Statement {
  public:
    Print(int line_number, const Expression* argument) 
        : line_number(line_number), argument(argument){}
    virtual void execute() const;
    ~Print(){};
  private:
    int line_number;
    const Expression* argument;
};

class Assign : public Statement {
  public:
    Assign(Variable* lhs, Expression* rhs) 
      : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Assign(){};
  private: 
    Variable* lhs;
    Expression* rhs;
};

class NullStatement : public Statement {
  public:
    NullStatement(){}
    virtual void execute() const{};
};

class If : public Statement {
    public:
        If(Expression* expression_Ptr, Statement* ifClause) 
          : expression_Ptr(expression_Ptr), ifClause(ifClause), elseClause(nullptr){}
        If(Expression* expression_Ptr, Statement* ifClause, Statement* elseClause) 
          : expression_Ptr(expression_Ptr), ifClause(ifClause), elseClause(elseClause){}
        virtual void execute() const;
        virtual ~If(){};
    private:
        Expression* expression_Ptr;
        Statement* ifClause;
        Statement* elseClause;
};

class For : public Statement {
    public:
        For(Statement* init, Expression* condition, Statement* inc, Statement* body) 
          : init(init), condition(condition), inc(inc), body(body) {}
        virtual void execute() const;
        virtual ~For(){};
    private:
        Statement* init;
        Expression* condition;
        Statement* inc;
        Statement* body;
        
};

class Exit : public Statement {
    public:
        Exit(int line_numb, Expression* status) 
          : line_numb(line_numb), status(status){}
        virtual void execute() const;
        virtual ~Exit(){};
    private:
        int line_numb;
        Expression* status;
};

#endif
