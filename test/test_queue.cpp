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

TEST(Queue, StressTestFifoLarge) {
    Queue<int> q;
    const int n = 1000000;

    for (int i = 0; i < n; ++i) {
        q.push(i);
    }
    EXPECT_EQ(q.size(), n);

    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(q.front(), i);
        q.pop();
    }
    EXPECT_TRUE(q.empty());
}

TEST(Queue, StressTestWrapAround) {
    Queue<int> q;
    const int m = 1000;
    const int n = 1000;

    for (int cycle = 0; cycle < m; ++cycle) {
        for (int i = 0; i < n; ++i) {
            q.push(cycle * n + i);
        }

        for (int i = 0; i < n; ++i) {
            EXPECT_EQ(q.front(), cycle * n + i);
            q.pop();
        }
        EXPECT_TRUE(q.empty());
    }
}

TEST(Queue, StressTestMixedOperations) {
    Queue<int> q;
    const int n = 2'000'000;
    int next_banan = 0;
    int next_morkov = 0;

    for (int i = 0; i < n; ++i) {
        if (q.empty() || (i % 3 != 0)) {
            q.push(next_banan++);
        } else {
            EXPECT_EQ(q.front(), next_morkov++);
            q.pop();
        }
    }

    while (!q.empty()) {
        EXPECT_EQ(q.front(), next_morkov++);
        q.pop();
    }
}

TEST(Queue, StressTestStrings) {
    Queue<std::string> q;
    const int n = 100000;

    for (int i = 0; i < n; ++i) {
        q.push("prikolchik_nomer_" + std::to_string(i));
    }

    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(q.front(), "prikolchik_nomer_" + std::to_string(i));
        q.pop();
    }
    EXPECT_TRUE(q.empty());
}

TEST(Queue, StressTestBackOperation) {
    Queue<int> q;
    const int n = 100'000;

    for (int i = 0; i < n; ++i) {
        q.push(i);
        EXPECT_EQ(q.back(), i);
    }

    for (int i = 0; i < n; ++i) {
        if (i < n - 1) {
            EXPECT_EQ(q.back(), n - 1);
        }
        EXPECT_EQ(q.front(), i);
        q.pop();
    }
}

TEST(Queue, StressTestCapacityGrowth) {
    Queue<int> q;
    const int n = 1'000'000;

    for (int i = 0; i < n; ++i) {
        q.push(i);
        if (i % 100000 == 0) {
            EXPECT_EQ(q.front(), 0);
            EXPECT_EQ(q.back(), i);
        }
    }

    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(q.front(), i);
        q.pop();
    }
}