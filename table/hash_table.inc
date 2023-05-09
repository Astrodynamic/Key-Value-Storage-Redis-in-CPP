template <class Key, class Value>
const std::vector<std::size_t> HashTable<Key, Value>::m_mpn{
    3,
    7,
    31,
    127,
    8'191,
    131'071,
    524'287,
    2'147'483'647,
    2'305'843'009'213'693'951,
    std::numeric_limits<std::size_t>::max()};

template <class Key, class Value>
HashTable<Key, Value>::HashTable() : m_mpn_cur_idx{0} {
  m_data.resize(m_mpn[m_mpn_cur_idx]);
}

template <class Key, class Value>
HashTable<Key, Value>::HashTable(HashTable &other) {
  *this = other;
}

template <class Key, class Value>
HashTable<Key, Value>::HashTable(HashTable &&other) {
  *this = other;
}

template <class Key, class Value>
HashTable<Key, Value>::~HashTable() {}

template <class Key, class Value>
[[nodiscard]] std::tuple<
    typename std::list<std::shared_ptr<std::pair<Key, Value> > >::iterator,
    std::size_t>
HashTable<Key, Value>::GetListIteratorByKey(const Key &key) {
  std::size_t idx = std::hash<Key>{}(key) % m_mpn[m_mpn_cur_idx];
  auto item =
      std::find_if(m_data[idx].begin(), m_data[idx].end(),
                   [&](const std::shared_ptr<std::pair<Key, Value> > &pair) {
                     return pair->first == key;
                   });

  return std::make_tuple(item, idx);
}

template <class Key, class Value>
const bool HashTable<Key, Value>::Set(const Key &key, const Value &value) {
  auto [item, idx] = GetListIteratorByKey(key);

  bool seted{m_data[idx].end() == item};
  if (seted) {
    m_data[idx].push_back(std::make_shared<std::pair<Key, Value> >(key, value));
    if (++this->m_amount_elements == m_mpn[m_mpn_cur_idx]) {
      ResizeHashTable();
    }
  }
  return seted;
}

template <class Key, class Value>
void HashTable<Key, Value>::ResizeHashTable() {
  decltype(m_data) temp(m_mpn[++m_mpn_cur_idx]);
  for (auto &list : m_data) {
    for (auto &pair : list) {
      std::size_t idx = std::hash<Key>{}(pair->first) % m_mpn[m_mpn_cur_idx];
      temp[idx].push_back(pair);
    }
  }
  m_data = std::move(temp);
}

template <class Key, class Value>
[[nodiscard]] std::optional<Value> HashTable<Key, Value>::Get(const Key &key) {
  auto [item, idx] = GetListIteratorByKey(key);

  std::optional<Value> result;
  if (m_data[idx].end() != item) {
    result = (*item)->second;
  }
  return result;
}

template <class Key, class Value>
[[nodiscard]] const bool HashTable<Key, Value>::Exists(const Key &key) {
  auto [item, idx] = GetListIteratorByKey(key);
  return m_data[idx].end() != item;
}

template <class Key, class Value>
const bool HashTable<Key, Value>::Del(const Key &key) {
  auto [item, idx] = GetListIteratorByKey(key);

  bool deleted{m_data[idx].end() != item};
  if (--this->m_amount_elements, deleted) {
    m_data[idx].erase(item);
  }
  return deleted;
}

template <class Key, class Value>
const bool HashTable<Key, Value>::Update(const Key &key, const Value &value) {
  auto [item, idx] = GetListIteratorByKey(key);

  bool updated{m_data[idx].end() != item};
  if (updated) {
    (*item)->second = value;
  }
  return updated;
}

template <class Key, class Value>
[[nodiscard]] std::vector<Key> HashTable<Key, Value>::Keys() {
  std::vector<Key> result;
  for (auto &list : m_data) {
    std::transform(list.begin(), list.end(), std::back_inserter(result),
                   [](auto const &item) { return item->first; });
  }
  return result;
}

template <class Key, class Value>
const bool HashTable<Key, Value>::Rename(const Key &key, const Key &rename) {
  auto [item, idx] = GetListIteratorByKey(key);

  bool renamed{m_data[idx].end() != item};
  if (renamed) {
    Set(rename, (*item)->second);
    Del(key);
  }
  return renamed;
}

template <class Key, class Value>
[[nodiscard]] const std::optional<std::size_t> HashTable<Key, Value>::TTL(
    const Key &key) {
  auto [item, idx] = GetListIteratorByKey(key);

  std::optional<std::size_t> seconds;
  if (m_data[idx].end() != item &&
      (*item)->second.GetRemovalTime().has_value()) {
    auto time_1 = std::chrono::steady_clock::now();
    auto time_2 = (*item)->second.GetRemovalTime().value();
    seconds = std::chrono::duration_cast<std::chrono::seconds>(time_2 - time_1)
                  .count();
  }
  return seconds;
}

template <class Key, class Value>
std::vector<Key> HashTable<Key, Value>::Find(const Value &value) {
  std::vector<Key> result;
  for (auto &list : m_data) {
    for (auto &item : list) {
      if (item->second == value) {
        result.push_back(item->first);
      }
    }
  }
  return result;
}

template <class Key, class Value>
void HashTable<Key, Value>::Showall() {
  std::size_t iteration{1};
  for (auto &list : m_data) {
    for (auto &item : list) {
      std::cout << "> " << iteration++ << " ";
      std::cout << item->second << "\n";
    }
  }
}

template <class Key, class Value>
HashTable<Key, Value> &HashTable<Key, Value>::operator=(HashTable &other) {
  if (this != &other) {
    m_data.clear();
    m_data.resize(m_mpn[m_mpn_cur_idx = {}]);
    this->m_amount_elements = {};
    for (auto &list : other.m_data) {
      for (auto &item : list) {
        Set(item->first, item->second);
      }
    }
  }
  return *this;
}

template <class Key, class Value>
HashTable<Key, Value> &HashTable<Key, Value>::operator=(HashTable &&other) {
  if (this != &other) {
    this->m_amount_elements = {};
    m_mpn_cur_idx = other.m_mpn_cur_idx;
    m_data = std::move(other.m_data);
    other.m_mpn_cur_idx = {};
    other.m_amount_elements = {};
  }
  return *this;
}