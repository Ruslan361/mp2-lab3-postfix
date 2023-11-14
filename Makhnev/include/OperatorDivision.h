#pragma once
#include <exception>
#include "Operator.h"
#include "KnownOperand.h"

class OperatorDivision : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) const override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        Lexem* lOperand = operands.Top();
        operands.Pop();
        //Operator* result = lOperand->Division(rOperand);
        if (KnownOperand<double>* tmp = dynamic_cast<KnownOperand<double>*>(lOperand)) {
            Operand* result = tmp->Division(rOperand);
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        else if (KnownOperand<int>* tmp = dynamic_cast<KnownOperand<int>*>(lOperand)) {
            Operand* result = tmp->Division(rOperand);
            operands.Push(result);
            delete tmp;
            delete rOperand;
            return;
        }
        throw std::exception("operator / is not defined");
    }
    virtual std::string GetYourself() const override
    {
        return "/";
    }
    static Operator* IsIt(std::string& current)
    {
        if (current[current.size() - 1] == '/') {
            current.erase(current.size() - 1);
            return new OperatorDivision();
        }
        return nullptr;
    }
    virtual size_t GetPriority() const { return 2; }
};
