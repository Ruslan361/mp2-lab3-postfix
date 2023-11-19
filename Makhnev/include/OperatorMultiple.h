#pragma once
#include <exception>
#include "KnownOperand.h"
#include "Operator.h"

class OperatorMultiple : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) const override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        Lexem* lOperand = operands.Top();
        operands.Pop();
        if (Operand* tmp = dynamic_cast<Operand*>(lOperand)) {
            Operand* result = tmp->Multiple(rOperand);
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        delete lOperand;
        delete rOperand;
        throw std::exception("operator * is not defined");
    }
    virtual std::string GetYourself() const override
    {
        return "*";
    }
    static Operator* IsIt(std::string& current)
    {
        if (current[current.size() - 1] == '*') {
            current.erase(current.size() - 1);
            return new OperatorMultiple();
        }
        return nullptr;
    }
    virtual size_t GetPriority() const { return 2; }
};