#pragma once
#include <exception>
#include "Operator.h"
#include "KnownOperand.h"
class OperatorPlus : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) const override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        Lexem* lOperand = operands.Top();
        operands.Pop();
        if (Operand* tmp = dynamic_cast<Operand*>(lOperand)) {
            Operand* result = tmp->Plus(rOperand);
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        delete lOperand;
        delete rOperand;
        throw std::exception("Operator + is not defined");
    }
    virtual std::string GetYourself() const override
    {
        return "+";
    }
    static Operator* IsIt(std::string& current)
    {
        if (current[current.size() - 1] == '+') {
            current.erase(current.size() - 1);
            return new OperatorPlus();
        }
        return nullptr;
    }
    virtual size_t GetPriority() const override { return 1; }
};