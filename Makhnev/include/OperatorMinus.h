#pragma once
#include <exception>
#include "Operator.h"
#include "Operand.h"
#include "OperatorUnaryMinus.h"
class OperatorMinus : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        Lexem* lOperand = operands.Top();
        operands.Pop();
        if (Operand<double>* tmp = dynamic_cast<Operand<double>*>(lOperand)) {
            Operand<double>* result = *tmp - rOperand;
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        if (Operand<int>* tmp = dynamic_cast<Operand<int>*>(lOperand)) {
            Operand<int>* result = *tmp - rOperand;
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        throw std::exception("");
    }
    virtual std::string GetYourself() override
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
    virtual size_t GetPriority() { return 1; }
};