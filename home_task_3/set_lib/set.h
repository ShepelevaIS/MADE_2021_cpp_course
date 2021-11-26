#ifndef SET_H
#define SET_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <vector>

struct Node {
  Node() : left(nullptr), right(nullptr), parent(nullptr) {}
  Node(Node *in_left, Node *in_right, Node *in_parent)
      : left(in_left), right(in_right), parent(in_parent) {}
  virtual ~Node() {}

  Node *left;
  Node *right;
  Node *parent;
};

template <typename T> struct ValueNode : public Node {
  ValueNode(const T &in_key) : Node(), key(in_key), height(1) {}
  virtual ~ValueNode() {}

  T key;
  size_t height;
};

template <typename T> ValueNode<T> *AsValueNode(Node *node_ptr) {
  return static_cast<ValueNode<T> *>(node_ptr);
}

Node *FindNext(Node *node_ptr) {
  Node *origin_ptr = node_ptr;
  if (node_ptr == nullptr) {
    return nullptr;
  }
  if (node_ptr->right) {
    node_ptr = node_ptr->right;
    while (node_ptr->left) {
      node_ptr = node_ptr->left;
    }
  } else {
    while (node_ptr->parent && node_ptr->parent->right == node_ptr) {
      node_ptr = node_ptr->parent;
    }
    node_ptr = node_ptr->parent;
  }
  return node_ptr;
}

Node *FindPrev(Node *node_ptr) {
  if (node_ptr == nullptr) {
    return nullptr;
  }
  if (node_ptr->left) {
    node_ptr = node_ptr->left;
    while (node_ptr->right) {
      node_ptr = node_ptr->right;
    }
  } else {
    while (node_ptr->parent && node_ptr->parent->left == node_ptr) {
      node_ptr = node_ptr->parent;
    }
    node_ptr = node_ptr->parent;
  }
  return node_ptr;
}

template <typename T> class Set {
public:
  class iterator;

  Set() : size_(0) {
    end_ = new Node();
    begin_ = end_;
    root_ = end_;
  }

  template <typename Iter> Set(Iter begin, Iter end) : Set() {
    for (auto iter = begin; iter != end; ++iter) {
      insert(*iter);
    }
  }

  Set(std::initializer_list<T> values) : Set() {
    for (const auto &value : values) {
      insert(value);
    }
  }

  Set(const Set<T> &other) : size_(other.size_) {
    root_ = MakeCopy(other.root_);
    UpdatePointers();
  }

  Set<T> &operator=(const Set<T> &other) {
    if (this != &other) {
      Set<T>(other).swap(*this);
    }
    return *this;
  }

  ~Set() {
    while (root_ != end_) {
      root_ = MakeDelete(root_, AsValueNode<T>(root_)->key);
    }
    delete end_;
  }

  iterator begin() const { return iterator(begin_); }

  iterator end() const { return iterator(end_); }

  size_t size() const { return size_; }

  bool empty() const { return begin_ == end_; }

  bool operator==(const Set<T> &other) const {
    if (size_ != other.size_) {
      return false;
    }
    auto left_iter = begin();
    auto right_iter = other.begin();
    while (left_iter != end() && right_iter != end()) {
      if (*left_iter != *right_iter) {
        return false;
      }
      ++left_iter;
      ++right_iter;
    }
    return true;
  }

  bool operator!=(const Set<T> &other) const { return !(*this == other); }

  iterator find(const T &value) const { return iterator(Search(root_, value)); }

  iterator lower_bound(const T &value) const {
    Node *result = end_;
    Node *node_ptr = root_;
    while (node_ptr != nullptr && node_ptr != end_) {
      if (AsValueNode<T>(node_ptr)->key < value) {
        node_ptr = node_ptr->right;
      } else {
        result = node_ptr;
        node_ptr = node_ptr->left;
      }
    }
    return iterator(result);
  }

  void swap(Set<T> &other) {
    std::swap(begin_, other.begin_);
    std::swap(end_, other.end_);
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  void insert(const T &value) {
    root_ = MakeInsert(root_, value);
    UpdatePointers();
  }

  void erase(const T &value) {
    root_ = MakeDelete(root_, value);
    UpdatePointers();
  }

private:
  void UpdatePointers() {
    if (root_ != nullptr) {
      root_->parent = nullptr;
    }
    begin_ = FindLeftmost(root_);
    end_ = FindRightmost(root_);
  }

  Node *FindLeftmost(Node *node_ptr) const {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    while (node_ptr->left != nullptr) {
      node_ptr = node_ptr->left;
    }
    return node_ptr;
  }

  Node *FindRightmost(Node *node_ptr) const {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    while (node_ptr->right != nullptr) {
      node_ptr = node_ptr->right;
    }
    return node_ptr;
  }

  size_t GetHeight(Node *node_ptr) const {
    return (node_ptr == nullptr) ? 0 : AsValueNode<T>(node_ptr)->height;
  }

  int64_t GetBalance(Node *node_ptr) const {
    return (node_ptr == nullptr)
               ? 0
               : static_cast<int64_t>(GetHeight(node_ptr->right)) -
                     static_cast<int64_t>(GetHeight(node_ptr->left));
  }

  void FixHeight(Node *node_ptr) {
    if (node_ptr == nullptr) {
      return;
    }
    AsValueNode<T>(node_ptr)->height =
        1 + std::max(GetHeight(AsValueNode<T>(node_ptr->left)),
                     GetHeight(AsValueNode<T>(node_ptr->right)));
  }

  void FixLeftParent(Node *node_ptr) {
    if (node_ptr == nullptr) {
      return;
    }
    if (node_ptr->left) {
      node_ptr->left->parent = node_ptr;
    }
  }

  void FixRightParent(Node *node_ptr) {
    if (node_ptr == nullptr) {
      return;
    }
    if (node_ptr->right) {
      node_ptr->right->parent = node_ptr;
    }
  }

  Node *SmallRotateRight(Node *p_node) {
    Node *q_node = p_node->left;
    p_node->left = q_node->right;
    FixLeftParent(p_node);

    q_node->right = p_node;
    FixRightParent(q_node);

    FixHeight(p_node);
    FixHeight(q_node);
    return q_node;
  }

  Node *SmallRotateLeft(Node *q_node) {
    Node *p_node = q_node->right;
    q_node->right = p_node->left;
    FixRightParent(q_node);

    p_node->left = q_node;
    FixLeftParent(p_node);

    FixHeight(q_node);
    FixHeight(p_node);
    return p_node;
  }

  Node *BigRotateLeft(Node *q_node) {
    Node *p_node = q_node->right;
    q_node->right = SmallRotateRight(p_node);
    FixRightParent(q_node);
    return SmallRotateLeft(q_node);
  }

  Node *BigRotateRight(Node *p_node) {
    Node *q_node = p_node->left;
    p_node->left = SmallRotateLeft(q_node);
    FixLeftParent(p_node);
    return SmallRotateRight(p_node);
  }

  Node *MakeRotates(Node *node_ptr) {
    if (node_ptr == nullptr || node_ptr == end_) {
      return node_ptr;
    }
    FixHeight(node_ptr);
    if (GetBalance(node_ptr) == 2) {
      if (GetBalance(node_ptr->right) < 0) {
        node_ptr = BigRotateLeft(node_ptr);
      } else {
        node_ptr = SmallRotateLeft(node_ptr);
      }
    } else if (GetBalance(node_ptr) == -2) {
      if (GetBalance(node_ptr->left) > 0) {
        node_ptr = BigRotateRight(node_ptr);
      } else {
        node_ptr = SmallRotateRight(node_ptr);
      }
    }
    return node_ptr;
  }

  Node *MakeCopy(Node *node_ptr) {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    ValueNode<T> *new_node = new ValueNode<T>(*AsValueNode<T>(node_ptr));
    new_node->left = MakeCopy(node_ptr->left);
    FixLeftParent(new_node);
    new_node->right = MakeCopy(node_ptr->right);
    FixRightParent(new_node);
    return new_node;
  }

  Node *MakeInsert(Node *node_ptr, const T &value) {
    if (node_ptr == nullptr) {
      Node *new_node = new ValueNode<T>(value);
      ++size_;
      return new_node;
    } else if (node_ptr == end_) {
      Node *new_node = new ValueNode<T>(value);
      ++size_;
      new_node->right = end_;
      FixRightParent(new_node);
      return new_node;
    } else if (value < AsValueNode<T>(node_ptr)->key) {
      node_ptr->left = MakeInsert(node_ptr->left, value);
      FixLeftParent(node_ptr);
    } else if (AsValueNode<T>(node_ptr)->key < value) {
      node_ptr->right = MakeInsert(node_ptr->right, value);
      FixRightParent(node_ptr);
    }
    node_ptr = MakeRotates(node_ptr);
    return node_ptr;
  }

  Node *MakeDelete(Node *node_ptr, const T &value) {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    if (node_ptr == end_) {
      return end_;
    }
    if (value < AsValueNode<T>(node_ptr)->key) {
      node_ptr->left = MakeDelete(node_ptr->left, value);
      FixLeftParent(node_ptr);
      node_ptr = MakeRotates(node_ptr);
      return node_ptr;
    }
    if (AsValueNode<T>(node_ptr)->key < value) {
      node_ptr->right = MakeDelete(node_ptr->right, value);
      FixRightParent(node_ptr);
      node_ptr = MakeRotates(node_ptr);
      return node_ptr;
    }
    if (node_ptr->left == nullptr && node_ptr->right == nullptr) {
      delete node_ptr;
      --size_;
      return nullptr;
    }
    if (node_ptr->left == nullptr) {
      Node *result = node_ptr->right;
      delete node_ptr;
      --size_;
      result = MakeRotates(result);
      return result;
    } else if (node_ptr->right == nullptr) {
      Node *result = node_ptr->left;
      delete node_ptr;
      --size_;
      result = MakeRotates(result);
      return result;
    } else {
      AsValueNode<T>(node_ptr)->key =
          AsValueNode<T>(FindRightmost(node_ptr->left))->key;
      AsValueNode<T>(node_ptr)->left =
          MakeDelete(node_ptr->left, AsValueNode<T>(node_ptr)->key);
      FixLeftParent(node_ptr);
    }
    node_ptr = MakeRotates(node_ptr);
    return node_ptr;
  }

  Node *Search(Node *node_ptr, const T &value) const {
    if (node_ptr == nullptr || node_ptr == end_) {
      return node_ptr;
    }
    if ((!(AsValueNode<T>(node_ptr)->key < value)) &&
        (!(value < AsValueNode<T>(node_ptr)->key))) {
      return node_ptr;
    } else if (value < AsValueNode<T>(node_ptr)->key) {
      return Search(node_ptr->left, value);
    } else {
      return Search(node_ptr->right, value);
    }
  }

  Node *begin_;
  Node *end_;
  Node *root_;
  size_t size_;

  friend class Iterator;
};

template <typename T> class Set<T>::iterator {
public:
  iterator() : node_ptr_(nullptr) {}
  iterator(Node *node_ptr) : node_ptr_(node_ptr) {}

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

  iterator &operator++() {
    node_ptr_ = FindNext(node_ptr_);
    return *this;
  }

  iterator operator++(int) {
    iterator res(*this);
    node_ptr_ = FindNext(node_ptr_);
    return res;
  }

  iterator &operator--() {
    node_ptr_ = FindPrev(node_ptr_);
    return *this;
  }

  iterator operator--(int) {
    iterator res(*this);
    node_ptr_ = FindPrev(node_ptr_);
    return res;
  }

  const value_type &operator*() const { return AsValueNode<T>(node_ptr_)->key; }

  const value_type *operator->() const {
    return &(AsValueNode<T>(node_ptr_)->key);
  }

  bool operator==(const iterator &other) const {
    return node_ptr_ == other.node_ptr_;
  }

  bool operator!=(const iterator &other) const {
    return node_ptr_ != other.node_ptr_;
  }

private:
  Node *node_ptr_;
};

#endif // SET_H