//
// Created by agno3 on 8/26/19.
//

#ifndef DATASTRUCTURE_HASH_TABLE_H
#define DATASTRUCTURE_HASH_TABLE_H

#include <vector>
#include <list>
#include <functional>
#include <algorithm>

namespace xhy {
template<class T>
class hash_table {
 private:
  std::vector<std::list<T>> lists;
  size_t curr_size;

  void rehash() {
      //todo 再散列
  };

  size_t my_hash(const T &x) const {
      static std::hash<T> hf;
      return hf(x) % lists.size();
  };

 public:
  explicit hash_table(int size = 101) : curr_size(0) {
      lists.reserve(size);
  };

  bool contains(const T &x) const {
      //取到对应位置的链表
      std::list<T> list = lists[my_hash(x)];
      //使用标准库中的方法进行查找
      return std::find(std::begin(list), std::end(list), x) != std::end(list);
  };

  void make_empty() {
      for (std::list<T> &list : lists)list.clear();
  };

  bool insert(const T &x) {
      std::list<T> list = lists[my_hash(x)];
      auto iter = std::find(std::begin(list), std::end(list), x);
      if (iter != std::end(list))return false;
      list.push_back(x);
      if (++curr_size > list.size())
          rehash();
      return true;
  };

  bool remove(const T &x) {
      std::list<T> list = lists[my_hash(x)];
      auto iter = std::find(std::begin(list), std::end(list), x);
      if (iter == std::end(list))
          return false;
      list.erase(iter);
      --curr_size;
      return true;
  }
};
}
#endif //DATASTRUCTURE_HASH_TABLE_H
