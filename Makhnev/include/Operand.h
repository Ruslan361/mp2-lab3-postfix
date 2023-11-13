#pragma once
#include <sstream>
#include "Lexem.h"
#include <map>
class Operand : public Lexem
{
public:
    virtual void action(TStack<Lexem*>& operands) override = 0;
    virtual std::string GetYourself() override = 0;
    virtual Operand* operator+(Lexem* operand) = 0;
    virtual Operand* operator-(Lexem* operand) = 0;
    virtual Operand* operator-() = 0;
    virtual Operand* operator*(const Lexem* operand) = 0;
    virtual Operand* operator/(const Lexem* operand) = 0;
};

template <typename T>
class KnownOperand : public Operand
{
public:
    T value;
    KnownOperand(T _value) : value(_value) {}
    KnownOperand(std::string& _value) {
        std::stringstream geek;
        geek << _value;
        geek >> value;
    }
    KnownOperand(KnownOperand& op) {
        value = op.value;
    }
    virtual void action(TStack<Lexem*>& operands) override
    {
        operands.Push(new KnownOperand(*this));
    }
    virtual std::string GetYourself() override
    {
        return std::to_string(value);
    }
    Operand* operator+(Lexem* operand)
    {
        Operand* op = dynamic_cast<Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value + op->value))
            return result;
        throw "operator + is not defined";
    }
    Operand* operator-(Lexem* operand)
    {
        Operand* op = dynamic_cast<Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value - op->value))
            return result;
        throw "operator - is not defined";
    }
    Operand* operator-()
    {
        Operand* result = nullptr;
        if (result = new Operand(-value))
            return result;
        throw "operator - is not defined";
    }
    Operand* operator*(const Lexem* operand)
    {
        const Operand* op = dynamic_cast<const Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value * op->value))
            return result;
        throw "operator * is not defined";
    }
    Operand* operator/(const Lexem* operand)
    {
        const Operand* op = dynamic_cast<const Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value / op->value))
            return result;
        throw "operator / is not defined";
    }
};

class UnknownOperand : public Operand
{
    static map<std::string, Operator*>
public:
    std::string name;
    UnknownOperand(std::string _name) : name(_name) {}
    virtual void action(TStack<Lexem*>& operands) override
    {
        operands.Push(new Operand(*this));
    }
    virtual std::string GetYourself() override
    {
        return std::to_string(value);
    }
    Operand* operator+(Lexem* operand)
    {
        Operand* op = dynamic_cast<Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value + op->value))
            return result;
        throw "operator + is not defined";
    }
    Operand* operator-(Lexem* operand)
    {
        Operand* op = dynamic_cast<Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value - op->value))
            return result;
        throw "operator - is not defined";
    }
    Operand* operator-()
    {
        Operand* result = nullptr;
        if (result = new Operand(-value))
            return result;
        throw "operator - is not defined";
    }
    Operand* operator*(const Lexem* operand)
    {
        const Operand* op = dynamic_cast<const Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value * op->value))
            return result;
        throw "operator * is not defined";
    }
    Operand* operator/(const Lexem* operand)
    {
        const Operand* op = dynamic_cast<const Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value / op->value))
            return result;
        throw "operator / is not defined";
    }
};