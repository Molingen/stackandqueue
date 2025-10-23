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

TEST(MinMaxStack, StressTestMinMaxTracking) {
    MinMaxStack<int> s;
    const int n = 1'000'000;
    int exp_min = 0;
    int exp_max = 0;

    for (int i = 0; i < n; ++i) {
        s.push(i);
        exp_min = 0;
        exp_max = i;
        EXPECT_EQ(s.min(), exp_min);
        EXPECT_EQ(s.max(), exp_max);
    }

    for (int i = n - 1; i >= 0; --i) {
        EXPECT_EQ(s.min(), 0);
        EXPECT_EQ(s.max(), i);
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}

TEST(MinMaxStack, StressTestAlternatingMinMax) {
    MinMaxStack<int> s;
    const int n = 500'000;

    for (int i = 0; i < n; ++i) {
        s.push(i);
        s.push(-i);

        EXPECT_EQ(s.min(), -i);
        EXPECT_EQ(s.max(), i);

        s.pop();
        EXPECT_EQ(s.min(), i);
        EXPECT_EQ(s.max(), i);

        s.pop();
    }
    EXPECT_TRUE(s.empty());
}

TEST(MinMaxStack, StressTestLargeNumbers) {
    MinMaxStack<long long> s;
    const int n = 100'000;
    long long big_nubumber = 1'000'000'000LL;

    for (int i = 0; i < n; ++i) {
        s.push(big_nubumber + i);
        s.push(-big_nubumber - i);

        EXPECT_EQ(s.min(), -big_nubumber - i);
        EXPECT_EQ(s.max(), big_nubumber + i);

        s.pop();
        s.pop();
    }
    EXPECT_TRUE(s.empty());
}
