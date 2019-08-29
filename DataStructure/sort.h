//
// Created by agno3 on 8/27/19.
//来自书籍<数据结构与算法--c++语言描述>的排序算法 不包括快速排序
//

#ifndef DATASTRUCTURE__SORT_H_
#define DATASTRUCTURE__SORT_H_
#include <vector>
#include <utility>
namespace xhy {
template<typename T>
class sort {
 public:
  //插入排序
  static void insertion_sort(std::vector<T> &array, int start, int end) {
    if (start == end)
      return;
    T tmp;
    for (int p = start + 1; p != end; ++p) {
      tmp = std::move(array[p]);
      int j = 0;
      for (j = p; j != start && tmp < array[j - 1]; --j)
        array[j] = std::move(array[j - 1]);
      array[j] = std::move(tmp);
    }
  }

  static void shell_sort(std::vector<T> &array) {
    //希尔排序的基本理论就是增量排序
    //每趟都排序a[0] ,a[k] a[2k]... // a[1],a[1+k],a[1+2k].. //a[k-1] a[k-1+2k]..
    //k逐渐递减至k = 1
    //这里的,每一趟的排序都用的插入排序,每过一趟,k变为一半,
    for (int gap = array.size() / 2; gap > 0; gap /= 2) { //gap就是k
      for (int i = gap; i < array.size(); ++i) {
        T tmp = std::move(array[i]);
        int j = i;
        for (; j >= gap && tmp < array[j - gap]; j -= gap)
          array[j] = std::move(array[j - gap]);
        array[j] = std::move(tmp);
      }
    }
  }

  /*
   * 大名鼎鼎的堆排序
   * 平均比较次数是 2n log(n)-O(n log log n)
   * 先通过上滤建立堆再下滤删除最小(大)的
   */
  static void heap_sort(std::vector<T> &array) {
    //下率前一半元素(默认叶子节点不管填满)
    for (int i = array.size() / 2 - 1; i >= 0; i--)
      perc_down(array, i, array.size());
    //下滤删除根节点元素
    for (int j = array.size() - 1; j > 0; --j) {
      //删除之前把根元素(当前堆中的最大值)塞到空余出来的空间上.
      std::swap(array[0], array[j]);
      perc_down(array, 0, j);
    }
  }
  /**
   * 堆排序中的内部操作(下滤)
   * @param array 数组
   * @param i 开始下过滤的位置
   * @param n 堆的逻辑大小(不包括已经排好序的堆的大小)
   */
  static int left_child(int i) { return 2 * i + 1; }
  //下滤
  static void perc_down(std::vector<T> &array, int i, int n) {
    int child;
    T tmp;
    for (tmp = std::move(array[i]); left_child(i) < n; i = child) {
      child = left_child(i);
      if (child != n - 1 && array[child] < array[child + 1])++child;
      if (tmp < array[child])
        array[i] = std::move(array[child]);
      else break;
    }
    array[i] = std::move(tmp);
  }

  //归并排序(merge sort) O(n log n)
  /*外部方法*/
  static void merge_sort(std::vector<T> &array) {
    std::vector<T> temp_array(array.size());
    merge_sort(array, temp_array, 0, array.size() - 1);
  }
  /*内部方法*/
  static void merge_sort(std::vector<T> &array, std::vector<T> &temp_array, int left, int right) {
    if (left < right) {
      int center = (left + right) / 2;
      merge_sort(array, temp_array, left, center);
      merge_sort(array, temp_array, center + 1, right);
      //执行到下面这一步的时候[left,center]和[center+1,right]这两部分自身是排好序的
      merge(array, temp_array, left, center + 1, right);
    }
  }

  /**
   * 合并子数组已经排序的两部分的内部方法
   * @param array
   * @param temp_array 放置归并结果的数组
   * @param left_pos  子数组最左元素的下标
   * @param right_pos  后半部分起点的下标
   * @param right_end  子数组最后元素的下标
   */
  static void merge(std::vector<T> &array, std::vector<T> &temp_array, int left_pos, int right_pos, int right_end) {
    int left_end = right_pos - 1;
    int temp_pos = left_pos;
    int num_elements = right_end - left_pos + 1;//子序列的元素个数
    /*
     * [left_pos-------(right_pos - 1 == left_end)]
     * [right_pos-------------right_end]
     */
    //移动指针法同时遍历俩链表(只遍历公共长度部分)
    /**
     * 指针1 --> left_pos
     * 指针2--> right_pos
     * 指针3--> temp_pos
     */
    while (left_pos <= left_end && right_pos <= right_end) {
      if (array[left_pos] < array[right_pos])
        temp_array[temp_pos++] = std::move(array[left_pos++]);
      else
        temp_array[temp_pos++] = std::move(array[right_pos++]);
    }
    //这里本应该判断哪个子数组还有剩余.但是它直接把两个数组全部复制了一遍
    while (left_pos <= left_end)
      temp_array[temp_pos++] = std::move(array[left_pos++]);
    while (right_pos <= right_end)
      temp_array[temp_pos++] = std::move(array[right_pos++]);
    //把temp的东西复制回原数组
    for (int i = 0; i < num_elements; ++i, --right_end) {
      array[right_end] = std::move(temp_array[right_end]);
    }
  }




};
}
#endif //DATASTRUCTURE__SORT_H_
