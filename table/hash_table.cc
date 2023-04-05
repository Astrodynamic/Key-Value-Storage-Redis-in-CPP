#include "hash_table.h"

namespace s21 {
template <>
const std::size_t HashTable<std::string, Storage>::Upload(std::ifstream &is) {
  std::size_t loaded{0};

  Storage storage;
  std::istringstream stream;
  static const std::regex regex(
      R"(^\w{1,15}\s+\S+\s+\S+\s+\d{4}\s+\S+\s+\d+(\s+)?$)");
  for (std::string line, key; std::getline(is, line); stream.clear()) {
    if (stream.str(line), std::regex_match(line, regex)) {
      stream >> key;
      stream >> storage;
      loaded += Set(key, storage);
    }
  }
  this->m_amount_elements += loaded;
  return loaded;
}

template <>
const std::size_t HashTable<std::string, Storage>::Export(std::ofstream &os) {
  std::size_t unloaded{0};
  for (auto &list : m_data) {
    for (auto &item : list) {
      os << item->first << " " << item->second;
      if (++unloaded != this->m_amount_elements) {
        os << '\n';
      }
    }
  }
  return unloaded;
}

}  // namespace s21