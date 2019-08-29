//
// Created by agno3 on 8/28/19.
//

#ifndef DATASTRUCTURE__QUICK_SORT_H_
#define DATASTRUCTURE__QUICK_SORT_H_
#include <vector>
#include <utility>
#include "sort.h"
namespace xhy {
using std::vector;
template<typename T>
class quick_sort {
 public:
  /**
   * 依据快排基本原理的一种递归排序
   * 但是算不上真正的快排
   * @param array
   */
  static void SORT(vector<T> &array) {
    if (array.size() > 1) {
      vector<T> smaller;
      vector<T> same;
      vector<T> bigger;
      //选取一个中间值
      T item = array[array.size() / 2];
      for (auto &i:array) {
        if (i < item)smaller.push_back(std::move(i));
        else if (i == item)same.push_back(std::move(i));
        else if (i > item)bigger.push_back(std::move(i));
      }
      SORT(smaller);
      SORT(bigger);
      std::move(std::begin(smaller), std::end(smaller), std::begin(array));
      std::move(std::begin(same), std::end(same), std::begin(array) + smaller.size());
      std::move(std::begin(bigger), std::end(bigger), std::end(array) - bigger.size());
    }
  }

  static void q_sort(vector<T> &array) {
    q_sort(array, 0, array.size() - 1);
  }

  /**
   * 返回left center 和 right的中间值
   * 将他们排序并将枢纽元放置到array的末端
   */
  static const T &median(vector<T> &array, int left, int right) {
    int center = (left + right) / 2;
    if(array[center] < array[left])
      std::swap(array[left],array[center]);
    if(array[right] < array[left])
      std::swap(array[right],array[left]);
    if(array[right] < array[center])
      std::swap(array[right],array[center]);

    std::swap(array[center],array[right-1]);
    return array[right-1];
  }

/**
 * 进行内部调用的递归快排算法
 * @param array
 * @param left
 * @param right
 */
  static void q_sort(vector<T> &array, int left, int right) {
    if (left + 10 <= right) {
      //这里进行递归快排
      const T& pivot = median(array,left,right);
      int i = left,j = right - 1;
      for (;;) {
        while(array[++i] < pivot);
        while(pivot < array[--j]);
        if(i < j)
          std::swap(array[j],array[i]);
        else
          break;
      }
      std::swap(array[i],array[right-1]);
      q_sort(array,left,i-1);
      q_sort(array,i+1,right);
    } else {
      //小于10个元素的时候直接进行归并
      sort<T>::insertion_sort(array, left, right + 1);
    }
  }

};
}
#endif //DATASTRUCTURE__QUICK_SORT_H_
