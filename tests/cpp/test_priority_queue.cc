#include <gtest/gtest.h>
#include <queue>
#include <vector>

class PriorityQueueTest : public ::testing::Test {
protected:
    std::priority_queue<int> pq;
};

TEST_F(PriorityQueueTest, IsEmptyInitially) {
    EXPECT_TRUE(pq.empty());
}

TEST_F(PriorityQueueTest, PushIncreasesSize) {
    pq.push(1);
    EXPECT_EQ(pq.size(), 1);
    pq.push(2);
    EXPECT_EQ(pq.size(), 2);
}

TEST_F(PriorityQueueTest, PopDecreasesSize) {
    pq.push(1);
    pq.push(2);
    pq.pop();
    EXPECT_EQ(pq.size(), 1);
    pq.pop();
    EXPECT_EQ(pq.size(), 0);
}

TEST_F(PriorityQueueTest, TopReturnsMaxElement) {
    pq.push(1);
    pq.push(3);
    pq.push(2);
    EXPECT_EQ(pq.top(), 3);
    pq.pop();
    EXPECT_EQ(pq.top(), 2);
}

TEST_F(PriorityQueueTest, HandlesDuplicateElements) {
    pq.push(1);
    pq.push(1);
    pq.push(1);
    EXPECT_EQ(pq.size(), 3);
    EXPECT_EQ(pq.top(), 1);
    pq.pop();
    EXPECT_EQ(pq.top(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}