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

using namespace std;


template <typename T>
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
      bool isCloseBracketLast = false;
      for (char symbol : infix)
      {
          current += symbol;
          Operator* tmp;
          if (tmp = OperatorPlus::IsIt(current)) {
              if (!current.empty()) 
              {
                  postfix.push_back(new Operand<T>(current));
                  current.clear();
              }
              InsertOperator(operators, tmp);
          }
          else if (tmp = OperatorMultiple::IsIt(current)) {
              if (!current.empty())
              {
                  postfix.push_back(new Operand<T>(current));
                  current.clear();
              }
              InsertOperator(operators, tmp);
          }
          else if (tmp = OperatorOpenBracket::IsIt(current))
          {
              if (!current.empty()) throw exception("missing operator before open bracket");
              //InsertOperator(operators, tmp);
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
              if (!current.empty())
              {
                  postfix.push_back(new Operand<T>(current));
                  current.clear();
              }
              if (isCloseBracketLast) {
                  delete tmp;
                  tmp = new OperatorMinus();
              }
              InsertOperator(operators, tmp);
          }
          else if (tmp = OperatorDivision::IsIt(current))
          {
              if (!current.empty())
              {
                  postfix.push_back(new Operand<T>(current));
                  current.clear();
              }
              InsertOperator(operators, tmp);
          }
          isCloseBracketLast = false;
          //cout << GetPostfix() << std::endl;
      }
      if (!current.empty()) 
          postfix.push_back(new Operand<int>(current));
      while (!operators.IsEmpty()) {
          if (OperatorOpenBracket* bracket = dynamic_cast<OperatorOpenBracket*>(operators.Top()))
              throw exception("miss close bracket");
          postfix.push_back(operators.Top());
          operators.Pop();
      }
      return postfix;
  }
  void InsertCloseBracket(std::string& current, TStack<Operator*>& operators)
  {
      if (!current.empty())
      {
          postfix.push_back(new Operand<T>(current));
          current.clear();
      }
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
  void InsertOperator(TStack<Operator*>& operators, Operator*& tmp)
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
  // Ввод переменных, вычисление по постфиксной форме
  T Calculate() {
      TStack<Lexem*> stack;
      for (Lexem* lexem : postfix) {
          lexem->action(stack);
      }
      Operand<T>* result = dynamic_cast<Operand<T>*>(stack.Top());
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
  }
};

#endif
