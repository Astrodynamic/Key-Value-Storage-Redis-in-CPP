#ifndef TRANSACTIONTREE_PLUS_BPTNODE_H_
#define TRANSACTIONTREE_PLUS_BPTNODE_H_

#include <algorithm>
#include <any>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <regex>
#include <sstream>
#include <tuple>
#include <utility>
#include <vector>

#include "storage.h"

namespace FKG {
template <class Key, class Value>
class BPTNode : public std::enable_shared_from_this<BPTNode<Key, Value> > {
 public:
  BPTNode();
  virtual ~BPTNode() = 0;

  virtual std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value> > > Set(
      const Key &key, const Value &value) = 0;
  [[nodiscard]] virtual std::optional<Value> Get(const Key &key) = 0;
  [[nodiscard]] virtual bool Exists(const Key &key) = 0;
  virtual std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value> > > Del(
      const Key &key) = 0;
  virtual bool Update(const Key &key, const Value &value) = 0;
  [[nodiscard]] virtual std::vector<Key> Keys() = 0;
  [[nodiscard]] virtual const std::optional<std::size_t> TTL(
      const Key &key) = 0;
  [[nodiscard]] virtual std::vector<Key> Find(const Value &value) = 0;
  virtual void Showall() = 0;
  virtual std::size_t Export(std::ofstream &os) = 0;

  [[nodiscard]] virtual std::weak_ptr<BPTNode<Key, Value> > GetLeafByKey(
      const Key &key) = 0;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Split() = 0;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Merge() = 0;
  virtual bool Update(const Key &key, const Key &rename) = 0;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Remove(
      const Key &key) = 0;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Append(
      const Key &key, const std::any &value) = 0;

 protected:
  static constexpr std::size_t kDegree = 16;

  std::size_t m_elements{};
  std::vector<Key> m_keys;
  std::weak_ptr<BPTNode> m_parent;
};

template <class Key, class Value>
class BPTINode final : virtual public BPTNode<Key, Value> {
 public:
  BPTINode();
  ~BPTINode();

  virtual std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value> > > Set(
      const Key &key, const Value &value) override final;
  [[nodiscard]] virtual std::optional<Value> Get(const Key &key) override final;
  [[nodiscard]] virtual bool Exists(const Key &key) override final;
  virtual std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value> > > Del(
      const Key &key) override final;
  virtual bool Update(const Key &key, const Value &value) override final;
  [[nodiscard]] virtual std::vector<Key> Keys() override final;
  [[nodiscard]] virtual const std::optional<std::size_t> TTL(
      const Key &key) override final;
  [[nodiscard]] virtual std::vector<Key> Find(
      const Value &value) override final;
  virtual void Showall() override final;
  virtual std::size_t Export(std::ofstream &os) override final;

  [[nodiscard]] virtual std::weak_ptr<BPTNode<Key, Value> > GetLeafByKey(
      const Key &key) override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Split()
      override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Merge()
      override final;
  virtual bool Update(const Key &key, const Key &rename) override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Remove(
      const Key &key) override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Append(
      const Key &key, const std::any &value) override final;

 private:
  std::vector<std::shared_ptr<BPTNode<Key, Value> > > m_childes;
  std::weak_ptr<BPTINode<Key, Value> > m_prev;
  std::weak_ptr<BPTINode<Key, Value> > m_next;
};

template <class Key, class Value>
class BPTLNode final : virtual public BPTNode<Key, Value> {
 public:
  BPTLNode();
  ~BPTLNode();

  virtual std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value> > > Set(
      const Key &key, const Value &value) override final;
  [[nodiscard]] virtual std::optional<Value> Get(const Key &key) override final;
  [[nodiscard]] virtual bool Exists(const Key &key) override final;
  virtual std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value> > > Del(
      const Key &key) override final;
  virtual bool Update(const Key &key, const Value &value) override final;
  [[nodiscard]] virtual std::vector<Key> Keys() override final;
  [[nodiscard]] virtual const std::optional<std::size_t> TTL(
      const Key &key) override final;
  [[nodiscard]] virtual std::vector<Key> Find(
      const Value &value) override final;
  virtual void Showall() override final;
  virtual std::size_t Export(std::ofstream &os) override final;

  [[nodiscard]] virtual std::weak_ptr<BPTNode<Key, Value> > GetLeafByKey(
      const Key &key) override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Split()
      override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Merge()
      override final;
  virtual bool Update(const Key &key, const Key &rename) override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Remove(
      const Key &key) override final;
  [[nodiscard]] virtual std::shared_ptr<BPTNode<Key, Value> > Append(
      const Key &key, const std::any &value) override final;

 private:
  std::vector<Value> m_values;
  std::weak_ptr<BPTLNode<Key, Value> > m_prev;
  std::weak_ptr<BPTLNode<Key, Value> > m_next;
};

#include "BPTNode.inc"
}  // namespace FKG

#endif  // TRANSACTIONTREE_PLUS_BPTNODE_H_