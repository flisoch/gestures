#include "gtest/gtest.h"
#include "ThreadsafeQueue.h"
#include <thread>
#include <iostream>

TEST(ThreadsafeQueueTest, EmptyQueueSizeIsZero) { 
    ThreadsafeQueue<int> q;
    ASSERT_EQ(q.size(), 0);
}

TEST(ThreadsafeQueueTest, IsEmptyReturnsTrueOnZeroSizedQueue) { 
    ThreadsafeQueue<int> q;
    ASSERT_EQ(q.empty(), true);
}

TEST(ThreadsafeQueueTest, SizeEqualsOneAfterPush) { 
    ThreadsafeQueue<int> q;

    q.push(1);

    ASSERT_EQ(q.size(), 1);
    ASSERT_EQ(q.empty(), false);
}

TEST(ThreadsafeQueueTest, SizeEqualsZeroAfterPushAndPop) { 
    ThreadsafeQueue<int> q;
    q.push(1);

    q.tryPop();

    ASSERT_EQ(q.size(), 0);
}

TEST(ThreadsafeQueueTest, OtherThreadWaitsAndPops) { 
    ThreadsafeQueue<int> q;
    std::thread t1([&]{
        std::shared_ptr<int> value = q.waitAndPop();
        ASSERT_EQ(*value, 1);
    });

    std::thread t2([&]{
        q.push(1);
    });
    t1.join();
    t2.join();
}
