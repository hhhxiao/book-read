//
// Created by agno3 on 8/26/19.
//

#ifndef DATASTRUCTURE_AVL_TREE_H
#define DATASTRUCTURE_AVL_TREE_H
namespace xhy {
template<typename T>
class avl_tree {
 public:

  int max(int a, int b) { return a > b ? a : b; }

  static const int ALLOWED_IMBALANCE = 1;

  struct avl_node {
    T element;
    avl_node *left;
    avl_node *right;
    int height;

    explicit avl_node(const T &ele, avl_node *l = nullptr, avl_node *r = nullptr, int h = 0) :
        element(ele), left(l), right(r), height(h) {}

  };

  avl_node *root;

  explicit avl_tree(T ele) {
    root = new avl_node(ele);
  }

  void insert(const T &val) { insert(val, root); }

  int height(avl_node *node) {
    return node == nullptr ? -1 : node->height;
  }

  void insert(const T &x, avl_node *&t) {
    if (t == nullptr)t = new avl_node(x, nullptr, nullptr);
    else if (x < t->element)insert(x, t->left);
    else if (x > t->element)insert(x, t->right);
    balance(t); //插入后进行平衡操作
  }

  void balance(avl_node *&t) {
    if (t == nullptr)return;
    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
      //对左儿子进行插入
      //下面判断插入的是左子树还是右右子树
      if (height(t->left->left) > height(t->left->right)) {
        std::cout << "左旋转！" << std::endl;
        rotateWitLeftChild(t);
      } else {
        std::cout << "双旋转" << std::endl;
        rotateWithRightChild(t->left);
        rotateWitLeftChild(t);
      }
    } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
      //对又儿子进行插入
      //下面判断插入的是左子树还是右右子树
      if (height(t->right->right) > height(t->right->left)) {
        std::cout << "右旋转！" << std::endl;
        rotateWithRightChild(t);
      } else {
        std::cout << "双旋转" << std::endl;
        rotateWitLeftChild(t->right);
        rotateWithRightChild(t);

      }
    }
    //更新t的高度
    t->height = max(height(t->left), height(t->right)) + 1;
  }

  /*
   *         k2
   *        /  \
   *       k1  Z
   *      / \
   *    X   Y
   *     k1 = k2.left,k2.left = k1.right
   *    k2     K1
   *    /\    / \
   *   Y Z   X  ?
   *   k1-right = k2:
   *    k1
   *   / \
   *  X  k2
   *     / \
   *    Y   Z
   *
   */
  void rotateWitLeftChild(avl_node *&k2) {
    avl_node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    //重新调整高度
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    //根指针重新指向k1
    k2 = k1;
  }

  /*  k2              k1
   * /  \            /  \
   * Z  k1   ==>    k2   Y
   *    /\          /\
   *   X  Y        Z  X
   */
  void rotateWithRightChild(avl_node *&k2) {
    avl_node *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(k2->height, height(k1->right)) + 1;
    k2 = k1;
  }

};

}
#endif //DATASTRUCTURE_AVL_TREE_H
