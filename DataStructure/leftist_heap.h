//
// Created by agno3 on 8/27/19.
//

#ifndef DATASTRUCTURE__LEFTIST_HEAP_H_
#define DATASTRUCTURE__LEFTIST_HEAP_H_

#include <utility>
namespace xhy {
template<class T>
class leftist_heap {
 public:
  struct leftist_node {
    T element;
    leftist_node *left;
    leftist_node *right;
    int npl;//该节点的零路径长
    explicit leftist_node(const T &elements, leftist_node *left = nullptr, leftist_node *right = nullptr, int npl = 0)
        : element(elements), left(left), right(right), npl(npl) {}
  };

  leftist_node *root;
  leftist_node *merge(leftist_node *h1, leftist_node *h2);
  leftist_node *merge1(leftist_node *h1, leftist_node *h2);
  void swap_child(leftist_node *node) { if (node != nullptr) std::swap(root->left, root->right); };
  //以下俩方法的实现见`bs_tree`
  //void reclaim_memory(leftist_node *node){};
  //leftist_node *clone(leftist_node *node) const{};
 public:
  leftist_heap() = default;
  explicit leftist_heap(const T &ele) { root = new leftist_node(ele); }
  //leftist_heap(const leftist_heap &rhs);
  ~leftist_heap() { make_empty(); };

  //leftist_heap &operator=(const leftist_heap &rhs);

  bool is_empty() const { return root == nullptr; };
  const T &find_min() const { return root->element; };
  void insert(const T &x);
  void delete_min();
  void delete_min(T &x);
  void make_empty() {}
  void merge(leftist_heap &rhs);
};
//调用内部merge方法合并两棵树
template<class T>
void leftist_heap<T>::merge(leftist_heap &rhs) {
  if (this == &rhs)return;//避免merge自身
  root == merge(root, rhs.root);
  rhs.root = nullptr;
}
template<class T>
typename leftist_heap<T>::leftist_node *leftist_heap<T>::merge(leftist_heap::leftist_node *h1,
                                                               leftist_heap::leftist_node *h2) {
  //merge  h1和h2
  if (h1 == nullptr) return h2;
  if (h2 == nullptr) return h1;
  //把根节点的值大的子树合并到根节点小的子树上
  //调用merge1()函数进行合并
  if (h1->element < h2->element)
    return merge1(h1, h2);
  else
    return merge1(h2, h1);
}

template<class T>
typename leftist_heap<T>::leftist_node *leftist_heap<T>::merge1(leftist_heap::leftist_node *h1,
                                                                leftist_heap::leftist_node *h2) {
  //把h2 merge 到h1上  h2的根节点的值小于h1的根节点的值
  if (h1->left == nullptr)
    h1->left = h2;
    /*    h1
     *   /
     *  h2
     * / \      */
  else {
    //这里是一个递归merge的过程
    //把h1的右子树和h2合并
    h1->right = merge(h1->right, h2);
    if (h1->left->npl < h1->right->npl) //此时的左子树和右子树分别是左式堆,根据两子树的根节点的大小对俩节点
      //进行位置调整,以求达到整个堆是一个左式堆
      swap_child(h1);
    //这时候右子树的零路径长肯定小于左子树,因此用右子树来更新整个子树的零路径长
    h1->npl = h1->right->npl + 1;
  }
  return h1;
}
template<class T>
void leftist_heap<T>::insert(const T &x) {
  //之前的树和单个元素进行merge
  root = merge(new leftist_node(x), root);
}
template<class T>
void leftist_heap<T>::delete_min() {
  if (is_empty())return;//这里应该要抛出一个异常
  leftist_node *r = root;
  root = merge(root->left, root->right);//左子树和右子树合并就是删除根节点元素
  delete r;
}
template<class T>
void leftist_heap<T>::delete_min(T &x) {
  x = find_min();
  delete_min();
}

}

#endif //DATASTRUCTURE__LEFTIST_HEAP_H_
