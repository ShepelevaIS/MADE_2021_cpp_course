#include "set.h"
#include <gtest/gtest.h>
#include <vector>

TEST(SetTest, ConstructEmpty) {
  Set<int64_t> set;
  std::vector<int64_t> actual(set.begin(), set.end());
  EXPECT_TRUE(actual.empty());
}

TEST(SetTest, ConstructIterator) {
  std::vector<int64_t> elements{3, 5, 4, 1, 2};
  Set<int64_t> set(elements.begin(), elements.end());
  std::vector<int64_t> actual(set.begin(), set.end());
  std::vector<int64_t> expected{1, 2, 3, 4, 5};
  EXPECT_EQ(expected, actual);
}

TEST(SetTest, ConstructInitializerList) {
  Set<int64_t> set({3, 5, 4, 1, 2});
  std::vector<int64_t> elements{3, 5, 4, 1, 2};
  Set<int64_t> expected_set(elements.begin(), elements.end());
  EXPECT_EQ(expected_set, set);  
}

TEST(SetTest, CheckCopy) {
  Set<int64_t> set({3, 2});
  auto set_other(set);
  EXPECT_EQ(set, set_other);
}

TEST(SetTest, CheckAssign) {
  Set<int64_t> set({3, 2});
  Set<int64_t> set_other;
  set_other = set;
  EXPECT_EQ(set, set_other);
}

TEST(SetTest, IsEmpty) {
  Set<int64_t> set;
  bool is_empty = set.empty();
  EXPECT_TRUE(is_empty);
}

TEST(SetTest, CheckSize) {
  Set<int64_t> set;
  size_t size = set.size();
  EXPECT_TRUE(size == 0); 
}

TEST(SetTest, InsertNew) {
  Set<int64_t> set({3, 5, 4, 1, 2});
  set.insert(7);
  Set<int64_t> expected_set({1, 2, 3, 4, 5, 7});
  EXPECT_EQ(expected_set, set);  
}

TEST(SetTest, InsertExisting) {
  Set<int64_t> set({3, 5, 4, 1, 2});
  set.insert(5);
  Set<int64_t> expected_set({1, 2, 3, 4, 5});
  EXPECT_EQ(expected_set, set);  
}

TEST(SetTest, EraseExisting) {
  Set<int64_t> set({3, 5, 4, 1, 2});
  set.erase(3);
  Set<int64_t> expected_set({5, 4, 1, 2});
  EXPECT_EQ(expected_set, set);  
}

TEST(SetTest, EraseNotExisting) {
  Set<int64_t> set({3, 5, 4, 1, 2});
  set.erase(9);
  Set<int64_t> expected_set({3, 5, 4, 1, 2});
  EXPECT_EQ(expected_set, set);  
}

TEST(SetTest, EraseEmpty) {
  Set<int64_t> set;
  set.erase(3);
  bool is_empty = set.empty();
  EXPECT_TRUE(is_empty);
}

TEST(SetTest, CheckExists) {
  Set<int64_t> set({3, 2});
  auto iter = set.find(2);
  EXPECT_EQ(2, *iter); 
}

TEST(SetTest, CheckNotExists) {
  Set<int64_t> set({3, 2});
  auto iter = set.find(4);
  EXPECT_EQ(set.end(), iter); 
}

TEST(SetTest, LowerBoundEqual) {
  Set<int64_t> set({3, 2, 0, 1});
  auto iter = set.lower_bound(3);
  EXPECT_EQ(*iter, 3);
}

TEST(SetTest, LowerBoundGreater) {
  Set<int64_t> set({3, 1});
  auto iter = set.lower_bound(2);
  EXPECT_EQ(*iter, 3);
}

TEST(SetTest, LowerBoundNotExist) {
  Set<int64_t> set({3, 2});
  auto iter = set.lower_bound(4);
  EXPECT_EQ(iter, set.end());
}

TEST(IteratorTest, IteratorNextLeft) {
  Set<int64_t> set({3, 1});
  auto iter = ++set.begin();
  EXPECT_EQ(3, *iter);
}

TEST(IteratorTest, IteratorNextRight) {
  Set<int64_t> set({3, 1});
  auto iter = set.begin()++;
  EXPECT_EQ(1, *iter);
}

TEST(IteratorTest, IteratorPrevLeft) {
  Set<int64_t> set({3, 1});
  auto iter = set.begin();
  ++iter;
  auto iter_res = --iter;
  EXPECT_EQ(1, *iter);
}

TEST(IteratorTest, IteratorPrevRight) {
  Set<int64_t> set({3, 1});
  auto iter = set.begin();
  ++iter;
  auto iter_res = iter--;
  EXPECT_EQ(3, *iter_res);
}

TEST(SetTest, CheckEqual) {
  Set<int64_t> set({3, 2});
  Set<int64_t> set_other{2, 3};
  EXPECT_EQ(set, set_other);
}

TEST(SetTest, CheckNotEqual) {
  Set<int64_t> set({3, 2});
  Set<int64_t> set_other{1, 3};
  EXPECT_NE(set, set_other);
}

TEST(SetTest, CheckNotEqualSize) {
  Set<int64_t> set({3, 2});
  Set<int64_t> set_other{3};
  EXPECT_NE(set, set_other);
}