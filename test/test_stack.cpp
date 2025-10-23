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

TEST(Stack, StressTestPushPop) {
    Stack<int> s;
    const int n = 1000000;

    for (int i = 0; i < n; ++i) {
        s.push(i);
    }
    EXPECT_EQ(s.size(), n);
    EXPECT_EQ(s.top(), n - 1);

    for (int i = n - 1; i >= 0; --i) {
        EXPECT_EQ(s.top(), i);
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}

TEST(Stack, StressTestAlternatingPushPop) {
    Stack<int> s;
    const int n = 500000;

    for (int i = 0; i < n; ++i) {
        s.push(i);
        s.push(i + 1);
        EXPECT_EQ(s.top(), i + 1);
        s.pop();
        EXPECT_EQ(s.top(), i);
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}

TEST(Stack, StressTestStrings) {
    Stack<std::string> s;
    const int n = 100000;

    for (int i = 0; i < n; ++i) {
        s.push("prikolchik_nomer_" + std::to_string(i));
    }

    for (int i = n - 1; i >= 0; --i) {
        EXPECT_EQ(s.top(), "prikolchik_nomer_" + std::to_string(i));
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}