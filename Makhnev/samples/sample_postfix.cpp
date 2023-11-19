#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;

  int res;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  cin >> expression;
  //for (size_t i = 0; i < expression.size(); i++)
  //{
	 // if (expression[i] == ' ') 
	 // {	
		//  expression.erase(i);
	 // }
  //}
  TPostfix<int> postfix(expression);

  cout << expression << endl;
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  postfix.ToPostfix();
  cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
  res = postfix.Calculate();
  cout << res << endl;

  return 0;
}
