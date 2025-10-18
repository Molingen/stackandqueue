#include <gtest/gtest.h>
#include <stack.hpp>
#include <string>
using ds::Stack;

TEST(Stack, PushPopInt) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
    for (int i = 1; i <= 5; ++i) s.push(i);
    EXPECT_EQ(s.size(), 5u);
    EXPECT_EQ(s.top(), 5);
    s.pop();
    EXPECT_EQ(s.top(), 4);
    s.pop(); s.pop(); s.pop(); s.pop();
    EXPECT_TRUE(s.empty());
    EXPECT_THROW(s.pop(), std::out_of_range);
    EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(Stack, PushStrings) {
    Stack<std::string> s;
    s.push("a");
    s.push(std::string("bc"));
    EXPECT_EQ(s.size(), 2u);
    EXPECT_EQ(s.top(), "bc");
    s.pop();
    EXPECT_EQ(s.top(), "a");
}
