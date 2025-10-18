#include <gtest/gtest.h>
#include <minmax_stack.hpp>
using ds::MinMaxStack;

TEST(MinMaxStack, TracksMinMax) {
    MinMaxStack<int> s;
    s.push(3);
    EXPECT_EQ(s.min(), 3);
    EXPECT_EQ(s.max(), 3);
    s.push(1);
    EXPECT_EQ(s.min(), 1);
    EXPECT_EQ(s.max(), 3);
    s.push(2);
    EXPECT_EQ(s.min(), 1);
    EXPECT_EQ(s.max(), 3);
    s.push(1);
    EXPECT_EQ(s.min(), 1);
    EXPECT_EQ(s.max(), 3);
    s.push(5);
    EXPECT_EQ(s.min(), 1);
    EXPECT_EQ(s.max(), 5);

    s.pop();
    EXPECT_EQ(s.min(), 1);
    EXPECT_EQ(s.max(), 3);
    s.pop();
    EXPECT_EQ(s.min(), 1);
    EXPECT_EQ(s.max(), 3);
    s.pop();
    EXPECT_EQ(s.min(), 1);
    EXPECT_EQ(s.max(), 3);
    s.pop();
    EXPECT_EQ(s.min(), 3);
    EXPECT_EQ(s.max(), 3);
    s.pop();
    EXPECT_TRUE(s.empty());
    EXPECT_THROW(s.min(), std::out_of_range);
    EXPECT_THROW(s.max(), std::out_of_range);
    EXPECT_THROW(s.top(), std::out_of_range);
    EXPECT_THROW(s.pop(), std::out_of_range);
}
