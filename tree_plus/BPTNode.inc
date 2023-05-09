template <class Key, class Value>
BPTNode<Key, Value>::BPTNode() {
  m_keys.resize(2 * this->kDegree - 1);
}

template <class Key, class Value>
BPTNode<Key, Value>::~BPTNode() {}

template <class Key, class Value>
BPTINode<Key, Value>::BPTINode() : BPTNode<Key, Value>() {
  m_childes.resize(2 * this->kDegree);
}

template <class Key, class Value>
BPTINode<Key, Value>::~BPTINode() {}

template <class Key, class Value>
std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value>>>
BPTINode<Key, Value>::Set(const Key &key, const Value &value) {
  return GetLeafByKey(key).lock()->Set(key, value);
}

template <class Key, class Value>
[[nodiscard]] std::optional<Value> BPTINode<Key, Value>::Get(const Key &key) {
  return GetLeafByKey(key).lock()->Get(key);
}

template <class Key, class Value>
[[nodiscard]] bool BPTINode<Key, Value>::Exists(const Key &key) {
  return GetLeafByKey(key).lock()->Exists(key);
}

template <class Key, class Value>
std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value>>>
BPTINode<Key, Value>::Del(const Key &key) {
  return GetLeafByKey(key).lock()->Del(key);
}

template <class Key, class Value>
bool BPTINode<Key, Value>::Update(const Key &key, const Value &value) {
  return GetLeafByKey(key).lock()->Update(key, value);
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> BPTINode<Key, Value>::Keys() {
  return m_childes[0]->Keys();
}

template <class Key, class Value>
bool BPTINode<Key, Value>::Update(const Key &key, const Key &rename) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);

  bool renamed{((this->m_keys.begin() + this->m_elements) != item) ||
               this->m_parent.expired()};
  if ((this->m_keys.begin() + this->m_elements) != item) {
    *item = rename;
  } else if (!this->m_parent.expired()) {
    renamed = this->m_parent.lock()->Update(key, rename);
  }
  return renamed;
}

template <class Key, class Value>
[[nodiscard]] const std::optional<std::size_t> BPTINode<Key, Value>::TTL(
    const Key &key) {
  return GetLeafByKey(key).lock()->TTL(key);
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> BPTINode<Key, Value>::Find(const Value &value) {
  return m_childes[0]->Find(value);
}

template <class Key, class Value>
void BPTINode<Key, Value>::Showall() {
  m_childes[0]->Showall();
}

template <class Key, class Value>
[[nodiscard]] std::weak_ptr<BPTNode<Key, Value>>
BPTINode<Key, Value>::GetLeafByKey(const Key &key) {
  for (std::size_t idx = 0; idx < this->m_elements; ++idx) {
    if (key < this->m_keys[idx]) {
      return m_childes[idx]->GetLeafByKey(key);
    }
  }
  return m_childes[this->m_elements]->GetLeafByKey(key);
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>> BPTINode<Key, Value>::Remove(
    const Key &key) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);

  std::shared_ptr<BPTNode<Key, Value>> root;
  if ((this->m_keys.begin() + this->m_elements) != item) {
    auto pos{std::distance(this->m_keys.begin(), item)};
    std::copy_n(item + 1, this->m_elements - pos - 1, item);
    std::copy_n(m_childes.begin() + pos + 2, this->m_elements - pos - 1,
                m_childes.begin() + pos + 1);
  } else if (!this->m_parent.expired()) {
    root = this->m_parent.lock()->Remove(key);
  }

  if (((--this->m_elements) < (this->kDegree - 1)) &&
      !this->m_parent.expired() && false) {
    root = Merge();
  }

  if (this->m_parent.expired() && this->m_elements == 0) {
    root = m_childes[0];
  }
  return root;
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>> BPTINode<Key, Value>::Append(
    const Key &key, const std::any &value) {
  auto link =
      std::any_cast<std::pair<std::shared_ptr<BPTNode<Key, Value>>,
                              std::shared_ptr<BPTNode<Key, Value>>>>(value);

  auto item = this->m_keys.begin();
  item = std::find_if_not(item, item + this->m_elements,
                          [&](const Key &src) { return src < key; });

  auto pos{std::distance(this->m_keys.begin(), item)};
  std::rotate(item, std::prev(this->m_keys.end(), 1), this->m_keys.end());
  std::rotate(m_childes.begin() + pos + 1, m_childes.end() - 1,
              m_childes.end());
  this->m_childes[pos + 1] = link.second;
  this->m_keys[pos] = key;

  if (!this->m_elements) {
    this->m_childes[pos] = link.first;
  }

  std::shared_ptr<BPTNode<Key, Value>> root;
  if (++this->m_elements >= (2 * this->kDegree - 1)) {
    root = Split();
  }
  return root;
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>>
BPTINode<Key, Value>::Split() {
  auto leaf = std::make_shared<BPTINode<Key, Value>>();
  decltype(leaf) node =
      std::dynamic_pointer_cast<BPTINode<Key, Value>>(this->shared_from_this());
  if (leaf->m_next = m_next, !m_next.expired()) {
    m_next.lock()->m_prev = leaf;
  }
  leaf->m_prev = node;
  m_next = leaf;

  std::copy_n(node->m_keys.begin() + this->kDegree, this->kDegree - 1,
              leaf->m_keys.begin());
  std::copy_n(node->m_childes.begin() + this->kDegree, this->kDegree,
              leaf->m_childes.begin());

  node->m_elements -= this->kDegree;
  leaf->m_elements += this->kDegree - 1;

  std::shared_ptr<BPTNode<Key, Value>> root;
  if (node->m_parent.expired()) {
    root = std::make_shared<BPTINode<Key, Value>>();
    node->m_parent = root;
  }
  leaf->m_parent = node->m_parent;

  decltype(root) node_1 = std::dynamic_pointer_cast<BPTINode<Key, Value>>(node);
  decltype(root) node_2 = std::dynamic_pointer_cast<BPTINode<Key, Value>>(leaf);
  auto link = std::make_pair(node_1, node_2);
  auto potential_root =
      node->m_parent.lock()->Append(node->m_keys[this->kDegree - 1], link);
  if (potential_root) {
    root = potential_root;
  }
  return root;
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>>
BPTINode<Key, Value>::Merge() {
  std::shared_ptr<BPTINode<Key, Value>> node =
      std::dynamic_pointer_cast<BPTINode<Key, Value>>(this->shared_from_this());
  decltype(node) parent{
      std::dynamic_pointer_cast<BPTINode<std::string, Storage>>(
          this->m_parent.lock())};
  auto r_sible{m_next.lock()};
  auto l_sible{m_prev.lock()};
  std::shared_ptr<BPTNode<Key, Value>> root;
  if (l_sible &&
      ((l_sible->m_elements + this->m_elements + 1) <=
       (2 * this->kDegree - 1)) &&
      l_sible->m_parent.lock() == parent) {
    auto item =
        std::find(parent->m_childes.begin(),
                  parent->m_childes.begin() + parent->m_elements, l_sible);
    auto pos{std::distance(parent->m_childes.begin(), item)};
    l_sible->m_keys[l_sible->m_elements] = parent->m_keys[pos];
    std::copy_n(this->m_keys.begin(), this->m_elements,
                l_sible->m_keys.begin() + l_sible->m_elements + 1);
    std::copy_n(this->m_childes.begin(), this->m_elements + 1,
                l_sible->m_childes.begin() + l_sible->m_elements + 1);
    l_sible->m_elements += this->m_elements + 1;
    root = parent->Remove(parent->m_keys[pos]);
  } else if (r_sible &&
             ((r_sible->m_elements + this->m_elements + 1) <=
              (2 * this->kDegree - 1)) &&
             r_sible->m_parent.lock() == parent) {
    auto item = std::find(parent->m_childes.begin(),
                          parent->m_childes.begin() + parent->m_elements, node);
    auto pos{std::distance(parent->m_childes.begin(), item)};
    this->m_keys[this->m_elements] = parent->m_keys[pos];
    std::copy_n(r_sible->m_keys.begin(), r_sible->m_elements,
                this->m_keys.begin() + this->m_elements + 1);
    std::copy_n(r_sible->m_childes.begin(), r_sible->m_elements + 1,
                this->m_childes.begin() + this->m_elements + 1);
    this->m_elements += r_sible->m_elements + 1;
    root = parent->Remove(parent->m_keys[pos]);
  }
  return root;
}

template <class Key, class Value>
BPTLNode<Key, Value>::BPTLNode() : BPTNode<Key, Value>() {
  m_values.resize(2 * this->kDegree - 1);
}

template <class Key, class Value>
BPTLNode<Key, Value>::~BPTLNode() {}

template <class Key, class Value>
std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value>>>
BPTLNode<Key, Value>::Set(const Key &key, const Value &value) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);

  bool seted{(this->m_keys.begin() + this->m_elements) == item};
  std::shared_ptr<BPTNode<Key, Value>> root;
  if (seted) {
    root = Append(key, value);
  }
  return std::make_tuple(seted, root);
}

template <class Key, class Value>
[[nodiscard]] std::optional<Value> BPTLNode<Key, Value>::Get(const Key &key) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);

  std::optional<Value> result;
  if ((this->m_keys.begin() + this->m_elements) != item) {
    result = m_values[std::distance(this->m_keys.begin(), item)];
  }
  return result;
}

template <class Key, class Value>
[[nodiscard]] bool BPTLNode<Key, Value>::Exists(const Key &key) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);
  return (this->m_keys.begin() + this->m_elements) != item;
}

template <class Key, class Value>
std::tuple<const bool, std::shared_ptr<BPTNode<Key, Value>>>
BPTLNode<Key, Value>::Del(const Key &key) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);

  bool deleted{(this->m_keys.begin() + this->m_elements) != item};
  std::shared_ptr<BPTNode<Key, Value>> root;
  if (deleted) {
    root = Remove(key);
  }
  return std::make_tuple(deleted, root);
}

template <class Key, class Value>
bool BPTLNode<Key, Value>::Update(const Key &key, const Value &value) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);

  bool updated{(this->m_keys.begin() + this->m_elements) != item};
  if (updated) {
    m_values[std::distance(this->m_keys.begin(), item)] = value;
  }
  return updated;
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> BPTLNode<Key, Value>::Keys() {
  std::vector<Key> result;
  decltype(m_next) leaf =
      std::dynamic_pointer_cast<BPTLNode<Key, Value>>(this->shared_from_this());
  for (auto temp = leaf.lock(); temp; leaf = temp->m_next, temp = leaf.lock()) {
    for (std::size_t idx = 0; idx < temp->m_elements; ++idx) {
      result.emplace_back(temp->m_keys[idx]);
    }
  }
  return result;
}

template <class Key, class Value>
bool BPTLNode<Key, Value>::Update(const Key &key, const Key &rename) {
  bool renamed{this->m_parent.expired()};
  if (!renamed) {
    renamed = this->m_parent.lock()->Update(key, rename);
  }
  return renamed;
}

template <class Key, class Value>
[[nodiscard]] const std::optional<std::size_t> BPTLNode<Key, Value>::TTL(
    const Key &key) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);
  std::size_t idx{
      static_cast<std::size_t>(std::distance(this->m_keys.begin(), item))};

  std::optional<std::size_t> seconds;
  if ((this->m_keys.begin() + this->m_elements) != item &&
      m_values[idx].GetRemovalTime().has_value()) {
    auto time_1 = std::chrono::steady_clock::now();
    auto time_2 = m_values[idx].GetRemovalTime().value();
    seconds = std::chrono::duration_cast<std::chrono::seconds>(time_2 - time_1)
                  .count();
  }
  return seconds;
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> BPTLNode<Key, Value>::Find(const Value &value) {
  std::vector<Key> result;
  decltype(m_next) leaf =
      std::dynamic_pointer_cast<BPTLNode<Key, Value>>(this->shared_from_this());
  for (auto temp = leaf.lock(); temp; leaf = temp->m_next, temp = leaf.lock()) {
    for (std::size_t idx = 0; idx < temp->m_elements; ++idx) {
      if (temp->m_values[idx] == value) {
        result.emplace_back(temp->m_keys[idx]);
      }
    }
  }
  return result;
}

template <class Key, class Value>
void BPTLNode<Key, Value>::Showall() {
  decltype(m_next) leaf =
      std::dynamic_pointer_cast<BPTLNode<Key, Value>>(this->shared_from_this());
  std::size_t iteration{};
  for (auto temp = leaf.lock(); temp; leaf = temp->m_next, temp = leaf.lock()) {
    for (std::size_t idx = 0; idx < temp->m_elements; ++idx) {
      std::cout << "> " << ++iteration << " ";
      std::cout << temp->m_values[idx] << "\n";
    }
  }
}

template <class Key, class Value>
[[nodiscard]] std::weak_ptr<BPTNode<Key, Value>>
BPTLNode<Key, Value>::GetLeafByKey([[maybe_unused]] const Key &key) {
  return std::dynamic_pointer_cast<BPTLNode<Key, Value>>(
      this->shared_from_this());
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>> BPTLNode<Key, Value>::Remove(
    const Key &key) {
  auto item = std::find(this->m_keys.begin(),
                        this->m_keys.begin() + this->m_elements, key);

  auto pos{std::distance(this->m_keys.begin(), item)};

  if (!pos) {
    Update(key, this->m_keys[1]);
  }

  std::copy_n(item + 1, this->m_elements - pos - 1, item);
  std::copy_n(m_values.begin() + pos + 1, this->m_elements - pos - 1,
              m_values.begin() + pos);

  std::shared_ptr<BPTNode<Key, Value>> root;
  if (((--this->m_elements) < (this->kDegree - 1)) &&
      !this->m_parent.expired()) {
    root = Merge();
  }
  return root;
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>> BPTLNode<Key, Value>::Append(
    const Key &key, const std::any &value) {
  auto item = this->m_keys.begin();
  item = std::find_if_not(item, item + this->m_elements,
                          [&](const Key &src) { return src < key; });

  auto pos{std::distance(this->m_keys.begin(), item)};

  if (!pos && this->m_elements > 0) {
    Update(*item, key);
  }

  std::rotate(item, this->m_keys.end() - 1, this->m_keys.end());
  std::rotate(m_values.begin() + pos, m_values.end() - 1, m_values.end());
  this->m_values[pos] = std::any_cast<Value>(value);
  this->m_keys[pos] = key;

  std::shared_ptr<BPTNode<Key, Value>> root;
  if ((++this->m_elements) >= (2 * this->kDegree - 1)) {
    root = Split();
  }
  return root;
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>>
BPTLNode<Key, Value>::Split() {
  auto leaf = std::make_shared<BPTLNode<Key, Value>>();
  decltype(leaf) node =
      std::dynamic_pointer_cast<BPTLNode<Key, Value>>(this->shared_from_this());
  if (leaf->m_next = m_next, !m_next.expired()) {
    m_next.lock()->m_prev = leaf;
  }
  leaf->m_prev = node;
  m_next = leaf;

  std::copy_n(this->m_keys.begin() + this->kDegree - 1, this->kDegree,
              leaf->m_keys.begin());
  std::copy_n(this->m_values.begin() + this->kDegree - 1, this->kDegree,
              leaf->m_values.begin());

  this->m_elements -= this->kDegree;
  leaf->m_elements += this->kDegree;

  std::shared_ptr<BPTNode<Key, Value>> root;
  if (this->m_parent.expired()) {
    root = std::make_shared<BPTINode<Key, Value>>();
    node->m_parent = root;
  }
  leaf->m_parent = node->m_parent;

  decltype(root) node_1 = std::dynamic_pointer_cast<BPTLNode<Key, Value>>(node);
  decltype(root) node_2 = std::dynamic_pointer_cast<BPTLNode<Key, Value>>(leaf);
  auto potential_root = leaf->m_parent.lock()->Append(
      leaf->m_keys[0], std::make_pair(node_1, node_2));
  if (potential_root) {
    root = potential_root;
  }
  return root;
}

template <class Key, class Value>
[[nodiscard]] std::shared_ptr<BPTNode<Key, Value>>
BPTLNode<Key, Value>::Merge() {
  std::shared_ptr<BPTLNode<Key, Value>> node =
      std::dynamic_pointer_cast<BPTLNode<Key, Value>>(this->shared_from_this());
  auto r_sible{m_next.lock()};
  auto l_sible{m_prev.lock()};
  auto parent{this->m_parent.lock()};
  std::shared_ptr<BPTNode<Key, Value>> root;
  if (l_sible && (l_sible->m_elements > (this->kDegree - 1)) &&
      l_sible->m_parent.lock() == parent) {
    ++this->m_elements;
    --l_sible->m_elements;
    std::rotate(this->m_keys.begin(), this->m_keys.end() - 1,
                this->m_keys.end());
    std::rotate(m_values.begin(), m_values.end() - 1, m_values.end());
    this->m_keys[0] = l_sible->m_keys[l_sible->m_elements];
    this->m_values[0] = l_sible->m_values[l_sible->m_elements];
    this->Update(this->m_keys[1], this->m_keys[0]);
  } else if (r_sible && (r_sible->m_elements > (this->kDegree - 1)) &&
             r_sible->m_parent.lock() == parent) {
    ++this->m_elements;
    --r_sible->m_elements;
    this->m_keys[this->m_elements - 1] = r_sible->m_keys[0];
    this->m_values[this->m_elements - 1] = r_sible->m_values[0];
    std::copy_n(r_sible->m_keys.begin() + 1, r_sible->m_elements,
                r_sible->m_keys.begin());
    std::copy_n(r_sible->m_values.begin() + 1, r_sible->m_elements,
                r_sible->m_values.begin());
    r_sible->Update(this->m_keys[this->m_elements - 1], r_sible->m_keys[0]);
  } else if (l_sible && l_sible->m_parent.lock() == parent) {
    std::copy_n(this->m_keys.begin(), this->m_elements,
                l_sible->m_keys.begin() + l_sible->m_elements);
    std::copy_n(this->m_values.begin(), this->m_elements,
                l_sible->m_values.begin() + l_sible->m_elements);
    l_sible->m_elements += this->m_elements;
    l_sible->m_next = this->m_next;
    if (r_sible) {
      r_sible->m_prev = l_sible;
    }
    root = parent->Remove(this->m_keys[0]);
  } else if (r_sible && r_sible->m_parent.lock() == parent) {
    std::copy_n(r_sible->m_keys.begin(), r_sible->m_elements,
                this->m_keys.begin() + this->m_elements);
    std::copy_n(r_sible->m_values.begin(), r_sible->m_elements,
                this->m_values.begin() + this->m_elements);
    this->m_elements += r_sible->m_elements;
    if (r_sible->m_next.expired()) {
      r_sible->m_next.lock()->m_prev = node;
    }
    this->m_next = r_sible->m_next;
    root = parent->Remove(r_sible->m_keys[0]);
  }
  return root;
}