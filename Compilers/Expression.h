//File: Expression.h
//Oliver
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "gpl_type.h"
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    virtual const Constant* evaluate() const=0;
    virtual Gpl_type type() const=0;
    virtual ~Expression();
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
  protected:
    //a wrapper around returned constants
    const Constant* ret(const Constant* new_evald_constant) const;
    //keep pointer to evaluate's created constant it can be released
    mutable const Constant* evaluated_constant;
};

class Binary_operator : public Expression {
  public:
    Binary_operator(Expression* lhs, Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Binary_operator() { delete lhs; delete rhs; }
  protected:
    const Expression* lhs;
    const Expression* rhs;
};

class Unary_operator : public Expression {
  public:
    Unary_operator(Expression* op): op(op){}
    virtual const Constant* evaluate() const  = 0;
    virtual ~Unary_operator(){delete op;}
  protected:
    Expression* op;
};

class Plus : public Binary_operator {
  public:
    Plus(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Or : public Binary_operator {
  public:
    Or(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class And : public Binary_operator {
  public:
    And(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Less_equal : public Binary_operator {
  public:
    Less_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Greater_equal : public Binary_operator {
  public:
    Greater_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Less : public Binary_operator {
  public:
    Less(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Greater : public Binary_operator {
  public:
    Greater(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Equal : public Binary_operator {
  public:
    Equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Not_equal : public Binary_operator {
  public:
    Not_equal(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Minus : public Binary_operator {
  public:
    Minus(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Divide : public Binary_operator {
  public:
    Divide(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Mod : public Binary_operator {
  public:
    Mod(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Unary_minus : public Unary_operator {
  public:
    Unary_minus(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Not : public Unary_operator {
  public:
    Not(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Sin : public Unary_operator {
  public:
    Sin(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Cos : public Unary_operator {
  public:
    Cos(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Tan : public Unary_operator {
  public:
    Tan(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Arcsin : public Unary_operator {
  public:
    Arcsin(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Arccos : public Unary_operator {
  public:
    Arccos(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Arctan : public Unary_operator {
  public:
    Arctan(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Square_root : public Unary_operator {
  public:
    Square_root(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Floor : public Unary_operator {
  public:
    Floor(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Absolute_value : public Unary_operator {
  public:
    Absolute_value(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Random : public Unary_operator {
  public:
    Random(Expression* op) : Unary_operator(op){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Near : public Binary_operator {
  public:
    Near(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

class Touches : public Binary_operator {
  public:
    Touches(Expression* lhs, Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual Gpl_type type() const;
};

#endif
