#ifndef TRANSACTION_SRC_BINARY_TREE_SELF_BALANCING_BINARY_SEARCH_TREE_H_
#define TRANSACTION_SRC_BINARY_TREE_SELF_BALANCING_BINARY_SEARCH_TREE_H_

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <regex>
#include <tuple>

#include "RBTree.h"
#include "container.h"
#include "storage.h"

namespace s21 {
template <class Key, class Value>
class SelfBalancingBinarySearchTree
    : virtual public AbstractContainer<Key, Value>,
      public RBTree<Key, Value> {
 public:
  SelfBalancingBinarySearchTree() {}
  SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree &other);
  SelfBalancingBinarySearchTree(SelfBalancingBinarySearchTree &&other);
  ~SelfBalancingBinarySearchTree();

  virtual const bool Set(const Key &key, const Value &value) override final;
  [[nodiscard]] virtual std::optional<Value> Get(const Key &key) override final;
  [[nodiscard]] virtual const bool Exists(const Key &key) override final;
  virtual const bool Del(const Key &key) override final;
  virtual const bool Update(const Key &key, const Value &value) override final;
  [[nodiscard]] virtual std::vector<Key> Keys() override final;
  virtual const bool Rename(const Key &key, const Key &rename) override final;
  [[nodiscard]] virtual const std::optional<std::size_t> TTL(
      const Key &key) override final;
  [[nodiscard]] virtual std::vector<Key> Find(
      const Value &value) override final;
  virtual void Showall() override final;
  virtual const std::size_t Upload(std::ifstream &is) override final;
  virtual const std::size_t Export(std::ofstream &os) override final;

  SelfBalancingBinarySearchTree &operator=(
      SelfBalancingBinarySearchTree &other);
  SelfBalancingBinarySearchTree &operator=(
      SelfBalancingBinarySearchTree &&other);

 private:
  virtual void clear() override final;
  virtual const bool empty() const override final;
  struct RBTNode : RBTree<Key, Value>::RBTNode {};
};

#include "self_balancing_binary_search_tree.inc"
}  // namespace s21

#endif  // TRANSACTION_SRC_BINARY_TREE_SELF_BALANCING_BINARY_SEARCH_TREE_H_