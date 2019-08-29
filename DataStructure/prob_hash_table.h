//
// Created by agno3 on 8/26/19.
//

#ifndef DATASTRUCTURE_PROB_HASH_TABLE_H
#define DATASTRUCTURE_PROB_HASH_TABLE_H

#include <vector>
#include <cstddef>

namespace xhy {
template<typename T>
class prob_hash_table {
 public:
  enum EntryType {
    ACTIVE, DELETE, EMPTY
  };
 private:

  struct hash_entry {
    T element;
    EntryType type;
    hash_entry() = default;
    explicit hash_entry(T &ele, prob_hash_table<T>::EntryType t = EntryType::EMPTY) : element(ele), type(t) {}
    bool operator==(const hash_entry &rhs) const {
      return this->element == rhs.element;
    }
  };

 private:
  std::vector<hash_entry> array;
  size_t curr_size;
 public:

  explicit prob_hash_table(size_t size) : curr_size(0) {
    array.resize(size);
    make_empty();
  }

  bool contains(const T &element) const;

  void make_empty();

  bool insert(const T &x);

  bool remove(const T &x);

 private:
  bool is_active(size_t current_pos) const;

  int find_pos(const T &x) const;

  void rehash() {}

  size_t my_hash(const T &x) const {
    static std::hash<T> hf;
    return hf(x) % array.size();
  };

};

template<typename T>
void prob_hash_table<T>::make_empty() {
  curr_size = 0;
  for (auto &x:array)
    x.type = EntryType::EMPTY;
}

template<typename T>
bool prob_hash_table<T>::contains(const T &element) const {
  return is_active(find_pos(element));
}

/**
 *找到元素x在哈希表中应该在的位置
 * （第一个没有被占用的位置）
 */
template<typename T>
int prob_hash_table<T>::find_pos(const T &x) const {
  int offset = 1;
  int current_pos = my_hash(x);//从本来应在的位置进行侦测
  while (array[current_pos].type != EMPTY && array[current_pos].element != x) {
    current_pos += offset;
    //这里实现了平方侦测
    //1 + 3 + 5+....+ (2n+1) = n^2
    offset += 2;
    if (current_pos > array.size())
      current_pos -= array.size();
  }
  return current_pos;
}

template<typename T>
bool prob_hash_table<T>::is_active(size_t current_pos) const {
  return array[current_pos].type == ACTIVE;
}

template<typename T>
bool prob_hash_table<T>::insert(const T &x) {
  int current_pos = find_pos(x);//如果找到的位置是active的说明这个函数已经存在
  if (is_active(x))return false;

  //不管这里有没有存其它的值，直接覆盖，设置激活
  array[current_pos].element = x;
  array[current_pos].type = ACTIVE;

  //如果已经存了的元素个数超过表容量的一办，翻倍表的大小，也就是重新哈希
  if (++curr_size > array.size() / 2)
    rehash();
  return true;
}

template<typename T>
bool prob_hash_table<T>::remove(const T &x) {
  int curr_pos = find_pos(x);
  if (!is_active(curr_pos))return false;
  array[curr_pos].type = DELETE;
  return true;
}

}

#endif //DATASTRUCTURE_PROB_HASH_TABLE_H
