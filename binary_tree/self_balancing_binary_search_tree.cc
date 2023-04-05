#include "self_balancing_binary_search_tree.h"

namespace s21 {
template <>
const std::size_t SelfBalancingBinarySearchTree<std::string, Storage>::Upload(
    std::ifstream &is) {
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
const std::size_t SelfBalancingBinarySearchTree<std::string, Storage>::Export(
    std::ofstream &os) {
  std::size_t unloaded{0};
  if (root_) {
    for (auto it = SelfBalancingBinarySearchTree::begin();
         it != SelfBalancingBinarySearchTree::end(); it++, ++unloaded) {
      os << it.getKey() << " ";
      os << *it << "\n";
    }
  }
  return unloaded;
}

}  // namespace s21
