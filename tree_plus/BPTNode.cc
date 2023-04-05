#include "BPTNode.h"

namespace s21 {
template <>
const std::size_t BPTINode<std::string, Storage>::Export(std::ofstream &os) {
  return m_childes[0]->Export(os);
}

template <>
const std::size_t BPTLNode<std::string, Storage>::Export(std::ofstream &os) {
  std::size_t unloaded{0};
  decltype(m_next) leaf =
      std::dynamic_pointer_cast<BPTLNode<std::string, Storage> >(
          this->shared_from_this());
  for (auto temp = leaf.lock(); temp; leaf = temp->m_next, temp = leaf.lock()) {
    for (std::size_t idx = 0; idx < temp->m_elements; ++idx, ++unloaded) {
      os << temp->m_keys[idx] << " ";
      os << temp->m_values[idx] << "\n";
    }
  }
  return unloaded;
}

}  // namespace s21