#pragma once
#include "Operand.h"


template <typename T>
class KnownOperand : public Operand
{
public:
    T value;
    KnownOperand(const T& _value) : value(_value) {}
    KnownOperand(std::string& _value) {
        std::stringstream geek;
        geek << _value;
        geek >> value;
    }
    KnownOperand(const KnownOperand<T>& op) {
        value = op.value;
    }
    virtual Operand* Copy() const override {
        return new KnownOperand(value);
    }
    virtual void action(TStack<Lexem*>& operands) const override
    {
        operands.Push(new KnownOperand(*this));
    }
    virtual std::string GetYourself() const override
    {
        return std::to_string(value);
    }
    virtual Operand* Plus(const Lexem* operand) const override
    {
        const KnownOperand<T>* op = dynamic_cast<const KnownOperand<T>*>(operand);
        Operand* result;
        if (result = new KnownOperand(value + op->value))
            return result;
        throw "operator + is not defined";
    }
    Operand* Minus (const Lexem* operand) const override
    {
        const KnownOperand* op = dynamic_cast<const KnownOperand<T>*>(operand);
        Operand* result;
        if (result = new KnownOperand<T>(value - op->value))
            return result;
        throw "operator - is not defined";
    }
    Operand* UnaryMinus () const override
    {
        KnownOperand* result = nullptr;
        if (result = new KnownOperand<T>(-value))
            return result;
        throw "operator - is not defined";
    }
    Operand* Multiple (const Lexem* operand) const override
    {
        const KnownOperand<T>* op = dynamic_cast<const KnownOperand<T>*>(operand);
        Operand* result;
        if (result = new KnownOperand(value * op->value))
            return result;
        throw "operator * is not defined";
    }
    Operand* Division(const Lexem* operand) const override
    {
        const KnownOperand<T>* op = dynamic_cast<const KnownOperand<T>*>(operand);
        Operand* result;
        if (result = new KnownOperand(value / op->value))
            return result;
        throw "operator / is not defined";
    }
protected:
    virtual size_t GetPriority() const override
    {
        return 0;
    }
};
