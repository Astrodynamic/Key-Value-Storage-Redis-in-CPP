template <class Key, class Value>
AbstractContainer<Key, Value>::~AbstractContainer() {}

template <class Key, class Value>
[[nodiscard]] const std::size_t
AbstractContainer<Key, Value>::GetAmountElements() const {
  return m_amount_elements;
}