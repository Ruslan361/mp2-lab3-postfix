#pragma once
#include "OperatorMinus.h"

class OperatorUnaryMinus : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) const override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        //Lexem* lOperand = operands.Top();
        //operands.Pop();
        if (KnownOperand<double>* tmp = dynamic_cast<KnownOperand<double>*>(rOperand)) {
            Operand* result = tmp->UnaryMinus();
            operands.Push(result);
            delete tmp;
            return;
        }
        if (KnownOperand<int>* tmp = dynamic_cast<KnownOperand<int>*>(rOperand)) {
            Operand* result = tmp->UnaryMinus();
            operands.Push(result);
            delete tmp;
            return;
        }
        throw std::exception("unary minus is not defined");
    }
    virtual std::string GetYourself() const override
    {
        return "-u";
    }
    static Operator* IsIt(std::string& current)
    {
        //if (current[current.size() - 1] == '-') {
        //    current.erase(current.size() - 1);
        //    if (!current.empty())
        //        return new OperatorMinus();
        //    else
        //        return new OperatorUnaryMinus();
        //}
        return nullptr;
    }
    virtual size_t GetPriority() const { return 100; }
};