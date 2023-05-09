#include <gtest/gtest.h>

#include "b_plus_tree.h"
#include "hash_table.h"
#include "self_balancing_binary_search_tree.h"

TEST(SelfBalancingBinarySearchTreeTest, Set_1) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  tree.Showall();
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  ASSERT_TRUE(tree.Set("1", str1));
  ASSERT_TRUE(tree.Set("2", str2));
  ASSERT_TRUE(tree.Set("4", str4));
  ASSERT_TRUE(tree.Set("5", str5));
  ASSERT_TRUE(tree.Set("6", str6));
  EXPECT_TRUE(tree.Exists("2"));
  EXPECT_TRUE(tree.Exists("6"));
  ASSERT_FALSE(tree.Set("1", str3));  // Overwrite existing key
}

TEST(HashTable, Set_1) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  ASSERT_TRUE(tree.Set("1", str1));
  ASSERT_TRUE(tree.Set("2", str2));
  ASSERT_TRUE(tree.Set("4", str4));
  ASSERT_TRUE(tree.Set("5", str5));
  ASSERT_TRUE(tree.Set("6", str6));
  EXPECT_TRUE(tree.Exists("2"));
  EXPECT_TRUE(tree.Exists("6"));
  ASSERT_FALSE(tree.Set("1", str3));  // Overwrite existing key
}

TEST(BPlusTree, Set_1) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  ASSERT_TRUE(tree.Set("1", str1));
  ASSERT_TRUE(tree.Set("2", str2));
  ASSERT_TRUE(tree.Set("4", str4));
  ASSERT_TRUE(tree.Set("5", str5));
  ASSERT_TRUE(tree.Set("6", str6));
  EXPECT_TRUE(tree.Exists("2"));
  EXPECT_TRUE(tree.Exists("6"));
  ASSERT_FALSE(tree.Set("1", str3));  // Overwrite existing key
}

TEST(SelfBalancingBinarySearchTreeTest, Get_1) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_EQ(tree.Get("1"), str1);
  ASSERT_EQ(tree.Get("2"), str2);
  ASSERT_EQ(tree.Get("4"), str4);
  ASSERT_EQ(tree.Get("5"), str5);
  ASSERT_EQ(tree.Get("6"), str6);
  ASSERT_EQ(tree.Get("3"), std::nullopt);  // Key not found
}

TEST(HashTable, Get_1) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_EQ(tree.Get("1"), str1);
  ASSERT_EQ(tree.Get("2"), str2);
  ASSERT_EQ(tree.Get("4"), str4);
  ASSERT_EQ(tree.Get("5"), str5);
  ASSERT_EQ(tree.Get("6"), str6);
  ASSERT_EQ(tree.Get("3"), std::nullopt);  // Key not found
}

TEST(BPlusTree, Get_1) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_EQ(tree.Get("1"), str1);
  ASSERT_EQ(tree.Get("2"), str2);
  ASSERT_EQ(tree.Get("4"), str4);
  ASSERT_EQ(tree.Get("5"), str5);
  ASSERT_EQ(tree.Get("6"), str6);
  ASSERT_EQ(tree.Get("3"), std::nullopt);  // Key not found
}

TEST(SelfBalancingBinarySearchTreeTest, GetAndUpdate) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  tree.Set("1", str1);
  tree.Set("2", str2);

  auto value = tree.Get("1");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), str1);
  EXPECT_FALSE(tree.Update("3", str3));  // Trying to update non-existing key
  EXPECT_TRUE(tree.Update("1", str3));
  value = tree.Get("1");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), str3);
}

TEST(HashTable, GetAndUpdate) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  tree.Set("1", str1);
  tree.Set("2", str2);

  auto value = tree.Get("1");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), str1);
  EXPECT_FALSE(tree.Update("3", str3));  // Trying to update non-existing key
  EXPECT_TRUE(tree.Update("1", str3));
  value = tree.Get("1");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), str3);
}

TEST(BPlusTree, GetAndUpdate) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  tree.Set("1", str1);
  tree.Set("2", str2);

  auto value = tree.Get("1");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), str1);
  EXPECT_FALSE(tree.Update("3", str3));  // Trying to update non-existing key
  EXPECT_TRUE(tree.Update("1", str3));
  value = tree.Get("1");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), str3);
}

TEST(SelfBalancingBinarySearchTreeTest, Exists) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);
  ASSERT_TRUE(tree.Exists("1"));
  ASSERT_FALSE(tree.Exists("3"));
  ASSERT_TRUE(tree.Exists("5"));
}

TEST(HashTable, Exists) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);
  ASSERT_TRUE(tree.Exists("1"));
  ASSERT_FALSE(tree.Exists("3"));
  ASSERT_TRUE(tree.Exists("5"));
}

TEST(BPlusTree, Exists) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);
  ASSERT_TRUE(tree.Exists("1"));
  ASSERT_FALSE(tree.Exists("3"));
  ASSERT_TRUE(tree.Exists("5"));
}

TEST(SelfBalancingBinarySearchTreeTest, Del_1) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_TRUE(tree.Exists("1"));
  ASSERT_TRUE(tree.Del("1"));
  ASSERT_FALSE(tree.Exists("1"));
  ASSERT_TRUE(tree.Exists("2"));
  ASSERT_TRUE(tree.Exists("4"));
  ASSERT_TRUE(tree.Exists("5"));
  ASSERT_TRUE(tree.Exists("6"));

  ASSERT_FALSE(tree.Del("3"));  // Non-existent key
}

TEST(HashTable, Del_1) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_TRUE(tree.Exists("1"));
  ASSERT_TRUE(tree.Del("1"));
  ASSERT_FALSE(tree.Exists("1"));
  ASSERT_TRUE(tree.Exists("2"));
  ASSERT_TRUE(tree.Exists("4"));
  ASSERT_TRUE(tree.Exists("5"));
  ASSERT_TRUE(tree.Exists("6"));

  ASSERT_FALSE(tree.Del("3"));  // Non-existent key
}

TEST(BPlusTree, Del_1) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_TRUE(tree.Exists("1"));
  ASSERT_TRUE(tree.Del("1"));
  ASSERT_FALSE(tree.Exists("1"));
  ASSERT_TRUE(tree.Exists("2"));
  ASSERT_TRUE(tree.Exists("4"));
  ASSERT_TRUE(tree.Exists("5"));
  ASSERT_TRUE(tree.Exists("6"));

  ASSERT_FALSE(tree.Del("3"));  // Non-existent key
}

// Test Update()
TEST(SelfBalancingBinarySearchTreeTest, Update) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);
  ASSERT_TRUE(tree.Update("1", str3));
  ASSERT_EQ(tree.Get("1"), str3);
  ASSERT_FALSE(tree.Update("3", str3));  // Non-existent key
}

TEST(HashTable, Update) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);
  ASSERT_TRUE(tree.Update("1", str3));
  ASSERT_EQ(tree.Get("1"), str3);
  ASSERT_FALSE(tree.Update("3", str3));  // Non-existent key
}

TEST(BPlusTree, Update) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str3, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str3.surname = "23";
  str3.name = "11231";
  str3.year_of_birth = 312;
  str3.city = "1231";
  str3.coins = 3123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);
  ASSERT_TRUE(tree.Update("1", str3));
  ASSERT_EQ(tree.Get("1"), str3);
  ASSERT_FALSE(tree.Update("3", str3));  // Non-existent key
}

// Test Keys()
TEST(SelfBalancingBinarySearchTreeTest, Keys_1) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_EQ(tree.GetAmountElements(), 5);
  std::vector<std::string> expected = {"1", "2", "4", "5", "6"};
  ASSERT_EQ(tree.Keys(), expected);
}

TEST(HashTable, Keys_1) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_EQ(tree.GetAmountElements(), 5);
#if __linux__
  std::vector<std::string> expected = {"2", "1", "5", "4", "6"};
#else
  std::vector<std::string> expected = {"1", "2", "6", "4", "5"};
#endif
  ASSERT_EQ(tree.Keys(), expected);
}

TEST(BPlusTree, Keys_1) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2, str4, str5, str6;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  str4.surname = "1";
  str4.name = "123";
  str4.year_of_birth = 10;
  str4.city = "123";
  str4.coins = 12;

  str5.surname = "2";
  str5.name = "13";
  str5.year_of_birth = 12;
  str5.city = "31";
  str5.coins = 123;

  str6.surname = "131234";
  str6.name = "1234124";
  str6.year_of_birth = 242;
  str6.city = "41234";
  str6.coins = 1234;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("4", str4);
  tree.Set("5", str5);
  tree.Set("6", str6);

  ASSERT_EQ(tree.GetAmountElements(), 5);
  std::vector<std::string> expected = {"1", "2", "4", "5", "6"};
  ASSERT_EQ(tree.Keys(), expected);
}

// Test Rename()
TEST(SelfBalancingBinarySearchTreeTest, Rename_1) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1;

  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  tree.Set("1", str1);

  EXPECT_TRUE(tree.Exists("1"));

  ASSERT_TRUE(tree.Rename("1", "2"));
  EXPECT_FALSE(tree.Exists("1"));
  EXPECT_TRUE(tree.Exists("2"));

  ASSERT_EQ(tree.Get("1"), std::nullopt);
  ASSERT_EQ(tree.Get("2"), str1);
  ASSERT_FALSE(tree.Rename("3", "4"));  // Non-existent key
}

TEST(HashTable, Rename_1) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1;

  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  tree.Set("1", str1);

  EXPECT_TRUE(tree.Exists("1"));

  ASSERT_TRUE(tree.Rename("1", "2"));
  EXPECT_FALSE(tree.Exists("1"));
#if __linux__
  EXPECT_FALSE(tree.Exists("2"));
#else
  EXPECT_TRUE(tree.Exists("2"));
#endif

  ASSERT_EQ(tree.Get("1"), std::nullopt);
#ifndef __linux__
  ASSERT_EQ(tree.Get("2"), str1);
#endif
  ASSERT_FALSE(tree.Rename("3", "4"));  // Non-existent key
}

TEST(BPlusTree, Rename_1) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1;

  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  tree.Set("1", str1);

  EXPECT_TRUE(tree.Exists("1"));

  ASSERT_TRUE(tree.Rename("1", "2"));
  EXPECT_FALSE(tree.Exists("1"));
  EXPECT_TRUE(tree.Exists("2"));

  ASSERT_EQ(tree.Get("1"), std::nullopt);
  ASSERT_EQ(tree.Get("2"), str1);
  ASSERT_FALSE(tree.Rename("3", "4"));  // Non-existent key
}

// Test Find()
TEST(SelfBalancingBinarySearchTreeTest, Find_1) {
  FKG::SelfBalancingBinarySearchTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("3", str1);
  std::vector<std::string> expected = {"1", "3"};  // Keys with value of 10
  ASSERT_EQ(tree.Find(str1), expected);
}

TEST(HashTable, Find_1) {
  FKG::HashTable<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("3", str1);
  std::vector<std::string> expected = {"1", "3"};  // Keys with value of 10
  ASSERT_EQ(tree.Find(str1), expected);
}

TEST(BPlusTree, Find_1) {
  FKG::BPlusTree<std::string, FKG::Storage> tree;
  FKG::Storage str1, str2;
  str1.surname = "1";
  str1.name = "123";
  str1.year_of_birth = 10;
  str1.city = "123";
  str1.coins = 12;

  str2.surname = "2";
  str2.name = "13";
  str2.year_of_birth = 12;
  str2.city = "31";
  str2.coins = 123;

  tree.Set("1", str1);
  tree.Set("2", str2);
  tree.Set("3", str1);
  std::vector<std::string> expected = {"1", "3"};  // Keys with value of 10
  ASSERT_EQ(tree.Find(str1), expected);
}