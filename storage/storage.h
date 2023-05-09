#ifndef TRANSACTIONSTORAGE_STORAGE_H_
#define TRANSACTIONSTORAGE_STORAGE_H_

#include <chrono>
#include <iomanip>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

namespace FKG {
class Storage {
 public:
  std::optional<std::string> surname;
  std::optional<std::string> name;
  std::optional<std::size_t> year_of_birth;
  std::optional<std::string> city;
  std::optional<std::size_t> coins;

  friend std::ostream &operator<<(std::ostream &os, const Storage &storage);
  friend std::istringstream &operator>>(std::istringstream &stream,
                                        Storage &storage);

  Storage() = default;
  Storage(const Storage &other);
  ~Storage() = default;

  void SetRemovalTime(const std::chrono::seconds seconds);
  [[nodiscard]] const std::optional<std::chrono::steady_clock::time_point>
  GetRemovalTime() const;

  Storage &operator=(const Storage &other);
  [[nodiscard]] bool operator==(const Storage &other) const;

  [[nodiscard]] bool operator!=(const Storage &other) const;
  [[nodiscard]] bool operator<(const Storage &other) const;
  [[nodiscard]] bool operator>(const Storage &other) const;
  [[nodiscard]] bool operator>=(const Storage &other) const;
  [[nodiscard]] bool operator<=(const Storage &other) const;

 private:
  std::optional<std::chrono::steady_clock::time_point> m_removal_time;

  template <class T>
  [[nodiscard]] inline bool Equal(const T &lhs, const T &rhs) const;
  template <class T>
  [[nodiscard]] inline bool NotEqual(const T &lhs, const T &rhs) const;
  template <class T>
  [[nodiscard]] inline bool IsLess(const T &lhs, const T &rhs) const;
  template <class T>
  [[nodiscard]] inline bool IsGreater(const T &lhs, const T &rhs) const;
  template <class T>
  [[nodiscard]] inline bool IsLessOrEqual(const T &lhs, const T &rhs) const;
  template <class T>
  [[nodiscard]] inline bool IsGreaterOrEqual(const T &lhs, const T &rhs) const;

  template <class T>
  inline void WriteValue(std::ostream &os, const T &src,
                         const std::size_t width) const;
};

std::ostream &operator<<(std::ostream &os, const Storage &storage);
std::istringstream &operator>>(std::istringstream &stream, Storage &storage);

}  // namespace FKG

#endif  // TRANSACTIONSTORAGE_STORAGE_H_