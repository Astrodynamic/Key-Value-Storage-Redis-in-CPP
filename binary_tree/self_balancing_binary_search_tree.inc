template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>::SelfBalancingBinarySearchTree(
    SelfBalancingBinarySearchTree &other) {
  *this = other;
}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>::SelfBalancingBinarySearchTree(
    SelfBalancingBinarySearchTree &&other) {
  *this = std::move(other);
}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>::~SelfBalancingBinarySearchTree() {}

template <class Key, class Value>
const bool SelfBalancingBinarySearchTree<Key, Value>::Set(const Key &key,
                                                          const Value &value) {
  if (!(this->find_node(key))) {
    auto new_node = std::make_shared<RBTNode>();
    new_node->key_ = key;
    new_node->value_ = value;
    RBTree<Key, Value>::insert(new_node);
    ++(this->m_amount_elements);
    return true;
  }
  return false;
}

template <class Key, class Value>
[[nodiscard]] std::optional<Value>
SelfBalancingBinarySearchTree<Key, Value>::Get(const Key &key) {
  auto node = this->find_node(key);
  return node ? node->value_ : std::optional<Value>();
}

template <class Key, class Value>
[[nodiscard]] const bool SelfBalancingBinarySearchTree<Key, Value>::Exists(
    const Key &key) {
  if (this->find_node(key)) return true;
  return false;
}

template <class Key, class Value>
const bool SelfBalancingBinarySearchTree<Key, Value>::Del(const Key &key) {
  auto node = this->find_node(key);
  if (node) {
    this->erase(node);
    --(this->m_amount_elements);
    return true;
  }
  return false;
}

template <class Key, class Value>
const bool SelfBalancingBinarySearchTree<Key, Value>::Update(
    const Key &key, const Value &value) {
  auto node = this->find_node(key);
  if (node) {
    node->value_ = value;
    return true;
  }
  return false;
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key>
SelfBalancingBinarySearchTree<Key, Value>::Keys() {
  std::vector<Key> finded_keys;
  for (auto it = SelfBalancingBinarySearchTree::begin();
       it != SelfBalancingBinarySearchTree::end(); it++)
    finded_keys.push_back(it.getKey());
  return finded_keys;
}

template <class Key, class Value>
const bool SelfBalancingBinarySearchTree<Key, Value>::Rename(
    const Key &key, const Key &rename) {
  auto node = this->find_node(key);
  if (node) {
    auto tmp = node->value_;
    return (Del(key) && Set(rename, tmp));
  }
  return false;
}

template <class Key, class Value>
[[nodiscard]] const std::optional<std::size_t>
SelfBalancingBinarySearchTree<Key, Value>::TTL(const Key &key) {
  auto item = this->find_node(key);
  std::optional<std::size_t> seconds;
  if (item && item->value_.GetRemovalTime().has_value()) {
    auto time_1 = std::chrono::steady_clock::now();
    auto time_2 = item->value_.GetRemovalTime().value();
    ;
    seconds = std::chrono::duration_cast<std::chrono::seconds>(time_2 - time_1)
                  .count();
  }
  return seconds;
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> SelfBalancingBinarySearchTree<Key, Value>::Find(
    const Value &value) {
  std::vector<Key> finded_keys;
  for (auto it = SelfBalancingBinarySearchTree::begin();
       it != SelfBalancingBinarySearchTree::end(); it++)
    if (*it == value) finded_keys.push_back(it.getKey());
  return finded_keys;
}

template <class Key, class Value>
void SelfBalancingBinarySearchTree<Key, Value>::Showall() {
  std::size_t iteration{};
  for (auto it = SelfBalancingBinarySearchTree::begin();
       it != SelfBalancingBinarySearchTree::end(); it++) {
    std::cout << "> " << iteration++ << " ";
    std::cout << *it << "\n";
  }
}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>
    &SelfBalancingBinarySearchTree<Key, Value>::operator=(
        SelfBalancingBinarySearchTree &other) {
  if (*this != other) {
    clear();
    for (auto it = other.begin(); it != other.end(); it++) {
      Set(it.getKey(), *it);
    }
  }
}

template <class Key, class Value>
SelfBalancingBinarySearchTree<Key, Value>
    &SelfBalancingBinarySearchTree<Key, Value>::operator=(
        SelfBalancingBinarySearchTree &&other) {
  if (*this != other) {
    clear();
    std::swap(this->root_, other.root_);
    std::swap(this->begin_, other.begin_);
    std::swap(this->end_, other.end_);
    std::swap(this->m_amount_elements, other.m_amount_elements);
  }
}

template <class Key, class Value>
void SelfBalancingBinarySearchTree<Key, Value>::clear() {
  while (this->root_) this->erase(this->begin_);
  this->m_amount_elements = 0;
}

template <class Key, class Value>
const bool SelfBalancingBinarySearchTree<Key, Value>::empty() const {
  return this->m_amount_elements == 0;
}