#ifndef TRANSACTION_SRC_BINARY_TREE_RBTREE_TPP_
#define TRANSACTION_SRC_BINARY_TREE_RBTREE_TPP_

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::get_parent(
    node_Sptr root) {
  return root ? root->parent_.lock() : nullptr;
}

template <class Key, class Value>
void RBTree<Key, Value>::set_parent(node_Sptr root, node_Sptr new_parent) {
  if (root) {
    root->parent_ = new_parent;
  }
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::get_left_child(
    node_Sptr root) {
  return root ? root->left_ : nullptr;
}

template <class Key, class Value>
void RBTree<Key, Value>::set_left_child(node_Sptr root, node_Sptr child) {
  if (root) {
    root->left_ = child;
    set_parent(get_left_child(root), root);
  }
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::get_right_child(
    node_Sptr root) {
  return root ? root->right_ : nullptr;
}

template <class Key, class Value>
void RBTree<Key, Value>::set_right_child(node_Sptr root, node_Sptr child) {
  if (root) {
    root->right_ = child;
    set_parent(get_right_child(root), root);
  }
}

template <class Key, class Value>
typename RBTree<Key, Value>::RBTColor RBTree<Key, Value>::get_color(
    node_Sptr root) {
  return root ? root->color_ : BLACK;
}

template <class Key, class Value>
void RBTree<Key, Value>::set_color(node_Sptr root, RBTColor color) {
  if (root) {
    root->color_ = color;
  }
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::take_left(
    node_Sptr root) {
  node_Sptr temp;
  if (root) {
    temp = root->left_;
    root->left_ = nullptr;
  }
  return temp;
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::take_right(
    node_Sptr root) {
  node_Sptr temp;
  if (root) {
    temp = root->right_;
    root->right_ = nullptr;
  }
  return temp;
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::copy_tree(
    node_Sptr root) {
  node_Sptr temp;
  if (root) {
    temp = std::make_shared<RBTNode>(*root);
    temp->left_ = copy_tree(root->left_);
    temp->right_ = copy_tree(root->right_);
  }
  return temp;
}

template <class Key, class Value>
void RBTree<Key, Value>::left_rotate(node_Sptr root) {
  auto parent = get_parent(root);
  auto right = take_right(root);
  auto right_left = take_left(right);
  set_right_child(root, right_left);
  set_left_child(right, root);
  if (get_left_child(parent) == root) {
    set_left_child(parent, right);
  } else {
    set_right_child(parent, right);
  }
}

template <class Key, class Value>
void RBTree<Key, Value>::right_rotate(node_Sptr root) {
  auto parent = get_parent(root);
  auto left = take_left(root);
  auto left_right = take_right(left);
  set_left_child(root, left_right);
  set_right_child(left, root);
  if (get_left_child(parent) == root) {
    set_left_child(parent, left);
  } else {
    set_right_child(parent, left);
  }
}

template <class Key, class Value>
void RBTree<Key, Value>::insert(node_Sptr node) {
  node_Sptr prev;
  node_Sptr curr = root_;
  while (curr) {
    prev = curr;
    if (node->key_ < curr->key_) {
      curr = get_left_child(curr);
    } else {
      curr = get_right_child(curr);
    }
  }
  if (!prev) {
    root_ = node;
  } else {
    if (node->key_ < prev->key_) {
      set_left_child(prev, node);
    } else {
      set_right_child(prev, node);
    }
  }
  insert_fixup(node);
  begin_ = get_tree_min(root_);
  end_ = root_;
}

template <class Key, class Value>
void RBTree<Key, Value>::insert_fixup(node_Sptr node) {
  while (get_color(get_parent(node)) == RED) {
    if (get_parent(node) == get_left_child(get_parent(get_parent(node)))) {
      auto uncle = get_right_child(get_parent(get_parent(node)));
      if (get_color(uncle) == RED) {
        set_color(get_parent(node), BLACK);
        set_color(uncle, BLACK);
        set_color(get_parent(get_parent(node)), RED);
        node = get_parent(get_parent(node));
      } else if (node == get_right_child(get_parent(node))) {
        node = get_parent(node);
        left_rotate(node);
      } else {
        set_color(get_parent(node), BLACK);
        set_color(get_parent(get_parent(node)), RED);
        right_rotate(get_parent(get_parent(node)));
      }
    } else {
      auto uncle = get_left_child(get_parent(get_parent(node)));
      if (get_color(uncle) == RED) {
        set_color(get_parent(node), BLACK);
        set_color(uncle, BLACK);
        set_color(get_parent(get_parent(node)), RED);
        node = get_parent(get_parent(node));
      } else if (node == get_left_child(get_parent(node))) {
        node = get_parent(node);
        right_rotate(node);
      } else {
        set_color(get_parent(node), BLACK);
        set_color(get_parent(get_parent(node)), RED);
        left_rotate(get_parent(get_parent(node)));
      }
    }
  }
  while (get_parent(node) != nullptr) {
    node = get_parent(node);
  }
  root_ = node;
  set_color(root_, BLACK);
}

template <class Key, class Value>
void RBTree<Key, Value>::transplant(node_Sptr node_1, node_Sptr node_2) {
  if (!get_parent(node_1)) {
    root_ = node_2;
    set_parent(node_2, nullptr);
  } else if (node_1 == get_left_child(get_parent(node_1))) {
    set_left_child(get_parent(node_1), node_2);
  } else {
    set_right_child(get_parent(node_1), node_2);
  }
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::get_tree_min(
    node_Sptr root) {
  while (get_left_child(root)) {
    root = get_left_child(root);
  }
  return root;
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::get_tree_max(
    node_Sptr root) {
  while (get_right_child(root)) {
    root = get_right_child(root);
  }
  return root;
}

template <class Key, class Value>
void RBTree<Key, Value>::erase(node_Sptr node) {
  auto next = node;
  auto color = get_color(next);
  node_Sptr child;
  if (!get_left_child(node)) {
    child = get_right_child(node);
    transplant(node, get_right_child(node));
  } else if (!get_right_child(node)) {
    child = get_left_child(node);
    transplant(node, get_left_child(node));
  } else {
    next = get_tree_min(get_right_child(node));
    color = get_color(next);
    child = get_right_child(next);
    if (get_parent(next) == node) {
      set_parent(child, next);
    } else {
      transplant(next, get_right_child(next));
      set_right_child(next, get_right_child(node));
    }
    transplant(node, next);
    set_left_child(next, get_left_child(node));
    set_color(next, get_color(node));
  }
  if (color == BLACK) {
    erase_fixup(child);
  }
}

template <class Key, class Value>
void RBTree<Key, Value>::erase_fixup(node_Sptr node) {
  while (get_parent(node) && get_color(node) == BLACK) {
    if (node == get_left_child(get_parent(node))) {
      auto brother = get_right_child(get_parent(node));
      if (get_color(brother) == RED) {
        set_color(brother, BLACK);
        set_color(get_parent(node), RED);
        left_rotate(get_parent(node));
        brother = get_right_child(get_parent(node));
      }
      if (get_color(get_left_child(brother)) == BLACK &&
          get_color(get_right_child(brother)) == BLACK) {
        set_color(brother, RED);
        node = get_parent(node);
      } else if (get_color(get_right_child(brother)) == BLACK) {
        set_color(get_left_child(brother), BLACK);
        set_color(brother, RED);
        right_rotate(brother);
        brother = get_right_child(get_parent(node));
      } else {
        set_color(brother, get_color(get_parent(node)));
        set_color(get_parent(node), BLACK);
        set_color(get_right_child(brother), BLACK);
        left_rotate(get_parent(node));
        node = root_;
      }
    } else {
      auto brother = get_left_child(get_parent(node));
      if (get_color(brother) == RED) {
        set_color(brother, BLACK);
        set_color(get_parent(node), RED);
        right_rotate(get_parent(node));
        brother = get_left_child(get_parent(node));
      }
      if (get_color(get_right_child(brother)) == BLACK &&
          get_color(get_left_child(brother)) == BLACK) {
        set_color(brother, RED);
        node = get_parent(node);
      } else if (get_color(get_left_child(brother)) == BLACK) {
        set_color(get_right_child(brother), BLACK);
        set_color(brother, RED);
        left_rotate(brother);
        brother = get_left_child(get_parent(node));
      } else {
        set_color(brother, get_color(get_parent(node)));
        set_color(get_parent(node), BLACK);
        set_color(get_left_child(brother), BLACK);
        right_rotate(get_parent(node));
        node = root_;
      }
    }
  }
  set_color(node, BLACK);
}

template <class Key, class Value>
bool RBTree<Key, Value>::is_equal(const Value &value_1, const Value &value_2) {
  return (value_1 == value_2);
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::find_node(
    const Value &value) const {
  auto curr = root_;
  while (curr && value != curr->value_) {
    if (value < curr->value_) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  return curr;
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::find_node(
    const Key &key) const {
  auto curr = root_;
  while (curr && key != curr->key_) {
    if (key < curr->key_) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  return curr;
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::get_next(
    node_Sptr node) {
  node_Sptr next = get_parent(node);
  if (get_right_child(node)) {
    next = get_tree_min(get_right_child(node));
  } else {
    while (next && node == get_right_child(next)) {
      node = next;
      next = get_parent(next);
    }
  }
  return next;
}

template <class Key, class Value>
typename RBTree<Key, Value>::node_Sptr RBTree<Key, Value>::get_prev(
    node_Sptr node) {
  node_Sptr prev = get_parent(node);
  if (get_left_child(node)) {
    prev = get_tree_max(get_left_child(node));
  } else {
    while (prev && node == get_left_child(prev)) {
      node = prev;
      prev = get_parent(prev);
    }
  }
  return prev;
}

template <class Key, class Value>
typename RBTree<Key, Value>::iterator RBTree<Key, Value>::begin() const {
  iterator it_temp_1(true, root_);
  iterator it_temp_2(begin_, root_);
  return empty() ? it_temp_1 : it_temp_2;
}

template <class Key, class Value>
typename RBTree<Key, Value>::iterator RBTree<Key, Value>::end() const {
  return {true, root_};
}

#endif  // TRANSACTION_SRC_BINARY_TREE_RBTREE_TPP_
