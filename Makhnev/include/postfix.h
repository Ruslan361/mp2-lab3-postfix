#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include <vector>
#include <sstream>
#include <string>
#define DYNAMIC_ARRAY
#include "stack.h"

using namespace std;

class Lexem {
public:
    virtual void action(TStack<Lexem*>& operands) = 0;
    virtual string GetYourself() = 0;
};
template <typename T>
class Operand : public Lexem
{
public:
    T value;
    Operand(T _value) : value(_value) {}
    Operand(std::string& _value) {
        stringstream geek;
        geek << _value;
        geek >> value;
    }
    virtual void action(TStack<Lexem*>& operands) override
    {
        operands.Push(this);
    }
    virtual string GetYourself() override 
    {
        return to_string(value);
    }
    Operand* operator+( Lexem* operand) 
    {
        Operand* op = dynamic_cast<Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value + op->value))
            return result;
        throw "operator + is not defined";
    }
    Operand* operator*(const Lexem* operand)
    {
        const Operand* op = dynamic_cast<const Operand<T>*>(operand);
        Operand* result;
        if (result = new Operand(value * op->value))
            return result;
        throw "operator * is not defined";
    }
};

//class Operand : public Lexem
//{
//public:
//    double value;
//    Operand(double _value) : value(_value) {}
    //Operand(string& _value) {
    //    stringstream geek;
    //    geek << _value;
    //    geek >> value;
    //}
    //virtual void action(TStack<Lexem*>& operands) override
    //{
    //    operands.Push(this);
    //}
    //virtual string GetYourself() override 
    //{
    //    return to_string(value);
    //}
    //Operand* operator+(const Lexem* operand) 
    //{
    //    Operand* op = dynamic_cast<Operand<T>*>(operand);
    //    Operand* result;
    //    if (result = new Operand(value + op->value))
    //        return result;
    //    throw "operator + is not defined";
    //}
//};
class Operator : public Lexem
{
public:
    static Lexem* IsIt(std::string& current);
    virtual size_t GetPriority() = 0;
};
class OperatorPlus : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        Lexem* lOperand = operands.Top();
        operands.Pop();
        if (Operand<double>* tmp = dynamic_cast<Operand<double>*>(lOperand)) {
            Operand<double>* result = *tmp + rOperand;
            operands.Push(result);
            delete tmp;
            delete rOperand;
        }
        throw exception("");
    }
    virtual string GetYourself() override
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
    virtual size_t GetPriority() { return 1; }
};

class OperatorMultiple : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) override
    {
        Lexem* rOperand = operands.Top();
        operands.Pop();
        Lexem* lOperand = operands.Top();
        operands.Pop();
        if (Operand<double>* tmp = dynamic_cast<Operand<double>*>(lOperand)) {
            Operand<double>* result = *tmp * rOperand;
            operands.Push(result);
            delete tmp;
            delete rOperand;
        }
        if (Operand<int>* tmp = dynamic_cast<Operand<int>*>(lOperand)) {
            Operand<int>* result = *tmp * rOperand;
            operands.Push(result);
            delete tmp;
            delete rOperand;
        }
        throw exception("");
    }
    virtual string GetYourself() override
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
    virtual size_t GetPriority() { return 2; }
};
class OperatorOpenBracket : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) override
    {
        throw exception("");
    }
    virtual string GetYourself() override
    {
        return "(";
    }
    static Operator* IsIt(std::string& current)
    {
        if (current[current.size() - 1] == '(') {
            current.erase(current.size() - 1);
            return new OperatorOpenBracket();
        }
        return nullptr;
    }
    virtual size_t GetPriority() { return 100; }
};
class OperatorCloseBracket : public Operator {
public:
    virtual void action(TStack<Lexem*>& operands) override
    {
        throw exception("");
    }
    virtual string GetYourself() override
    {
        return "(";
    }
    static Operator* IsIt(std::string& current)
    {
        if (current[current.size() - 1] == ')') {
            current.erase(current.size() - 1);
            return new OperatorOpenBracket();
        }
        return nullptr;
    }
    virtual size_t GetPriority() { return 100; }
};
class TPostfix
{
  string infix;
  vector<Lexem*> postfix;
public:
  TPostfix()
  {
    infix = "3+2*4";
  }
  TPostfix(std::string _infix)
  {
      infix = _infix;
  }
  string GetInfix() { return infix; }
  string GetPostfix() { 
      string result = "";
      for (Lexem* lexem : postfix) {
          result += lexem->GetYourself();
      }
      return result;
  }
  vector<Lexem*> ToPostfix() {
      string current = "";
      TStack<Operator*> operators;
      for (char symbol : infix)
      {
          current += symbol;
          Operator* tmp;
          if (tmp = OperatorPlus::IsIt(current)) {
              postfix.push_back(new Operand<int>(current));
              current.clear();
              InsertOperator(operators, tmp);
          }
          else if (tmp = OperatorMultiple::IsIt(current)) {
              postfix.push_back(new Operand<int>(current));
              current.clear();
              InsertOperator(operators, tmp);
          }
          else if (tmp = OperatorOpenBracket::IsIt(current))
          {
              if (!current.empty()) throw exception("missing operator before open bracket");
              InsertOperator(operators, tmp);
          }
          else if (tmp = OperatorCloseBracket::IsIt(current))
          {
              //if (!current.empty()) throw exception("missing operator before open bracket");
              InsertOperator(operators, tmp);
          }
      }
      if (!current.empty()) 
          postfix.push_back(new Operand<int>(current));
      while (!operators.IsEmpty()) {
          postfix.push_back(operators.Top());
          operators.Pop();
      }
      return postfix;
  }
  void InsertOperator(TStack<Operator*>& operators, Operator*& tmp)
  {
      if (operators.IsEmpty() || operators.Top()->GetPriority() < tmp->GetPriority())
          operators.Push(tmp);
      else
      {
          do {
              postfix.push_back(operators.Top());
              operators.Pop();
          } while (!operators.IsEmpty() && operators.Top()->GetPriority() <= tmp->GetPriority());
          operators.Push(tmp);
      }
  }
  // Ввод переменных, вычисление по постфиксной форме
  double Calculate() {
      TStack<Lexem*> stack;
      for (Lexem* lexem : postfix) {
          lexem->action(stack);
      }
      Operand<double>* result = dynamic_cast<Operand<double>*>(stack.Top());
      return result->value;
  }
};

#endif
