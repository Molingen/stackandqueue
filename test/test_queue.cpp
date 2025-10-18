#include <gtest/gtest.h>
#include <queue.hpp>
using ds::Queue;

TEST(Queue, BasicFifo) {
    Queue<int> q;
    for (int i = 1; i <= 5; ++i) q.push(i);
    EXPECT_EQ(q.size(), 5u);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 5);
    q.pop();
    EXPECT_EQ(q.front(), 2);
    EXPECT_EQ(q.size(), 4u);
}

TEST(Queue, WrapAndGrowKeepsOrder) {
    Queue<int> q;
    for (int i = 0; i < 5; ++i) q.push(i);
    for (int i = 0; i < 3; ++i) q.pop();
    for (int i = 5; i < 20; ++i) q.push(i);
    int expected = 3;
    while (!q.empty()) {
        ASSERT_EQ(q.front(), expected) << "mismatch at expected=" << expected;
        q.pop();
        ++expected;
    }
    EXPECT_EQ(expected, 20);
    EXPECT_THROW(q.pop(), std::out_of_range);
    EXPECT_THROW(q.front(), std::out_of_range);
    EXPECT_THROW(q.back(), std::out_of_range);
}
