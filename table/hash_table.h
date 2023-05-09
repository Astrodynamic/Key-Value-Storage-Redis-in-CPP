#ifndef TRANSACTIONTABLE_HASH_TABLE_H_
#define TRANSACTIONTABLE_HASH_TABLE_H_

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <memory>
#include <regex>
#include <tuple>

#include "container.h"
#include "storage.h"

namespace FKG {
template <class Key, class Value>
class HashTable : virtual public AbstractContainer<Key, Value> {
 public:
  HashTable();
  HashTable(HashTable &other);
  HashTable(HashTable &&other);
  ~HashTable();

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

  HashTable &operator=(HashTable &other);
  HashTable &operator=(HashTable &&other);

 private:
  std::size_t m_mpn_cur_idx;
  static const std::vector<std::size_t> m_mpn;

  std::vector<std::list<std::shared_ptr<std::pair<Key, Value> > > > m_data;

  void ResizeHashTable();
  [[nodiscard]] std::tuple<
      typename std::list<std::shared_ptr<std::pair<Key, Value> > >::iterator,
      std::size_t>
  GetListIteratorByKey(const Key &key);
};

#include "hash_table.inc"
}  // namespace FKG

#endif  // TRANSACTIONTABLE_HASH_TABLE_H_