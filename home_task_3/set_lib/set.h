#ifndef SET_H
#define SET_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <vector>

template <typename T> struct Node {
  Node(T in_key)
      : key(in_key), left(nullptr), right(nullptr), parent(nullptr), height(1) {
  }
  T key;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;
  size_t height;
};

template <typename T> Node<T> *FindNext(Node<T> *node_ptr) {
  if (node_ptr == nullptr) {
    return nullptr;
  }
  if (node_ptr->right) {
    node_ptr = node_ptr->right;
    while (node_ptr->left) {
      node_ptr = node_ptr->left;
    }
    return node_ptr;
  } else {
    while (node_ptr->parent && node_ptr->parent->right == node_ptr) {
      node_ptr = node_ptr->parent;
    }
    return node_ptr->parent;
  }
}

template <typename T> Node<T> *FindPrev(Node<T> *node_ptr) {
  // if ((node_ptr == nullptr) && (node_ptr->parent != nullptr)) {
  //   return node_ptr->parent;
  // } else if (node_ptr == nullptr) {
  //   return nullptr;
  // }
  if (node_ptr == nullptr) {
    return nullptr;
  }
  if (node_ptr->left) {
    node_ptr = node_ptr->left;
    while (node_ptr->right) {
      node_ptr = node_ptr->right;
    }
    return node_ptr;
  } else {
    while (node_ptr->parent && node_ptr->parent->left == node_ptr) {
      node_ptr = node_ptr->parent;
    }
    return node_ptr->parent;
  }
}

template <typename T> class Set {
public:
  class iterator;

  Set() : begin_(nullptr), last_(nullptr), root_(nullptr), size_(0) {}

  template <typename Iter>
  Set(Iter begin, Iter end) : begin_(nullptr), last_(nullptr), root_(nullptr), size_(0) {
    for (auto iter = begin; iter != end; ++iter) {
      insert(*iter);
    }
  }

  Set(std::initializer_list<T> values)
      : begin_(nullptr), last_(nullptr), root_(nullptr), size_(0) {
    for (const auto &value : values) {
      insert(value);
    }
  }

  Set(const Set<T> &other) : size_(other.size_) {
    root_ = MakeCopy(other.root_);
    begin_ = FindMin(root_);
    last_ = FindMax(root_);
  }

  Set<T> &operator=(const Set<T> &other) {
    if (this != &other) {
      Set<T>(other).swap(*this);
    }
    return *this;
  }

  ~Set() {
    while (root_ != nullptr) {
      root_ = MakeDelete(root_, root_->key);
    }
  }

  iterator begin() const { return begin_; }

  iterator end() const { return nullptr; }

  size_t size() const { return size_; }

  bool empty() const { return root_ == nullptr; }

  bool operator==(const Set<T>& other) const {
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

  bool operator!=(const Set<T>& other) const {
    return !(*this == other);
  }

  iterator find(const T &value) const { return Search(root_, value); }

  iterator lower_bound(const T &value) const {
    Node<T>* result = nullptr;
    Node<T>* node_ptr = root_;
    while (node_ptr != nullptr) {
      if (node_ptr->key < value) {
        node_ptr = node_ptr->right;
      } else {
        result = node_ptr;
        node_ptr = node_ptr->left;
      }
    }
    return result;
  }

  void swap(Set<T> &other) {
    std::swap(begin_, other.begin_);
    std::swap(last_, other.last_);
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  void insert(const T &value) {
    root_ = MakeInsert(root_, value);
    root_->parent = nullptr;
    begin_ = FindMin(root_);
    last_ = FindMax(root_);
  }

  void erase(const T &value) {
    root_ = MakeDelete(root_, value);
    if (root_ != nullptr) {
      root_->parent = nullptr;
    }
    begin_ = FindMin(root_);
    last_ = FindMax(root_); // Fix
  }

private:
  Node<T> *FindMin(Node<T> *node_ptr) const {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    while (node_ptr->left != nullptr) {
      node_ptr = node_ptr->left;
    }
    return node_ptr;
  }

  Node<T> *FindMax(Node<T> *node_ptr) const {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    while (node_ptr->right != nullptr) {
      node_ptr = node_ptr->right;
    }
    return node_ptr;
  }

  size_t GetHeight(Node<T> *node_ptr) const {
    return (node_ptr == nullptr) ? 0 : node_ptr->height;
  }

  int64_t GetBalance(Node<T> *node_ptr) const {
    return (node_ptr == nullptr)
               ? 0
               : static_cast<int64_t>(GetHeight(node_ptr->right)) -
                     static_cast<int64_t>(GetHeight(node_ptr->left));
  }

  void FixHeight(Node<T> *node_ptr) {
    node_ptr->height =
        1 + std::max(GetHeight(node_ptr->left), GetHeight(node_ptr->right));
  }

  void FixLeftParent(Node<T> *node_ptr) {
    if (node_ptr->left) {
      node_ptr->left->parent = node_ptr;
    }
  }

  void FixRightParent(Node<T> *node_ptr) {
    if (node_ptr->right) {
      node_ptr->right->parent = node_ptr;
    }
  }

  Node<T> *SmallRotateRight(Node<T> *p_node) {
    Node<T> *q_node = p_node->left;
    p_node->left = q_node->right;
    FixLeftParent(p_node);

    q_node->right = p_node;
    FixRightParent(q_node);

    FixHeight(p_node);
    FixHeight(q_node);
    return q_node;
  }

  Node<T> *SmallRotateLeft(Node<T> *q_node) {
    Node<T> *p_node = q_node->right;
    q_node->right = p_node->left;
    FixRightParent(q_node);

    p_node->left = q_node;
    FixLeftParent(p_node);

    FixHeight(q_node);
    FixHeight(p_node);
    return p_node;
  }

  Node<T> *BigRotateLeft(Node<T> *q_node) {
    Node<T> *p_node = q_node->right;
    q_node->right = SmallRotateRight(p_node);
    FixRightParent(q_node);
    return SmallRotateLeft(q_node);
  }

  Node<T> *BigRotateRight(Node<T> *p_node) {
    Node<T> *q_node = p_node->left;
    p_node->left = SmallRotateLeft(q_node);
    FixLeftParent(p_node);
    return SmallRotateRight(p_node);
  }

  Node<T> *MakeRotates(Node<T> *node_ptr) {
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

  Node<T> *MakeCopy(Node<T> *node_ptr) {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    Node<T> *new_node = new Node(*node_ptr);
    new_node->left = MakeCopy(node_ptr->left);
    FixLeftParent(new_node);
    new_node->right = MakeCopy(node_ptr->right);
    FixRightParent(new_node);
    return new_node;
  }

  Node<T> *MakeInsert(Node<T> *node_ptr, const T &value) {
    if (node_ptr == nullptr) {
      Node<T> *new_node = new Node(value);
      ++size_;
      return new_node;
    } else if (value < node_ptr->key) {
      node_ptr->left = MakeInsert(node_ptr->left, value);
      FixLeftParent(node_ptr);
    } else if (node_ptr->key < value) {
      node_ptr->right = MakeInsert(node_ptr->right, value);
      FixRightParent(node_ptr);
    }
    node_ptr = MakeRotates(node_ptr);
    return node_ptr;
  }

  Node<T> *MakeDelete(Node<T> *node_ptr, const T &value) {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    if (value < node_ptr->key) {
      node_ptr->left = MakeDelete(node_ptr->left, value);
      FixLeftParent(node_ptr);
      node_ptr = MakeRotates(node_ptr);
      return node_ptr;
    }
    if (node_ptr->key < value) {
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
      Node<T> *result = node_ptr->right;
      delete node_ptr;
      --size_;
      result = MakeRotates(result);
      return result;
    } else if (node_ptr->right == nullptr) {
      Node<T> *result = node_ptr->left;
      delete node_ptr;
      --size_;
      result = MakeRotates(result);
      return result;
    } else {
      node_ptr->key = FindMin(node_ptr->right)->key;
      node_ptr->right = MakeDelete(node_ptr->right, node_ptr->key);
      FixLeftParent(node_ptr);
    }
    node_ptr = MakeRotates(node_ptr);
    return node_ptr;
  }

  Node<T> *Search(Node<T> *node_ptr, const T &value) const {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    if ((!(node_ptr->key < value)) && (!(value < node_ptr->key))) {
      return node_ptr;
    } else if (value < node_ptr->key) {
      return Search(node_ptr->left, value);
    } else {
      return Search(node_ptr->right, value);
    }
  }

  Node<T> *begin_;
  Node<T> *last_;
  Node<T> *root_;
  size_t size_;

  friend class Iterator;
};

template <typename T> class Set<T>::iterator {
public:
  iterator() : node_ptr_(nullptr) {}
  iterator(Node<T> *node_ptr) : node_ptr_(node_ptr) {}

  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;

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

  const value_type &operator*() const { return node_ptr_->key; }

  const value_type *operator->() const { return &(node_ptr_->key); }

  bool operator==(const iterator &other) const {
    return node_ptr_ == other.node_ptr_;
  }

  bool operator!=(const iterator &other) const {
    return !(*this == other);
  }

private:
  Node<value_type> *node_ptr_;
};

#endif // SET_H