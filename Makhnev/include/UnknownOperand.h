#pragma once
#include <sstream>
#include <iostream>
#include "KnownOperand.h"
#include <map>

class UnknownOperand : public Lexem
{
    std::string name;
public:
    static std::map<std::string, Operand*> known_values;
    UnknownOperand(const std::string& _name) : name(_name) {}
    virtual void action(TStack<Lexem*>& operands) const override
    {
        try {
            operands.Push(known_values.at(name)->Copy());
        }
        catch (std::out_of_range exception) {
            int value;
            std::cout << "enter " << name << std::endl;
            std::cin >> value;
            KnownOperand<int>* tmp = new KnownOperand<int>(value);
            known_values[name] = tmp;
            operands.Push(tmp);
        }
    }
    virtual std::string GetYourself() const override
    {
        return name;
    }
protected:
    virtual size_t GetPriority() const override
    {
        return 0;
    }
};
std::map<std::string, Operand*> UnknownOperand::known_values;