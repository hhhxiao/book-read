//
// Created by agno3 on 8/27/19.
//

#ifndef DATASTRUCTURE__BINOMIAL_QUEUE_H_
#define DATASTRUCTURE__BINOMIAL_QUEUE_H_
#include <iostream>
#include <vector>
namespace xhy {
template<typename T>
class binomial_queue {
 public:
  int max(int a, int b) { return a > b ? a : b; }
  const static int DEFAULT_TREE = 1;
  struct binomial_node {
    T element;
    binomial_node *left;
    binomial_node *next_sibling;
    explicit binomial_node(const T &ele) : element(ele), left(nullptr), next_sibling(nullptr) {}
  };
  //数据成员
 private:
  std::vector<xhy::binomial_queue<T>::binomial_node> forest;
  int current_size;

  //私有方法
  int find_min_index() const;
  int capacity() const;
  binomial_node *combine_trees(binomial_node *t1, binomial_node *t2);
  void make_empty(binomial_node *&t);
  binomial_node *clone(binomial_node *t) const;

  //接口
 public:
  binomial_queue() = default;
  binomial_queue(const T &item);
  binomial_queue(const binomial_queue &rhs);
  ~binomial_queue();
  bool is_empty();
  const T &find_min() const;
  void insert(const T &t);
  void delete_min();
  void delete_min(T &x);
  void make_empty();
  void merge(binomial_queue &rhs);
 public:

};
template<typename T>
typename binomial_queue<T>::binomial_node *binomial_queue<T>::combine_trees(binomial_queue::binomial_node *t1,

    /**合并两颗同样大的树
     * 把t1的子树接到t2上,然后让t1指向t2
     */
                                                                            binomial_queue::binomial_node *t2) {
  if (t2->element < t1->element)
    return combine_trees(t2, t1);
  t2->next_sibling = t1->left;
  t1->left = t2;

}
template<typename T>
void binomial_queue<T>::merge(binomial_queue &rhs) {
  if (this == &rhs)return;
  current_size += rhs.current_size; //更新一下元素大小

  if (current_size > capacity()) {
    size_t old_tree_num = forest.size();
    int new_tree_num = max(forest.size(), rhs.forest.size()) + 1;
    forest.resize(new_tree_num);
    //更新大小并且把新加的空间设为nullptr
    for (int i = old_tree_num; i < new_tree_num; ++i)
      forest[i] = nullptr;
  }

  binomial_node *carry = nullptr;
  for (int i = 0, j = 1; j < current_size; ++i, j *= 2) {
    binomial_node *t1 = forest[i];//取出森林1的第一棵树
    //取出森林2的第i棵树(避免出现越界异常手动加了判断,超出就是nullptr)
    binomial_node *t2 = i < rhs.forest.size() ? rhs.forest[i] : nullptr;

    //这里使用一个三位二进制数表示八中情况
    int which_case = t1 == nullptr ? 0 : 1;
    which_case += t2 == nullptr ? 0 : 2;
    which_case += carry == nullptr ? 0 : 4;

    switch (which_case) {
      case 0: //t1 t2都是空的,没有树
      case 1:break; //this非空 t2空,什么都不干
      case 2://this空 t2空
        forest[i] = t2;
        rhs.forest[i] = nullptr;
      case 4://只有carry 这里的carry应该是进位(整个操作类似于逐位加法)
        //直接保留进位就行了
        forest[i] = carry;
        carry = nullptr;
        break;
      case 3: //t1 t2都非空
        carry = combine_trees(t1, t2);
        forest[i] = rhs.forest[i] = nullptr;
        break;
      case 5://只有t1和carry
        carry = combine_trees(t1, carry);
        forest[i] = nullptr;
        break;
      case 6: //只有t2和carry
        carry = combine_trees(t2, carry);
        rhs.forest[i] = nullptr;
        break;
      case 7:forest[i] = carry;
        carry = combine_trees(t1, t2);
        rhs.forest[i] = nullptr;
        break;
      default:break;
    }
  }
  for (auto &root : rhs.forest)
    root = nullptr;
  rhs.current_size = 0;
}
//没看懂
template<typename T>
void binomial_queue<T>::delete_min(T &x) {
  if (is_empty())return;//空树直接返回
  unsigned int min_index = find_min_index();
  x = forest[min_index]->element;

  binomial_node *old_root = forest[min_index];
  binomial_node *delete_tree = old_root->left;
  delete old_root;

  binomial_queue delete_queue;

  delete_queue.forest.resize(min_index + 1);
  delete_queue.current_size = (1u << min_index) - 1;
  for (unsigned int j = min_index - 1; j >= 0; --j) {
    delete_queue.forest[j] = delete_tree;
    delete_queue = delete_queue->next_sibling;
    delete_queue.forest[j]->next_sibling = nullptr;
  }

  forest[min_index] = nullptr;
  current_size -= delete_queue.current_size + 1;
  merge(delete_queue);
}
//线性查找
template<typename T>
int binomial_queue<T>::find_min_index() const {
  int i = 0;
  int min_index = 0;
  for (i = 0; forest[i] == nullptr; ++i);
  for (min_index = i; i < forest.size(); ++i) {
    if (forest[i] != nullptr && forest[i]->element < forest[min_index].element)
      min_index = i;
  }
  return min_index;
}
#endif //DATASTRUCTURE__BINOMIAL_QUEUE_H_
