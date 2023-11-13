#pragma once
#include <exception>
#include "Operator.h"

class OperatorOpenBracket : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) override
    {
        throw std::exception("");
    }
    virtual std::string GetYourself() override
    {
        return "(";
    }
    static Operator* IsIt(std::string& current)
    {
        if (current[current.size() - 1] == '(') {
            current.erase(current.size() - 1);
            return new OperatorOpenBracket();
        }
        return nullptr;
    }
    virtual size_t GetPriority() { return 0; }
};