//
// Created by agno3 on 8/29/19.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include <cstddef>
#include <map>
#include <list>
#include <algorithm>
#include <iostream>
#include <set>
#include <queue>

namespace xhy {
    using std::map;
    using std::set;

    template<typename T, typename D = int>
    class graph {
    private:
        /**
         *
         * D 距离
         * 默认是有向的图
         */
        map<T, map<T, D>> g;


    public:
        static const D INF = 65535;

        graph() = default;
        /*
         * 下面的inline方法是 构建图的一些基本操作
         */
        //增加一条v1到v2的边
        void add_edge(const T &v1, const T &v2, D distance = 1) {
            //v2不存在就插入v2
            auto iter = g.find(v2);
            if (iter == g.end())
                g.insert({v2, {}});
            g[v1].insert({v2, distance});
        }

        void add_undirected(const T &v1, const T &v2, D distance = 1) {
            add_edge(v1, v2, distance);
            add_edge(v2, v1, distance);
        }

        //增加一个顶点
        void add_vertex(const T &v) {
            g.insert({v, {}});
        }

        //移除一个顶点
        void remove_vertex(const T &v) {
            g.erase(v);
            for (auto &vertex:g)
                vertex.second.erase(v);
        }

        //移除一条边
        void remove_edge(const T &v1, const T &v2) {
            auto iter = g.find(v1);
            if (iter != g.end())
                g[v1].erase(v2);
        }

        //判断有无v1到v2的边
        bool is_connect(const T &v1, const T &v2) {
            auto iter = g.find(v1);
            if (iter == g.end())
                return false;
            return g[v1].find(v2) != g[v1].end();
        }

        //把图打印出来
        void print() const {
            for (auto v:g) {
                std::cout << v.first << " ---> ";
                for (auto e:v.second)
                    std::cout << "(" << e.first << "," << e.second << ")  ";
                std::cout << std::endl;
            }
        }

        //返回图的大小(顶点数)
        size_t size() const {
            return g.size();
        }

        //为了拓扑排序准备的,有更好的实现但是懒得改了
        //获取一个入度为0的点
        std::set<T> get_zero_degree() const {
            std::set<T> s;
            for (auto v:g)
                s.insert(v.first);
            for (auto v:g)
                for (auto p:v.second)
                    s.erase(p.first);
            return s;
        }


        //图算法
    public:
        //拓扑排序
        static std::vector<T> topsort(graph graph);

        /**
         * 无权最短路径(采用队列的广度优先搜索,非递归)
         * @param s 出发的顶点
         * @return 返回一个map,是目标顶点到路径的一个映射
         */
        map<T, std::vector<T>> unweighted(T s);

        //单源有权最短路径算法
        //迪杰斯特拉算法是典型的贪心算法
        //返回值同上
        map<T, std::vector<T>> dijkstra(T s);

        //无向图的最小生成树(prim 算法)
        //和dijkstra算法基本一样
        //返回边的集合 一条边是一个pair<T,T>
        std::multimap<T, T> prim(T s);

        //Kruskal的实现需要并查集,这里暂时没有实现就先不写
        //std::multimap<T,T> kruskal();


        //无向图的dfs(深度有限搜索)递归实现
        //非递归可以用栈来实现
        void undirected_dfs(T s);

        //dfs的内部实现,递归全局变量没有放在成员列表中就在外面套了一层函数
        void dfs(T s, set<T> &visited);

    };

    /**
     * 改善图的数据结构可以改善这个算法
     * 这里就懒得改了qaq
     */
    template<typename T, typename D>
    std::vector<T> graph<T, D>::topsort(graph graph) {
        std::vector<T> v;
        std::set<T> s;
        do {
            s = graph.get_zero_degree();
            for (auto i:s) {
                v.push_back(i);
                graph.remove_vertex(i);
            }
        } while (!s.empty());
        return v;
    }

    //无权的最短路径算法(非递归bfs)
    template<typename T, typename D>
    map<T, std::vector<T>> graph<T, D>::unweighted(T s) {
        std::queue<T> queue;
        map<T, D> distance;
        map<T, std::vector<T>> path;
        for (auto i:g) {
            distance.insert({i.first, INF});
            path.insert({i.first, std::vector<T>()});
        }
        distance[s] = 0;
        queue.push(s);
        while (!queue.empty()) {
            T v = queue.front();
            queue.pop();
            for (auto &i:g) {
                if (is_connect(v, i.first) && distance[i.first] == INF) {
                    distance[i.first] = distance[v] + 1;
                    path[i.first].assign(path[v].begin(), path[v].end());
                    path[i.first].push_back(v);
                    queue.push(i.first);
                }
            }
        }
        return path;
    }

    //这里写的只是演示算法,肯定还有十分多的优化余地
    //因为各种操作都可通过其他诸如堆之类的数据结构来实现以提升效率
    //这里直接使用STL自带的容器&算法以简化过程
    template<typename T, typename D>
    map<T, std::vector<T>> graph<T, D>::dijkstra(T s) {
        map<T, std::vector<T>> path;
        map<T, D> distance;
        map<T, bool> known;
        //初始化距离数组和是否被发现数组
        for (auto i :g) {
            distance.insert({i.first, 65535});
            known.insert({i.first, false});
            path.insert({i.first, std::vector<T>()});
        }
        distance[s] = 0;
        known[s] = true;
        //这里使用一个容器算法来判断是不是到所有的点的路径全部算出来了
        //没有全部算出来的时候 返回 true 循环继续执行
        while (!std::all_of(known.begin(),
                            known.end(),
                            [](std::pair<T, D> p) { return p.second; })) {
            //找到离已知顶点距离最近的点的值
            D min(INF);
            T v, conn;
            //遍历全图
            for (auto &item : g) {
                //对于距离已知的点遍历它所连的边
                if (known[item.first]) {
                    //遍历它所连的边
                    for (auto &i: item.second) {
                        //如果连的边的下一个顶点距离未知
                        if (!known[i.first])
                            if (min > i.second) { //进行距离比较,找到距离最小的点
                                min = i.second;
                                v = i.first;
                                conn = item.first;
                            }
                    }
                }
            }
            //更新找到的点的距离(但不一定是最短的,因为可能有多条边连着这个点)
            known[v] = true;
            distance[v] = distance[conn] + min;
            //连到指定顶点的边可能不止一条,这里要更新距离来找到真正最短的距离
            for (auto &item:g) {
                //如果这个顶点连到了v而且它的距离已知
                if (distance[item.first] != INF && is_connect(item.first, v)) {
                    //计算新的距离
                    D new_dis = item.second[v] + distance[item.first];
                    //如果新的距离比之前的距离更短,就更新距离和直接连接它的节点
                    if (new_dis < min + distance[conn]) {
                        min = item.second[v];
                        distance[v] = new_dis;
                        conn = item.first;
                    }
                }
            }
            //更新路径
            path[v].assign(path[conn].begin(), path[conn].end());
            path[v].push_back(conn);
            min = INF;//重置min
            //进入下一轮查找
        }
        //返回路径信息
        return path;
    }


    /*
     * primer算法,基本原理和上面的dijkstra相同
     */
    template<typename T, typename D>
    std::multimap<T, T> graph<T, D>::prim(T s) {
        std::multimap<T, T> path;
        map<T, bool> known;
        //初始化是否被发现数组
        for (auto &i :g)
            known.insert({i.first, false});
        known[s] = true;
        //这里使用一个容器算法来判断是不是到所有的点的路径全部算出来了
        //没有全部算出来的时候返回 true 循环继续执行
        while (!std::all_of(known.begin(),
                            known.end(),
                            [](std::pair<T, D> p) { return p.second; })) {
            //找到离已知顶点距离最近的点的值
            D min(INF);
            T v, conn;
            //遍历全图位置已知的点
            for (auto i = g.begin(); i != g.end(); ++i) {
                if (known[i->first])
                    //遍历所有连着的点
                    for (auto item :i->second) {
                        if (!known[item.first] && min > item.second) {
                            min = item.second;
                            v = item.first;
                            conn = i->first;
                        }
                    }
            }
            path.insert({conn, v});
            known[v] = true;
        }
        return path;
    }

    template<typename T, typename D>
    void graph<T, D>::undirected_dfs(T s) {
        std::set<T> visited;
        dfs(s, visited);
    }

    template<typename T, typename D>
    void graph<T, D>::dfs(T s, set<T> &visited) {
        visited.insert(s);
        //这里是结果打印,也能用一个变量存起来
        //存入 set 的元素顺序会被打乱因此不能直接遍历set来获取dfs的顺序
        // ,用vector就会减慢查询效率
        std::cout << s << std::endl;
        for (auto &i:g[s])
            if (visited.find(i.first) == visited.end())
                dfs(i.first, visited);
    }


}
#endif //DATASTRUCTURE_GRAPH_H
