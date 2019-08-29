//
// Created by agno3 on 8/24/19.
//

#ifndef DATASTRUCTURE_LIST_H
#define DATASTRUCTURE_LIST_H

#include <utility>
#include <cstddef>

namespace xhy {

template<typename T>
class list {
 public:
  typedef T value_type;
  typedef size_t size_type;
 private:

  struct node {
    value_type data;
    node *prev;
    node *next;

    node() = default;

    explicit node(const value_type &d, node *p = nullptr, node *n = nullptr)
        : data(d), prev(p), next(n) {}

    explicit node(const value_type &&d, node *p = nullptr, node *n = nullptr)
        : data(std::move(d)), prev(p),
          next(n) {}
  };

  class const_iterator {
   protected:
    node *current;

    value_type &retrieve() { return current->data; }

    explicit const_iterator(node *p) : current(p) {}

   public:
    const_iterator() : current(nullptr) {}

    virtual const value_type &operator*() { return retrieve(); }

    virtual const_iterator &operator++() {
      current = current->next;
      return *this;
    }

    bool operator==(const_iterator &rhs) const { return this->current == rhs.current; }

    bool operator!=(const_iterator &rhs) const { return this->current != rhs.current; }

    friend class list<T>;
  };

  class iterator : public const_iterator {
   public:
    friend class list<T>;

    iterator() = default;

    value_type &operator*() { return const_iterator::retrieve(); }

    const value_type &operator*() const { return const_iterator::retrieve(); }

    iterator &operator++() {
      this->current = this->current->next;
      return *this;
    }

   public:
    explicit iterator(node *p) : const_iterator(p) {}

  };

 private:
  size_type the_size = 0;
  node *head;
  node *tail;

  void init();

 public:
  list() { init(); }

  list(const list &rhs);

  list &operator=(const list &rhs);

  list(const list &&rhs) noexcept;

  list &operator=(list &&rhs) noexcept;

  ~ list() {
    clear();
    delete head;
    delete tail;
  };

 public:
  iterator begin() { return iterator(head->next); }

  const_iterator begin() const { return const_iterator(head->next); }

  iterator end() { return iterator(tail); }

  const_iterator end() const { return const_iterator(tail); }

 public:
  size_type size() { return the_size; }

  bool empty() { return the_size == 0; }

  void clear() { while (!empty()) { pop_front(); }}

  value_type &front() { return *begin(); }

  const value_type &front() const { return *begin(); }

  value_type &back() { return *--end(); }

  const value_type &back() const { return *--end(); }

 public:
  iterator insert(iterator itr, const value_type &x);

  iterator insert(iterator itr, const value_type &&x);

  iterator erase(iterator itr);

  iterator erase(iterator from, iterator to);

  void push_front(const value_type &x) { insert(begin(), x); }

  void push_front(const value_type &&x) { insert(begin(), std::move(x)); }

  void push_back(const value_type &x) { insert(end(), x); }

  void push_back(const value_type &&x) { auto i = insert(end(), std::move(x)); }

  void pop_front() { erase(begin()); }

  void pop_back() { erase(--end()); }

};

//拷贝构造
template<typename T>
list<T>::list(const list &rhs) {
  init();
  for (auto &x:rhs)push_back(x);
}

//拷贝赋值
template<typename T>
list<T> &list<T>::operator=(const list &rhs) {
  list copy = rhs;//这里调用的拷贝构造函数
  std::swap(copy, *this);
  return *this;
}

//移动构造
template<typename T>
list<T>::list(const list &&rhs) noexcept
    :the_size(rhs.the_size), head(rhs.head), tail(rhs.tail) {
  rhs.head = nullptr;
  rhs.tail = nullptr;
  rhs.the_size = 0;
}

//移动赋值
template<typename T>
list<T> &list<T>::operator=(list &&rhs) noexcept {
  std::swap(the_size, rhs.the_size);
  std::swap(head, rhs.head);
  std::swap(tail, rhs.tail);
}

template<typename T>
void list<T>::init() {
  the_size = 0;
  head = new node();
  tail = new node();
  head->next = tail;
  tail->prev = head;
}

//下面的函数都缺少相关的边界和空指针检查
template<typename T>
typename list<T>::iterator list<T>::insert(list::iterator itr, const value_type &x) {
  node *curr = itr.current;//获取当前node的地址
  node *p = new node(x, curr->prev, curr); //构造新的node
  /*prev<-->p<--> curr  */
  curr->prev->next = p;//重新连接
  curr->prev = p;//重新连接
  the_size++;
  return iterator(p);
}

template<typename T>
typename list<T>::iterator list<T>::insert(list::iterator itr, const value_type &&x) {
  //  下面的四行应该可以直接用着一行代替
  //   insert(itr,std::move(x));
  node *curr = itr.current;
  node *p = new node(std::move(x), curr->prev, curr);
  curr->prev->next = p;
  curr->prev = p;
  the_size++;
  return iterator(p);
}

template<typename T>
typename list<T>::iterator list<T>::erase(list::iterator itr) {
  node *p = itr.current;
  iterator iterator(p->next);
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  the_size--;
  return iterator;
}

template<typename T>
typename list<T>::iterator list<T>::erase(list::iterator from, list::iterator to) {
  iterator it;
  for (it = from; it != to;) {
    it = erase(it);
  }
  return it;
}

}

#endif //DATASTRUCTURE_LIST_H
