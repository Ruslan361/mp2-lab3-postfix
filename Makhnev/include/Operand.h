#pragma once
#include <sstream>
#include <iostream>
#include "Lexem.h"
#include <map>

class Operand : public Lexem
{
public:
    virtual void action(TStack<Lexem*>& operands) const override = 0;
    virtual std::string GetYourself() const override = 0;
    virtual size_t GetPriority() const override = 0;
    virtual Operand* Copy() const = 0;
    virtual Operand* Plus(const Lexem* operand) const = 0;
    virtual Operand* Minus(const Lexem* operand) const = 0;
    virtual Operand* UnaryMinus() const = 0;
    virtual Operand* Multiple(const Lexem* operand) const = 0;
    virtual Operand* Division(const Lexem* operand) const = 0;
};
