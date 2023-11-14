#pragma once
#define DYNAMIC_ARRAY
#include "stack.h"

class Lexem {
public:
    virtual void action(TStack<Lexem*>& operands) const = 0;
    virtual std::string GetYourself() const = 0;
    virtual size_t GetPriority() const = 0;
};