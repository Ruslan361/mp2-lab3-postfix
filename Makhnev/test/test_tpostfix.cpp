#include "postfix.h"
#include <gtest.h>
//
TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix<int> p);
}
TEST(TPostfix, can_get_postfix)
{
	TPostfix<int> p("(3*(1*1+5))");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix2)
{
	TPostfix<int> p("((1+1))");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix3)
{
	TPostfix<int> p("(())");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_get_postfix_no_close_bracket)
{
	TPostfix<int> p("(()");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, cant_get_postfix_no_open_bracket)
{
	TPostfix<int> p("())");
	ASSERT_ANY_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix4)
{
	TPostfix<int> p("-(-1+1)");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix5)
{
	TPostfix<int> p("1/(1+1)");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix6)
{
	TPostfix<int> p("1/2*3");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix7)
{
	TPostfix<int> p("-(-1/2)");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_get_postfix8)
{
	TPostfix<int> p("-(-(-1/2))");
	p.ToPostfix();
	ASSERT_NO_THROW(p.ToPostfix());
}
TEST(TPostfix, can_calculate_postfix)
{
	TPostfix<int> p("1+1");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_unary_minus)
{
	TPostfix<int> p("-1+1");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_unary_minus2)
{
	TPostfix<int> p("-(1+1)");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_division)
{
	TPostfix<int> p("-(2/1)");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_multiple)
{
	TPostfix<int> p("-(2*3)");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_minus)
{
	TPostfix<int> p("-(2-3)");
	p.ToPostfix();
	ASSERT_NO_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_postfix_large)
{
	TPostfix<int> p("8/(1+1)+5+(2*3/(8)-5)");
	p.ToPostfix();
	p.Calculate();
	ASSERT_NO_THROW(p.Calculate());
}

TEST(TPostfix, is_calculation_postfix_correct)
{
	TPostfix<int> p("1+1");
	p.ToPostfix();
	EXPECT_EQ(p.Calculate(), 1+1);
}
TEST(TPostfix, is_calculation_postfix_unary_minus_correct)
{
	TPostfix<int> p("-1+1");
	p.ToPostfix();
	EXPECT_EQ(p.Calculate(), -1+1);
}
TEST(TPostfix, is_calculation_postfix_unary_minus2_correct)
{
	TPostfix<int> p("-(1+1)");
	p.ToPostfix();
	EXPECT_EQ(p.Calculate(), -(1+1));
}
TEST(TPostfix, is_calculation_postfix_division_correct)
{
	TPostfix<int> p("-(2/1)");
	p.ToPostfix();
	EXPECT_EQ(p.Calculate(), -(2/1));
}
TEST(TPostfix, is_calculation_postfix_multiple_correct)
{
	TPostfix<int> p("-(2*3)");
	p.ToPostfix();
	EXPECT_EQ(p.Calculate(), -(2*3));
}
TEST(TPostfix, is_calculation_postfix_minus_correct)
{
	TPostfix<int> p("-(2-3)");
	p.ToPostfix();
	EXPECT_EQ(p.Calculate(), -(2-3));
}
TEST(TPostfix, is_calculation_postfix_large_correct)
{
	TPostfix<int> p("8/(1+1)+5+(2*3/(8)-5)");
	p.ToPostfix();
	p.Calculate();
	EXPECT_EQ(p.Calculate(), 8 / (1 + 1) + 5 + (2 * 3 / (8) - 5));
}
