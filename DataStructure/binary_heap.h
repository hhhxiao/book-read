//
// Created by agno3 on 8/26/19.
//

#ifndef DATASTRUCTURE_BINARY_HEAP_H
#define DATASTRUCTURE_BINARY_HEAP_H

#include <stdexcept>
#include <vector>

namespace xhy {
    template<typename T>
    class binary_heap {
    private:
        int current_size;
        std::vector<T> array;

        void build_heap();

        void percolate_down(int hole);

    public:
        explicit binary_heap(unsigned  long capacity = 127) : current_size(0) {
            array.resize(capacity);
        };

        explicit binary_heap(const std::vector<T> &items) {
            array.resize(items.size() + 10);
            current_size = items.size();
            for (int i = 0; i < items.size(); ++i) {
                array[i + 1] = items[i];
            }
            //构造堆
            build_heap();
        }

        bool is_empty() const { return current_size == 0; };

        const T &find_min() const { return is_empty() ? nullptr : array[1]; };

        void insert(const T &x);

        void delete_min();

        void delete_min(T &x);

        void make_empty() { current_size = 0; }
    };

    template<typename T>
    void binary_heap<T>::insert(const T &x) {
        //堆数组没空间啦，扩容为两倍
        if (current_size == array.size() - 1)
            array.resize(array.size() * 2);
        //current_size 是当前堆中的元素个数，也是最后一个元素在数组中的下标
        int hole = ++current_size; //hole就是新增添的位置的下标
        T copy = x;
        //这里进行上滤操作，有效减少赋值次数
        array[0] = std::move(copy);
        for (; x < array[hole / 2]; hole /= 2)
            array[hole] = std::move(array[hole / 2]);
        array[hole] = std::move(array[0]);
    }

    template<typename T>
    void binary_heap<T>::delete_min() {
        if (is_empty())
            throw std::runtime_error("empty heap!!!");
        array[1] = std::move(array[current_size--]);
        percolate_down(1);
    }

    template<typename T>
    void binary_heap<T>::delete_min(T &x) {
        if (is_empty())
            throw std::runtime_error("empty heap!!!");
        x = std::move(array[1]);
        array[1] = std::move(array[current_size--]);
        percolate_down(1);
    }

    //下滤，删除操作
    template<typename T>
    void binary_heap<T>::percolate_down(int hole) {
        int child;
        T tmp = std::move(array[hole]);
        for (; hole * 2 <= current_size; hole = child/*更新hole*/) {
            child = hole * 2;
            //child != current_size就说明还有其他当前的hold两个子树都在
            //两个子树都在的时候进一步判断两个子树哪个更小
            //如果第一个条件不满足就说吗只有一个子树
            if (child != current_size && array[child + 1] < array[child])++child;
            //把提取到的最小的子树和当前的值进行比较，一般情况下必然成立,直接上提
            if (array[child] < tmp)
                array[hole] = std::move(array[child]);
            else break;
        }
        array[hole] = std::move(tmp);
    }

    template<typename T>
    void binary_heap<T>::build_heap() {
        for (int i = current_size / 2; i > 0; --i)
            percolate_down(i);
    }
}


#endif //DATASTRUCTURE_BINARY_HEAP_H
