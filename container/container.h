#ifndef TRANSACTION_SRC_CONTEINER_CONTEINER_H_
#define TRANSACTION_SRC_CONTEINER_CONTEINER_H_

#include <fstream>
#include <optional>
#include <utility>
#include <vector>

namespace s21 {
template <class Key, class Value>
class AbstractContainer {
 public:
  virtual ~AbstractContainer() = 0;

  [[nodiscard]] virtual const std::size_t GetAmountElements() const final;

  virtual const bool Set(const Key &key, const Value &value) = 0;
  [[nodiscard]] virtual std::optional<Value> Get(const Key &key) = 0;
  [[nodiscard]] virtual const bool Exists(const Key &key) = 0;
  virtual const bool Del(const Key &key) = 0;
  virtual const bool Update(const Key &key, const Value &value) = 0;
  [[nodiscard]] virtual std::vector<Key> Keys() = 0;
  virtual const bool Rename(const Key &key, const Key &rename) = 0;
  [[nodiscard]] virtual const std::optional<std::size_t> TTL(
      const Key &key) = 0;
  [[nodiscard]] virtual std::vector<Key> Find(const Value &value) = 0;
  virtual void Showall() = 0;
  virtual const std::size_t Upload(std::ifstream &is) = 0;
  virtual const std::size_t Export(std::ofstream &os) = 0;

 protected:
  std::size_t m_amount_elements{};
};

#include "container.inc"
}  // namespace s21

#endif  // TRANSACTION_SRC_CONTEINER_CONTEINER_H_