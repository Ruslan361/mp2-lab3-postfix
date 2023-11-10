#include "postfix.h"
#include <gtest.h>
//
TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_get_postfix)
{
	TPostfix p("3+4*2+10");
	p.ToPostfix();
	std::cout << p.GetInfix() << std::endl;
	std::cout << p.GetPostfix() << std::endl;
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_calculate_postfix)
{
	TPostfix p;
	p.ToPostfix();
	double result = p.Calculate();
	ASSERT_NO_THROW(p.ToPostfix());
}

