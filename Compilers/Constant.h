//File: Constant.h
//Oliver
#ifndef CONSTANT_H
#define CONSTANT_H
#include "Expression.h"
#include "Game_object.h"
#include "gpl_type.h"

class Constant : public Expression {
  public:
    Constant(Gpl_type enum_name) 
      : intrinsic_type(enum_name) {}
    virtual const Constant*   evaluate() const final;
    virtual int         as_int()    const {throw intrinsic_type;}
    virtual double      as_double() const {throw intrinsic_type;}
    virtual std::string as_string() const {throw intrinsic_type;}
    virtual Gpl_type    type()      const final;
    //p6
    virtual const Game_object* as_game_object() const {throw intrinsic_type;}
    virtual const Animation_code* as_animation_block() const {throw intrinsic_type;}

  private:
    Gpl_type intrinsic_type;
};

class Integer_constant : public Constant {
  public:
    Integer_constant(int d) 
      : Constant(INT), data(d) {}
    virtual int         as_int()    const { return data; }
    virtual double      as_double() const { return data; }
    virtual std::string as_string() const { return std::to_string(data);}
  private:
    int data;
};

class Double_constant : public Constant {
  public:
    Double_constant(double d) 
      : Constant(DOUBLE), data(d) {}
    virtual double      as_double() const { return data; }
    virtual std::string as_string() const { return std::to_string(data);}
  private:
    double data;
};

class String_constant : public Constant {
  public:
    String_constant(const std::string& d) 
      : Constant(STRING), data(d) {}
    virtual std::string as_string() const { return data;}
  private:
    std::string data;
};

class Game_attribute_constant : public Constant {
  public:
    Game_attribute_constant(const Game_object* gop, const std::string& attribute_name)
      : Constant(gop->attribute_type(attribute_name)),
        gop(gop),
        attribute_name(attribute_name) {}
    virtual const Animation_code* as_animation_block() const override;
    virtual int           as_int()         const;
    virtual double        as_double()      const;
    virtual std::string   as_string()      const;

  private:
    const Game_object* gop;
    std::string attribute_name;
};

class Game_object_constant : public Constant {
    public:
      Game_object_constant(Game_object* gop) : Constant(GAME_OBJECT), gop(gop) {}
      virtual const Game_object* as_game_object() const { return gop; }
    private:
      const Game_object* gop;
};

class Animation_block_constant : public Constant {
  public:
    Animation_block_constant(Animation_code* data) : Constant(ANIMATION_BLOCK), data(data) {}
    virtual const Animation_code* as_animation_block() const override { return data; }
  private:
    Animation_code* data;
};

#endif
