#ifndef TRANSACTION_SRC_BINARY_TREE_RBTREE_H_
#define TRANSACTION_SRC_BINARY_TREE_RBTREE_H_

#include <chrono>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <optional>
#include <utility>

namespace s21 {
template <class Key, class Value>
class RBTree {
 protected:
  enum RBTColor : bool { BLACK, RED };
  struct RBTNode {
    Key key_;
    Value value_;
    RBTColor color_;

    std::weak_ptr<RBTNode> parent_;
    std::shared_ptr<RBTNode> left_;
    std::shared_ptr<RBTNode> right_;
  };

  std::shared_ptr<RBTNode> root_;
  std::shared_ptr<RBTNode> begin_;
  std::shared_ptr<RBTNode> end_;

  using node_Sptr = std::shared_ptr<RBTNode>;
  using node_Wptr = std::weak_ptr<RBTNode>;

  RBTree() {}
  RBTree(RBTree &other) = delete;
  RBTree(RBTree &&other) = delete;

  class iterator;

  virtual iterator begin() const;
  virtual iterator end() const;
  virtual void clear() = 0;
  virtual const bool empty() const = 0;
  void insert(node_Sptr node);
  node_Sptr find_node(const Value &value) const;
  node_Sptr find_node(const Key &key) const;
  void erase(node_Sptr node);

 private:
  static node_Sptr get_parent(node_Sptr root);
  void set_parent(node_Sptr root, node_Sptr new_parent);
  static node_Sptr get_left_child(node_Sptr root);
  void set_left_child(node_Sptr root, node_Sptr child);
  static node_Sptr get_right_child(node_Sptr root);
  void set_right_child(node_Sptr root, node_Sptr child);
  RBTColor get_color(node_Sptr root);
  void set_color(node_Sptr root, RBTColor color);
  node_Sptr take_left(node_Sptr root);
  node_Sptr take_right(node_Sptr root);
  node_Sptr copy_tree(node_Sptr root);
  void left_rotate(node_Sptr root);
  void right_rotate(node_Sptr root);
  static node_Sptr get_tree_min(node_Sptr root);
  static node_Sptr get_tree_max(node_Sptr root);
  bool is_equal(const Value &value_1, const Value &value_2);
  static node_Sptr get_next(node_Sptr node);
  static node_Sptr get_prev(node_Sptr node);

 private:
  void insert_fixup(node_Sptr node);
  void transplant(node_Sptr node_1, node_Sptr node_2);
  void erase_fixup(node_Sptr node);
};

#include "RBTIterator.inc"
#include "RBTree.inc"
}  // namespace s21

#endif  // TRANSACTION_SRC_BINARY_TREE_RBTREE_H_
