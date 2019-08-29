//
// Created by agno3 on 8/25/19.
//

#ifndef DATASTRUCTURE_BS_TREE_H
#define DATASTRUCTURE_BS_TREE_H

#include <utility>
#include <ostream>

namespace xhy {
template<typename T>
class bs_tree {
 public:
  typedef T value_type;

  struct node {
    value_type element;
    node *left;
    node *right;

    explicit node(value_type ele) : element(ele), left(nullptr), right(nullptr) {
    }
  };

 public:
  //data member & ctor & dtor
  node *root;

  explicit bs_tree(const value_type &ele) {
    root = new node(ele);
  }

  ~bs_tree() {
    make_empty();
  };
  //对外接口
 public:
  const value_type &find_max() const {
    return find_max(root)->element;
  }

  const value_type &find_min() const {
    return find_min(root)->element;
  }

  bool contains(const value_type &x) const {
    return contains(x, root);
  };

  void make_empty() {
    make_empty(root);
  }

  void insert(const value_type &x) {
    insert(x, root);
  }

  void remove(const value_type &x) {
    remove(x, root);
  }

 private:
  void insert(const value_type &x, node *&t);

  void remove(const value_type &x, node *&t);

  node *find_max(node *t) const;

  node *find_min(node *t) const;

  bool contains(const value_type &x, node *t) const;

  void make_empty(node *&t);

  node *close(node *t) const;

};

template<typename T>
bool bs_tree<T>::contains(const value_type &x, bs_tree::node *t) const {
  if (t == nullptr)return false;
  else if (x < t->element)return contains(x, t->left);
  else if (x > t->element)return contains(x, t->right);
  else return true;
}

template<typename T>
typename bs_tree<T>::node *bs_tree<T>::find_max(bs_tree::node *t) const {
  if (t == nullptr)return nullptr;
  if (t->right == nullptr)return t;
  return find_max(t->right);
}

template<typename T>
typename bs_tree<T>::node *bs_tree<T>::find_min(bs_tree::node *t) const {
  if (t == nullptr)return nullptr;
  if (t->left == nullptr)return t;
  return find_min(t->left);
}

template<typename T>
void bs_tree<T>::insert(const value_type &x, bs_tree::node *&t) {
  if (t == nullptr)
    t = new node(x);
  else if (x < t->element)
    insert(x, t->left);
  else if (x > t->element)
    insert(x, t->right);
  else;
}

template<typename T>
void bs_tree<T>::remove(const value_type &x, bs_tree::node *&t) {
  if (t == nullptr)//空树直接返回
    return;
  if (x < t->element)//从左子树删除
    remove(x, t->left);
  else if (x > t->element)//从右子树删除
    remove(x, t->right);
  else { //x == element 删除当前节点
    if (t->left != nullptr && t->right != nullptr) { //左右子树都存在的情况
      t->element = find_min(t->right)->element;//赋值为又子树的最小值
      remove(t->element, t->right);//=把右子树中被赋值的那个最小值删掉
      //最小值要么是叶子节点要么只有一个右子树，绝对不会有座子树
    } else if (t->left == nullptr && t->right == nullptr) { //t是叶子节点
      delete t;
    } else {//仅有一个子节点
      node *n = t->right == nullptr ? t->left : t->right;
      t->element = n->element;
      delete n;
    }
  }
}

template<typename T>
typename bs_tree<T>::node *bs_tree<T>::close(bs_tree::node *t) const {
  if (t == nullptr)return nullptr;
  else {
    node *n = new node(t->element);
    n->left = clone(t->left);
    n->right = clone(t->right);
    return n;
  }
}

template<typename T>
void bs_tree<T>::make_empty(bs_tree::node *&t) {
  if (t != nullptr) {
    make_empty(t->left);
    make_empty(t->right);
    delete t;
  }
  t = nullptr;
}
}
#endif //DATASTRUCTURE_BS_TREE_H
