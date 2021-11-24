#ifndef SET_H
#define SET_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

template <typename T>
struct Node {
  Node(T in_key) : key(in_key), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
  T key;
  Node<T>* left;
  Node<T>* right;
  Node<T>* parent;
  size_t height;
};

template <typename T>
Node<T>* FindNext(Node<T>* node_ptr) {
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

template <typename T>
Node<T>* FindPrev(Node<T>* node_ptr) {
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

template <typename T>
class Iterator {
public:
  Iterator(Node<T>* node_ptr) : node_ptr_(node_ptr) {}

  Iterator& operator++() {
    node_ptr_ = FindNext(node_ptr_);
    return *this;
  }

  Iterator& operator++(int) {
    Iterator res(*this);
    node_ptr_ = FindNext(node_ptr_);
    return res;
  }

  Iterator& operator--() {
    node_ptr_ = FindPrev(node_ptr_);
    return *this;
  }

  Iterator& operator--(int) {
    Iterator res(*this);
    node_ptr_ = FindPrev(node_ptr_);
    return res;
  }

  const T& operator*() const {
    return node_ptr_->key;
  }

  bool operator!=(const Iterator& other) const  {
    return node_ptr_ != other.node_ptr_;
  }

private:
  Node<T>* node_ptr_;
};

template <typename T>
class Set { 
public:
  Set() : begin_(nullptr), root_(nullptr), size_(0) {}
  
  template <typename Iter>
  Set(Iter begin, Iter end) : begin_(nullptr), root_(nullptr), size_(0) {
    for (auto iter = begin; iter != end; ++iter) {
      Insert(*iter);
    }
  }

  Set(std::initializer_list<T> values) : begin_(nullptr), root_(nullptr), size_(0) {
    for (const auto &value : values) {
      Insert(value);
    }
  }

  Set(const Set<T> &other) {
    // NOT IMPLEMENTED
  }

  Set<T> &operator=(const Set<T> &other) {
    if (this != &other) {
      Set<T>(other).Swap(*this);
    }
    return *this;
  }

  ~Set() {
    while (root_ != nullptr) {
      root_ = MakeDelete(root_, root_->key);
    }
  }

  Iterator<T> Begin() const {
    return begin_;
  }

  Iterator<T> End() const {
    return nullptr;
  }

  Iterator<T> Find(const T& value) const {
    return Search(root_, value);
  }

  Iterator<T> LowerBound(const T& value) const {

  }

  size_t Size() const {
    return size_;
  }

  bool Empty() const {
    return root_ == nullptr;
  }

  void Swap(Set<T>& other) {
    std::swap(root_, other.root_);
  }

  // void Print() const {
  //   Node<T>* node_ptr = root_;
  //   while (node_ptr->left) {
  //     node_ptr = node_ptr->left;
  //   }
  //   while (node_ptr) {
  //     std::cout << node_ptr->key << " ";
  //     node_ptr = FindNext(node_ptr);
  //   }
  //   std::cout << std::endl;
  // }

  void Print() const {
    for (auto iter = Begin(); iter != End(); ++iter) {
      std::cout << *iter << ' ';
    }
    std::cout << std::endl;
  }

  void PrintReversed() const {
    Node<T>* node_ptr = root_;
    while (node_ptr->right) {
      node_ptr = node_ptr->right;
    }
    while (node_ptr) {
      std::cout << node_ptr->key << " ";
      node_ptr = FindPrev(node_ptr);
    }
    std::cout << std::endl;
  }

  // void Insert(const T& value) {
  //   auto value_ptr = make_insert(value);
  //   auto prev_value_ptr = FindPrev(value_ptr);
  //   auto next_value_ptr = FindNext(value_ptr);
  //   value_ptr->prev = prev_value_ptr;
  //   value_ptr->next = next_value_ptr;
  //   prev_value_ptr->next = value_ptr;
  //   next_value_ptr->prev = value_ptr;
  // }

  void Insert(const T& value) {
    root_ = MakeInsert(root_, value);
    root_->parent = nullptr;
    begin_ = FindMin(root_);
  }

  void Delete(const T& value) {
    root_ = MakeDelete(root_, value);
    root_->parent = nullptr;
    begin_ = FindMin(root_);
  }

  bool Exists(const T& value) const {
    return Search(root_, value) != nullptr;
  }

  std::optional<T> Next(const T& value) const {
    const Node<T>* node_ptr = root_;
    const Node<T>* result = nullptr;
    while (node_ptr != nullptr) {
      if (node_ptr->key > value) {
        result = node_ptr;
        node_ptr = node_ptr->left;
      } else {
        node_ptr = node_ptr->right;
      }
    }
    return (result == nullptr) ? std::nullopt :
        std::optional<T>(result->key);
  }

  std::optional<T> Prev(const T& value) const {
    const Node<T>* node_ptr = root_;
    const Node<T>* result = nullptr;
    while (node_ptr != nullptr) {
      if (node_ptr->key < value) {
        result = node_ptr;
        node_ptr = node_ptr->right;
      } else {
        node_ptr = node_ptr->left;
      }
    }
    return (result == nullptr) ? std::nullopt :
        std::optional<T>(result->key);
  }

  // void Print() const {
  //   Print(root_);
  //   std::cout << std::endl;
  // }

  // void Print(Node<T>* node) const {
  //   if (node->left) {
  //     Print(node->left);
  //   }
  //   std::cout << node->key << " ";
  //   if (node->right) {
  //     Print(node->right);
  //   }
  // }

  // void PrintParents() const {
  //   PrintParents(root_);
  // }

  // void PrintParents(Node<T>* node) const {
  //   if (node->left) {
  //     PrintParents(node->left);
  //   }
  //   if (node->parent) {
  //     std::cout << node->parent->key << " ";
  //   }
  //   if (node->right) {
  //     PrintParents(node->right);
  //   }
  // }

private:
  Node<T>* FindMin(Node<T>* node_ptr) const {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    while (node_ptr->left != nullptr) {
      node_ptr = node_ptr->left;
    }
    return node_ptr;
  }

  Node<T>* FindMax(Node<T>* node_ptr) const {
    while (node_ptr->right != nullptr) {
      node_ptr = node_ptr->right;
    }
    return node_ptr;
  }

  size_t GetHeight(Node<T>* node_ptr) const {
    return (node_ptr == nullptr) ? 0 : node_ptr->height;
  }

  int64_t GetBalance(Node<T>* node_ptr) const {
    return (node_ptr == nullptr) ? 0 : static_cast<int64_t>(GetHeight(node_ptr->right)) -
        static_cast<int64_t>(GetHeight(node_ptr->left));
  }

  void FixHeight(Node<T>* node_ptr) {
    node_ptr->height = 1 + std::max(GetHeight(node_ptr->left), 
        GetHeight(node_ptr->right));
  }

  void FixLeftParent(Node<T>* node_ptr) {
    if (node_ptr->left) {
      node_ptr->left->parent = node_ptr;
    }
  }

  void FixRightParent(Node<T>* node_ptr) {
    if (node_ptr->right) {
      node_ptr->right->parent = node_ptr;
    } 
  }

  Node<T>* SmallRotateRight(Node<T>* p_node) {
    Node<T>* q_node = p_node->left;
    p_node->left = q_node->right;
    FixLeftParent(p_node);

    q_node->right = p_node;
    FixRightParent(q_node);

    FixHeight(p_node);
    FixHeight(q_node);
    return q_node;
  }

  Node<T>* SmallRotateLeft(Node<T>* q_node) {
    Node<T>* p_node = q_node->right;
    q_node->right = p_node->left;
    FixRightParent(q_node);

    p_node->left = q_node;
    FixLeftParent(p_node);

    FixHeight(q_node);
    FixHeight(p_node);
    return p_node;
  }

  Node<T>* BigRotateLeft(Node<T>* q_node) {
    Node<T>* p_node = q_node->right;
    q_node->right = SmallRotateRight(p_node);
    FixRightParent(q_node);
    return SmallRotateLeft(q_node);
  }

  Node<T>* BigRotateRight(Node<T>* p_node) {
    Node<T>* q_node = p_node->left;
    p_node->left = SmallRotateLeft(q_node);
    FixLeftParent(p_node);
    return SmallRotateRight(p_node);
  }

  Node<T>* MakeRotates(Node<T>* node_ptr) {
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

  // Node<T>* MakeInsert(const T& value) {
  //   Node<T>* node_ptr = root_;
  //   if (node_ptr == nullptr) {
  //     root_ = new Node(value);
  //     return root_;
  //   }
  //   while (true) {
  //     if (value == node_ptr->key) {
  //       return nullptr;
  //     } else if (value < node_ptr->key node_ptr->left) {
  //       node_ptr = node_ptr->left;
  //     } else if (value > node_ptr->key && node_ptr->right) {
  //       node_ptr = node_ptr->right;
  //     } else {
  //     }
  //   }
  // }

  Node<T>* MakeInsert(Node<T>* node_ptr, const T& value) {
    if (node_ptr == nullptr) {
      Node<T>* new_node = new Node(value);
      ++size_;
      return new_node;
    } else if (value < node_ptr->key) {
      node_ptr->left = MakeInsert(node_ptr->left, value);
      FixLeftParent(node_ptr);
    } else if (value > node_ptr->key) {
      node_ptr->right = MakeInsert(node_ptr->right, value);
      FixRightParent(node_ptr);
    } 
    node_ptr = MakeRotates(node_ptr);
    return node_ptr;
  }

  Node<T>* MakeDelete(Node<T>* node_ptr, const T& value) {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    if (value < node_ptr->key) {
      node_ptr->left = MakeDelete(node_ptr->left, value);
      FixLeftParent(node_ptr);
      node_ptr = MakeRotates(node_ptr);
      return node_ptr;
    }
    if (value > node_ptr->key) {
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
      Node<T>* result = node_ptr->right;
      delete node_ptr;
      --size_;
      result = MakeRotates(result);
      return result;
    } else if (node_ptr->right == nullptr) {
      Node<T>* result = node_ptr->left;
      delete node_ptr;
      --size_;
      result = MakeRotates(result);
      return result;
    } else {
      node_ptr->key = FindMax(node_ptr->left)->key;
      node_ptr->left = MakeDelete(node_ptr->left, node_ptr->key);
      FixLeftParent(node_ptr);
    }
    node_ptr = MakeRotates(node_ptr);
    return node_ptr;
  }

  // Node<T>* LowerBound(Node<T>* node_ptr, const T& value) const {
  //   Node<T>* node_ptr = root_;
  //   Node<T>* result = nullptr;
  //   while (node_ptr != nullptr) {
  //     if (node_ptr->key > value) {
  //       result = node_ptr;
  //       node_ptr = node_ptr->left;
  //     } else {
  //       node_ptr = node_ptr->right;
  //     }
  //   }
  //   return (result == nullptr) ? std::nullopt :
  //       std::optional<T>(result->key);
  // }
  // }

  Node<T>* Search(Node<T>* node_ptr, const T& value) const {
    if (node_ptr == nullptr) {
      return nullptr;
    }
    if (node_ptr->key == value) {
      return node_ptr;
    } else if (value < node_ptr->key) {
      return Search(node_ptr->left, value);
    } else {
      return Search(node_ptr->right, value);
    }
  }

  Node<T>* begin_;
  Node<T>* root_;
  size_t size_;
};


#endif // SET_H