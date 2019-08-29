//
// Created by agno3 on 8/24/19.
//

#ifndef DATASTRUCTURE_VECTOR_H
#define DATASTRUCTURE_VECTOR_H

#include <cstddef>
#include <algorithm>

namespace xhy {
template<typename T>
class vector {
 private:
  typedef size_t size_type;
  typedef T value_type;
  typedef value_type *iterator;
  typedef const value_type *const_iterator;
  static const int SPACE_CAPACITY = 16;
 private:
  value_type *objects;
  size_type size;
  size_type capacity;
 public:
  explicit vector(size_type init_size = 0) : size(init_size), capacity(init_size + SPACE_CAPACITY) {
    objects = new value_type[capacity];
  }

  vector(const vector &rhs) : size(rhs.size), capacity(rhs.capacity), objects(nullptr) {
    objects = new value_type[capacity];
    for (size_type i = 0; i < size; i++)
      objects[i] = rhs.objects[i];
  }

  vector &operator=(const vector &rhs) {
    vector copy(rhs);
    std::swap(*this, copy);
    return *this;
  }

  ~vector() { delete[] objects; }

  vector(vector &&rhs) noexcept : size(rhs.size), capacity(rhs.capacity), objects(rhs.objects) {
    rhs.objects = nullptr;
    rhs.size = 0;
    rhs.capacity = 0;
  }

  vector &operator=(vector &&rhs) noexcept {
    std::swap(size, rhs.size);
    std::swap(capacity, rhs.capacity);
    std::swap(objects, rhs.objects);
    return *this;
  }

 public:
  //扩容
  void reserve(size_type new_capacity) {
    if (new_capacity <= capacity)return;
    auto *new_array = new value_type(new_capacity);
    for (size_type i = 0; i < new_capacity; ++i)
      new_array[i] = std::move(objects[i]);
    capacity = new_capacity;
    std::swap(objects, new_array);
    delete new_array;
  }

  void resize(size_type new_size) {
    if (new_size > capacity)
      reserve(new_size * 2);
    size = new_size;
  }

  value_type &operator[](size_type index) {
    return objects[index];
  }

  const value_type &operator[](size_type index) const {
    return objects[index];
  }

  bool empty() {
    return size == 0;
  }

  size_type get_size() const {
    return size;
  }

  size_type get_capacity() const {
    return capacity;
  }

  void push_back(const value_type &x) {
    if (size == capacity)reserve(2 * capacity + 1);
    objects[size++] = x;
  }

  void push_back(const value_type &&x) {
    if (size == capacity)reserve(2 * capacity + 1);
    objects[size++] = std::move(x);
  }

  bool pop_back() {
    if (empty())return false;
    --size;
    return true;
  }

  const value_type &back() const {
    return objects[size - 1];
  }

  iterator begin() {
    return &objects[0];
  }

  iterator end() {
    return &objects[size];
  }

  const_iterator begin() const {
    return &objects[0];
  }

  const_iterator end() const {
    return &objects[size];
  }

};

}

#endif //DATASTRUCTURE_VECTOR_H
