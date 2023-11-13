#pragma once
#include "OperatorMinus.h"

class OperatorUnaryMinus : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        //Lexem* lOperand = operands.Top();
        //operands.Pop();
        if (Operand<double>* tmp = dynamic_cast<Operand<double>*>(rOperand)) {
            Operand<double>* result = (-*tmp);
            operands.Push(result);
            delete tmp;
            return;
        }
        if (Operand<int>* tmp = dynamic_cast<Operand<int>*>(rOperand)) {
            Operand<int>* result = (-*tmp);
            operands.Push(result);
            delete tmp;
            return;
        }
        throw std::exception("unary minus is not defined");
    }
    virtual std::string GetYourself() override
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
    virtual size_t GetPriority() { return 100; }
};