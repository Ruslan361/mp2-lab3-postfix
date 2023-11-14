#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
//#define DYNAMIC_ARRAY
//#include "stack.h"
#include "Lexem.h"
#include "Operand.h"
#include "OperatorDivision.h"
#include "OperatorMinus.h"
#include "OperatorMultiple.h"
#include "OperatorPlus.h"
#include "OperatorCloseBracket.h"
#include "OperatorOpenBracket.h"
#include "UnknownOperand.h"

using namespace std;


template <typename T>
class TPostfix
{
  string infix;
  vector<Lexem*> postfix;
  void AddOperand(std::string& current);
  void CheckOpenBracket(TStack<Lexem*>& operators);
  void InsertCloseBracket(std::string& current, TStack<Lexem*>& operators);
  void InsertOperator(TStack<Lexem*>& operators, Operator*& tmp);
public:
  TPostfix()
  {
    infix = "3+2*4";
  }
  TPostfix(std::string _infix)
  {
      infix = _infix;
  }
  ~TPostfix() {
      for (auto lexem : postfix) {
          delete lexem;
      }
  }
  string GetInfix() { return infix; }
  string GetPostfix() { 
      string result = "";
      for (Lexem* lexem : postfix) {
          result += lexem->GetYourself();
      }
      return result;
  }
  void ToPostfix();
  // Ввод переменных, вычисление по постфиксной форме
  T Calculate();
};

#endif

template<typename T>
inline void TPostfix<T>::AddOperand(std::string& current)
{
    if (!current.empty())
    {
        if (isdigit(current[0]))
            postfix.push_back(new KnownOperand<T>(current));
        else
            postfix.push_back(new UnknownOperand(current));
        current.clear();
    }
}

template<typename T>
inline void TPostfix<T>::CheckOpenBracket(TStack<Lexem*>& operators)
{
    while (!operators.IsEmpty()) {
        if (OperatorOpenBracket* bracket = dynamic_cast<OperatorOpenBracket*>(operators.Top()))
            throw exception("miss close bracket");
        postfix.push_back(operators.Top());
        operators.Pop();
    }
}

template<typename T>
inline void TPostfix<T>::InsertCloseBracket(std::string& current, TStack<Lexem*>& operators)
{
    AddOperand(current);
    OperatorOpenBracket* close = nullptr;
    while ((!operators.IsEmpty()) && ((close = dynamic_cast<OperatorOpenBracket*>(operators.Top())) == nullptr))
    {
        postfix.push_back(operators.Top());
        operators.Pop();
    }
    if (close)
    {
        delete close;
        operators.Pop();
    }
    else
    {
        throw exception("miss open bracket");
    }
}

template<typename T>
inline void TPostfix<T>::InsertOperator(TStack<Lexem*>& operators, Operator*& tmp)
{
    if (operators.IsEmpty() || operators.Top()->GetPriority() < tmp->GetPriority())
        operators.Push(tmp);
    else
    {
        do {
            postfix.push_back(operators.Top());
            operators.Pop();
        } while (!operators.IsEmpty() && operators.Top()->GetPriority() >= tmp->GetPriority());
        operators.Push(tmp);
    }
}

template<typename T>
inline void TPostfix<T>::ToPostfix() {
    string current = "";
    TStack<Lexem*> operators;
    bool isCloseBracketLast = false;
    for (char symbol : infix)
    {
        current += symbol;
        Operator* tmp;
        if (tmp = OperatorPlus::IsIt(current)) {
            AddOperand(current);
            InsertOperator(operators, tmp);
        }
        else if (tmp = OperatorMultiple::IsIt(current)) {
            AddOperand(current);
            InsertOperator(operators, tmp);
        }
        else if (tmp = OperatorOpenBracket::IsIt(current))
        {
            if (!current.empty()) throw exception("missing operator before open bracket");
            operators.Push(tmp);
        }
        else if (tmp = OperatorCloseBracket::IsIt(current))
        {
            InsertCloseBracket(current, operators);
            isCloseBracketLast = true;
            continue;
        }
        else if (tmp = OperatorMinus::IsIt(current))
        {
            AddOperand(current);
            if (isCloseBracketLast) {
                delete tmp;
                tmp = new OperatorMinus();
            }
            InsertOperator(operators, tmp);
        }
        else if (tmp = OperatorDivision::IsIt(current))
        {
            AddOperand(current);
            InsertOperator(operators, tmp);
        }
        isCloseBracketLast = false;
        //cout << GetPostfix() << std::endl;
    }
    AddOperand(current);
    CheckOpenBracket(operators);
}

// Ввод переменных, вычисление по постфиксной форме
template<typename T>
inline T TPostfix<T>::Calculate() {
    TStack<Lexem*> stack;
    for (Lexem* lexem : postfix) {
        lexem->action(stack);
    }
    KnownOperand<T>* result = dynamic_cast<KnownOperand<T>*>(stack.Top());
    T res = result->value;
    delete result;
    stack.Pop();
    if (stack.IsEmpty())
        return res;
    else
    {
        while (!stack.IsEmpty())
        {
            std::cout << stack.Top()->GetYourself() << '\n';
            delete stack.Top();
            stack.Pop();
        }
        throw exception("something went wrong");
    }
    for (auto op : UnknownOperand::known_values) {
        delete op.second;
    }
    UnknownOperand::known_values.clear();
}
