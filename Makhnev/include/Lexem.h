#pragma once
#define DYNAMIC_ARRAY
#include "stack.h"

class Lexem {
public:
    virtual void action(TStack<Lexem*>& operands) = 0;
    virtual std::string GetYourself() = 0;
};