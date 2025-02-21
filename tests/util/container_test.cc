#include <gtest/gtest.h>
#include <oat/unordered_bi_map.h>
#include <oat/indexed_vector.h>

TEST(UnorderedBiMapTest, InsertAndRetrieve) {
    oat::unordered_bi_map<int, std::string> bi_map;
    bi_map.insert(1, "one");
    bi_map.insert(2, "two");

    EXPECT_EQ(bi_map.left_at(1), "one");
    EXPECT_EQ(bi_map.left_at(2), "two");
    EXPECT_EQ(bi_map.right_at("one"), 1);
    EXPECT_EQ(bi_map.right_at("two"), 2);
}

TEST(UnorderedBiMapTest, Remove) {
    oat::unordered_bi_map<int, std::string> bi_map;
    bi_map.insert(1, "one");
    bi_map.insert(2, "two");

    bi_map.erase_left(1);
    EXPECT_THROW(bi_map.left_at(1), std::out_of_range);
    EXPECT_THROW(bi_map.right_at("one"), std::out_of_range);

    bi_map.erase_right("two");
    EXPECT_THROW(bi_map.left_at(2), std::out_of_range);
    EXPECT_THROW(bi_map.right_at("two"), std::out_of_range);
}

TEST(IndexedVectorTest, InsertAndRetrieve) {
    oat::indexed_vector<int> idx_vector;
    idx_vector.push_back(10);
    idx_vector.push_back(20);
    idx_vector.push_back(30);

    EXPECT_EQ(idx_vector[0], 10);
    EXPECT_EQ(idx_vector[1], 20);
    EXPECT_EQ(idx_vector[2], 30);
}

TEST(IndexedVectorTest, Remove) {
    oat::indexed_vector<int> idx_vector;
    idx_vector.push_back(10);
    idx_vector.push_back(20);
    idx_vector.push_back(30);

    idx_vector.erase(idx_vector.begin() + 1);
    EXPECT_EQ(idx_vector.size(), 2);
    EXPECT_EQ(idx_vector[0], 10);
    EXPECT_EQ(idx_vector[1], 30);
}

TEST(IndexedVectorTest, Indexing) {
    oat::indexed_vector<int> idx_vector;
    idx_vector.push_back(10);
    idx_vector.push_back(20);
    idx_vector.push_back(30);

    EXPECT_EQ(idx_vector.index_of(10), 0);
    EXPECT_EQ(idx_vector.index_of(20), 1);
    EXPECT_EQ(idx_vector.index_of(30), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}