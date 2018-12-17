#ifndef FENWICK_H
#define FENWICK_H

#include <vector>

namespace Fenwick {

template <class T>
class Fenwick {
private:
  class Node;

public:
  typedef T value_type ;
  typedef value_type & reference;
  typedef const value_type & const_reference;

  Fenwick() { }
  Fenwick(int size) { resize(size); };

  void resize(int size) {
    data_.resize(size);
    tree_.resize(size);
    size_ = size;
  }

  int size () const {
    return size_;
  }

  value_type sum(int n) const;

  Node operator[] (int idx) { return Node(*this, idx); }

private:
  class Node {
    public:
      Node(Fenwick &tree, int idx) : tree_(tree), idx_(idx) { }

      operator value_type() const { return tree_.data_[idx_]; }

      Node & operator+=(const_reference delta) {
        tree_.update(idx_, delta);
        return *this;
      }

    private:
      Fenwick &tree_;
      const int idx_;
  };

  std::vector<value_type> data_;
  std::vector<value_type> tree_;

  int size_;

  void update(int idx, const_reference delta);
  void update_tree(int idx, const_reference delta);

  friend class Node;
};

template<class T>
void Fenwick<T>::update(int idx, const_reference delta) {
  data_[idx] += delta;

  update_tree(idx + 1, delta);
}

template<class T>
void Fenwick<T>::update_tree(int idx, const_reference delta) {
  if (idx < 0 || idx >= size_) {
    return;
  }

  tree_[idx - 1] += delta;

  idx = idx + (idx & (-idx));

  update_tree(idx, delta);
}

template<class T>
typename Fenwick<T>::value_type
Fenwick<T>::sum(int n) const {
  value_type ret = 0;

  if (n > size_) {
    n = size_;
  }

  while (n > 0) {
    ret += tree_[n - 1];
    n = n - (n & (-n));
  }

  return ret;
}

}

#endif // FENWICK_H
