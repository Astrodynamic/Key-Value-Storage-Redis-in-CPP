template <class Key, class Value>
BPlusTree<Key, Value>::BPlusTree() {}

template <class Key, class Value>
BPlusTree<Key, Value>::~BPlusTree() {}

template <class Key, class Value>
const bool BPlusTree<Key, Value>::Set(const Key &key, const Value &value) {
  if (!m_root) {
    m_root = std::make_shared<BPTLNode<Key, Value> >();
  }
  auto [seted, root] = m_root->Set(key, value);
  if (this->m_amount_elements += seted, root) {
    m_root = root;
  }
  return seted;
}

template <class Key, class Value>
[[nodiscard]] std::optional<Value> BPlusTree<Key, Value>::Get(const Key &key) {
  return m_root ? m_root->Get(key) : std::optional<Value>();
}

template <class Key, class Value>
[[nodiscard]] const bool BPlusTree<Key, Value>::Exists(const Key &key) {
  return m_root ? m_root->Exists(key) : false;
}

template <class Key, class Value>
const bool BPlusTree<Key, Value>::Del(const Key &key) {
  bool deleted{};
  if (m_root) {
    std::shared_ptr<BPTNode<Key, Value> > root;
    std::tie(deleted, root) = m_root->Del(key);
    if ((this->m_amount_elements -= deleted),
        !this->m_amount_elements || root) {
      m_root = root;
    }
  }
  return deleted;
}

template <class Key, class Value>
const bool BPlusTree<Key, Value>::Update(const Key &key, const Value &value) {
  return m_root ? m_root->Update(key, value) : false;
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> BPlusTree<Key, Value>::Keys() {
  return m_root ? m_root->Keys() : std::vector<Key>();
}

template <class Key, class Value>
const bool BPlusTree<Key, Value>::Rename(const Key &key, const Key &rename) {
  bool renamed{false};
  if (m_root && key != rename) {
    std::optional<Value> value = m_root->Get(key);
    if (renamed = value.has_value(), renamed) {
      m_root->Del(key);
      m_root->Set(rename, value.value());
    }
  }
  return renamed;
}

template <class Key, class Value>
[[nodiscard]] const std::optional<std::size_t> BPlusTree<Key, Value>::TTL(
    const Key &key) {
  return m_root ? m_root->TTL(key) : std::optional<std::size_t>();
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> BPlusTree<Key, Value>::Find(const Value &value) {
  return m_root ? m_root->Find(value) : std::vector<Key>();
}

template <class Key, class Value>
void BPlusTree<Key, Value>::Showall() {
  if (m_root) {
    m_root->Showall();
  }
}