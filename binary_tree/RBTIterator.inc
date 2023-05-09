#ifndef TRANSACTIONBINARY_TREE_RBTITERATOR_TPP_
#define TRANSACTIONBINARY_TREE_RBTITERATOR_TPP_

template <class Key, class Value>
class RBTree<Key, Value>::iterator {
  friend class RBTree;

 private:
  node_Sptr node_;
  node_Sptr root_;
  bool is_end_ = false;

 protected:
  iterator(bool is_end, node_Sptr root) : root_(root), is_end_(is_end) {}
  iterator(node_Sptr node, node_Sptr root)
      : node_(node), root_(root), is_end_(false) {}

 public:
  iterator() = default;
  iterator(const iterator &other) = default;
  iterator &operator=(const iterator &other) = default;

  iterator operator++() {
    auto next = get_next(node_);
    node_ = next;
    if (next == nullptr) {
      is_end_ = true;
    }
    return *this;
  }

  iterator operator++(int) {
    auto state = *this;
    auto next = get_next(node_);
    node_ = next;
    if (next == nullptr) {
      is_end_ = true;
    }
    return state;
  }

  iterator operator--() {
    if (is_end_) {
      node_ = get_tree_max(root_);
      is_end_ = false;
    } else {
      node_ = get_prev(node_);
    }
    return *this;
  }

  iterator operator--(int) {
    auto state = *this;
    if (is_end_) {
      node_ = get_tree_max(root_);
      is_end_ = false;
    } else {
      node_ = get_prev(node_);
    }
    return state;
  }

  const Value &operator*() const { return node_->value_; }

  const Key &getKey() const { return node_->key_; }

  bool operator==(const iterator &other) const {
    return other.root_ == root_ && other.node_ == node_ &&
           other.is_end_ == is_end_;
  }

  bool operator!=(const iterator &other) const { return !(other == *this); }
};

#endif  // TRANSACTIONBINARY_TREE_RBTITERATOR_TPP_
