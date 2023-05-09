#ifndef TRANSACTIONTREE_PLUS_B_PLUS_TREE_H_
#define TRANSACTIONTREE_PLUS_B_PLUS_TREE_H_

#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <regex>
#include <sstream>
#include <tuple>

#include "BPTNode.h"
#include "container.h"
#include "storage.h"

namespace FKG {
template <class Key, class Value>
class BPlusTree : virtual public AbstractContainer<Key, Value> {
 public:
  BPlusTree();
  BPlusTree(BPlusTree &other) = delete;
  BPlusTree(BPlusTree &&other) = delete;
  ~BPlusTree();

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

  BPlusTree &operator=(BPlusTree &other) = delete;
  BPlusTree &operator=(BPlusTree &&other) = delete;

 private:
  std::shared_ptr<BPTNode<Key, Value> > m_root;
};

#include "b_plus_tree.inc"
}  // namespace FKG

#endif  // TRANSACTIONTREE_PLUS_B_PLUS_TREE_H_