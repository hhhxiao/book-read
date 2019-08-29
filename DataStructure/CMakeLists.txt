cmake_minimum_required(VERSION 3.14)
project(DataStructure)

set(CMAKE_CXX_STANDARD 11)

add_executable(DataStructure
        main.cpp
        vector.h #向量
        list.h #双向链表
        bs_tree.h #二叉搜索树
        avl_tree.h #自平衡二叉树
        tree_tool.h
        hash_table.h #哈希表
        prob_hash_table.h #二次冲突检查哈希表
        #cuckoo_hash_table.h #杜鹃哈希
        binary_heap.h  #二叉堆
        leftist_heap.h  #左式堆
        # binomial_queue.h # 二项队列
        sort.h#>
            #插入排序 insertion_sort
            #希尔排序 shell_sort
            #堆排序 heap_sort
            #归并排序 merge_sort
        quick_sort.h #快速排序
        special_sort.h#>
            #基数排序
            #计数基数排序
        graph.h#>
            #图
            #拓扑排序
            #bfs无权图最短路径算法
            #dijkstra有权图最短路径算法
            #pirm最小生成树
        )