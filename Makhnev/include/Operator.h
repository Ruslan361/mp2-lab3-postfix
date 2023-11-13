#pragma once
#include "Lexem.h"
class Operator : public Lexem
{
public:
    static Lexem* IsIt(std::string& current);
    virtual size_t GetPriority() = 0;
};