#pragma once
#include <exception>
#include "Operator.h"
#include "KnownOperand.h"
#include "OperatorUnaryMinus.h"
class OperatorMinus : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) const override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        Lexem* lOperand = operands.Top();
        operands.Pop();
        if (KnownOperand<double>* tmp = dynamic_cast<KnownOperand<double>*>(lOperand)) {
            Operand* result = tmp->Minus(rOperand);
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        if (KnownOperand<int>* tmp = dynamic_cast<KnownOperand<int>*>(lOperand)) {
            Operand* result = tmp->Minus(rOperand);
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        throw std::exception("operator - is not defined");
    }
    virtual std::string GetYourself() const override
    {
        return "-";
    }
    static Operator* IsIt(std::string& current)
    {

        if (current[current.size() - 1] == '-') {
            //if (current.size() == 1)
            //    return nullptr;
            current.erase(current.size() - 1);
            if (!current.empty())
                return new OperatorMinus();
            else
                return new OperatorUnaryMinus();
        }
        return nullptr;
    }
    virtual size_t GetPriority() const { return 1; }
};