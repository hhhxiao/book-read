//
// Created by agno3 on 8/26/19.
//

#ifndef DATASTRUCTURE_CUCKOO_HASH_TABLE_H
#define DATASTRUCTURE_CUCKOO_HASH_TABLE_H

#include <cstddef>
#include <vector>

namespace xhy {
template<typename T>
class cuckoo_hash_family {
 public:
  size_t hash(const T &, int which) const {/*todo 哈希函数接口*/return 0; }

  int get_number_of_functions() {/*todo*/return 0; }

  void generate_new_fun() {/*todo*/}
};

template<typename T, typename HashFamily = cuckoo_hash_family<T>>
class cuckoo_hash_table {
 private:

  constexpr static const double MAX_LOAD = 0.4;
  static const int ALLOWED_REHASH = 5;

  struct hash_entry {
    T element;
    bool is_active;

    explicit hash_entry(T element, bool isActive = false) : element(element), is_active(isActive) {}
  };

  std::vector<hash_entry> array;
  int current_size = 0;
  int num_hash_functions;
  int rehashes;
  HashFamily hash_functions;

  bool insert_helper(const T &x);

  bool is_active(int current_pos) {};

  size_t my_hash(const T &x, int which) const;

  int find_pos(const T &x) const;

  void expand();

  void rehash();

  void rehash(int new_size);




  //对外接口
 public:
  explicit cuckoo_hash_table(int size) {
    array.resize(size);
    //获取哈希函数的数量
    num_hash_functions = hash_functions.get_number_of_functions();
    rehashes = 0;
    make_empty();
  }

  void make_empty();

  bool contains(const T &x);

  bool remove(const T &x);

  bool insert(const T &x);

  int next_prime(int size);
};

template<typename T, typename HashFamily>
void cuckoo_hash_table<T, HashFamily>::make_empty() {
  current_size = 0;
  for (auto &entry: array) {
    entry.is_active = false;
  }
}

//使用特定函数计算x的散列码
//特定的哈希函数由哈希函数接口提供
template<typename T, typename HashFamily>
size_t cuckoo_hash_table<T, HashFamily>::my_hash(const T &x, int which) const {
  return hash_functions.hash(x, which) % array.size();
}

//依次计算每一个哈希函数对应的哈希值，去对应的地方查找该位置
//如果找到直接返回该位置，找不到就返回-1
template<typename T, typename HashFamily>
int cuckoo_hash_table<T, HashFamily>::find_pos(const T &x) const {
  for (int i = 0; i < num_hash_functions; ++i) {
    int pos = my_hash(x, i);
    if (is_active(pos) && array[pos].element == x)
      return pos;
  }
  return -1;
}

template<typename T, typename HashFamily>
bool cuckoo_hash_table<T, HashFamily>::contains(const T &x) {
  return find_pos(x) != 1;
}

template<typename T, typename HashFamily>
bool cuckoo_hash_table<T, HashFamily>::remove(const T &x) {
  int curr_pos = find_pos(x);
  if (!is_active(curr_pos))
    return false;
  array[curr_pos].is_active = false;
  --current_size;
  return true;
}

template<typename T, typename HashFamily>
bool cuckoo_hash_table<T, HashFamily>::insert(const T &x) {
  if (contains(x))return false;
  if (current_size >= array.size() > MAX_LOAD)
    expand();
  return insert_helper(x);
}

template<typename T, typename HashFamily>
bool cuckoo_hash_table<T, HashFamily>::insert_helper(const T &x) {
  const int limit = 100;
  while (true) {
    int last_pos = -1;
    int pos;
    for (int count = 0; count < limit; ++count) {
      for (int i = 0; i < num_hash_functions; ++i) {
        pos = my_hash(x, i);
        if (!is_active(pos)) {
          array[pos] = hash_entry(x, true);
          ++current_size;
          return true;
        }
      }
      int i = 0;
      do {
        pos = my_hash(x, i);
      } while (pos == last_pos && i++ < 5);
      last_pos = pos;
      std::swap(x, array[pos].element);
    }

    if (++rehashes > ALLOWED_REHASH) {
      expand();
      rehashes = 0;
    } else {
      rehash();
    }

  }
}

template<typename T, typename HashFamily>
void cuckoo_hash_table<T, HashFamily>::expand() {
  rehash(static_cast<int>(array.size() / MAX_LOAD));
}

template<typename T, typename HashFamily>
void cuckoo_hash_table<T, HashFamily>::rehash() {
  hash_functions.generate_new_fun();
  rehash(array.size());
}

template<typename T, typename HashFamily>
void cuckoo_hash_table<T, HashFamily>::rehash(int new_size) {
  std::vector<hash_entry> old_array = array;
  array.resize(next_prime(new_size));
  for (auto &entry : array) {
    entry.is_active = false;
  }
  current_size = 0;
  for (auto &i:old_array)
    if (i.is_active)
      insert(std::move(i.element));
}

template<typename T, typename HashFamily>
int cuckoo_hash_table<T, HashFamily>::next_prime(int size) {
  return 0;
}

}
#endif //DATASTRUCTURE_CUCKOO_HASH_TABLE_H
