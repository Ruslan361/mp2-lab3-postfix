#pragma once
#include <exception>
#include "KnownOperand.h"

class OperatorOpenBracket : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) const override
    {
        throw std::exception("miss close bracket 2");
    }
    virtual std::string GetYourself() const override
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
    virtual size_t GetPriority() const override { return 0; }
};