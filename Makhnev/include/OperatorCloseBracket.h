#pragma once
#include <exception>
#include "Operator.h"

class OperatorCloseBracket : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) const override
    {
        throw std::exception("miss open braket 2");
    }
    virtual std::string GetYourself() const override
    {
        return "(";
    }
    static Operator* IsIt(std::string& current)
    {
        if (current[current.size() - 1] == ')') {
            current.erase(current.size() - 1);
            return new OperatorCloseBracket();
        }
        return nullptr;
    }
    virtual size_t GetPriority() const { return 0; }
};