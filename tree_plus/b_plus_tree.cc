#include "b_plus_tree.h"

namespace s21 {
template <>
const std::size_t BPlusTree<std::string, Storage>::Upload(std::ifstream &is) {
  if (!m_root) {
    m_root = std::make_shared<BPTLNode<std::string, Storage> >();
  }

  std::size_t loaded{0};
  bool seted;
  Storage storage;
  std::istringstream stream;
  std::shared_ptr<BPTNode<std::string, Storage> > root;
  static const std::regex regex(
      R"(^\w{1,15}\s+\S+\s+\S+\s+\d{4}\s+\S+\s+\d+(\s+)?$)");
  for (std::string line, key; std::getline(is, line);
       stream.clear(), loaded += seted) {
    if (stream.str(line), std::regex_match(line, regex)) {
      stream >> key;
      stream >> storage;
      if (std::tie(seted, root) = m_root->Set(key, storage), root) {
        m_root = root;
      }
    }
  }
  this->m_amount_elements += loaded;
  return loaded;
}

template <>
const std::size_t BPlusTree<std::string, Storage>::Export(std::ofstream &os) {
  return m_root ? m_root->Export(os) : static_cast<std::size_t>(0);
}
}  // namespace s21