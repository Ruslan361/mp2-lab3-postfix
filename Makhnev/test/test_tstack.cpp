#define DYNAMIC_ARRAY
#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, cant_pop_empty_stack)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Pop());
}
TEST(TStack, cant_top_empty_stack)
{
	TStack<int> st;
	ASSERT_ANY_THROW(st.Top());
}
TEST(TStack, can_push_element)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.Push(-1));
}
TEST(TStack, can_push_many_elements)
{
	TStack<int> st;
	ASSERT_NO_THROW(st.Push(-1));
	ASSERT_NO_THROW(st.Push(-1));
	ASSERT_NO_THROW(st.Push(-1));
	ASSERT_NO_THROW(st.Push(-1));
	ASSERT_NO_THROW(st.Push(-1));
	ASSERT_NO_THROW(st.Push(-1));
	ASSERT_NO_THROW(st.Push(-1));
	ASSERT_NO_THROW(st.Push(-1));
}
TEST(TStack, is_pushed_elements_correct)
{
	TStack<int> st;
	st.Push(10);
	EXPECT_EQ(10, st.Top());
	st.Push(20);
	EXPECT_EQ(20, st.Top());
	st.Push(40);
	EXPECT_EQ(40, st.Top());
}
TEST(TStack, can_stack_copy)
{
	TStack<int> st;
	st.Push(10);
	st.Push(20);
	st.Push(40);
	ASSERT_NO_THROW(TStack<int> st2(st));
}
TEST(TStack, is_stack_copy_correct)
{
	TStack<int> st;
	st.Push(10);
	st.Push(20);
	st.Push(40);
	TStack<int> st2(st);
	EXPECT_EQ(st, st2);
}