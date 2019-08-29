#include <iostream>
#include "graph.h"
#include <queue>
#include <vector>
#include <set>
int main() {

    std::set<int> s;
    s.insert(12);
    s.insert(32);
    s.insert(44);
    s.insert(-32);
    for (int i : s) {
        std::cout<<i<<"   ";
    }
//    xhy::graph<int> g;
//    g.add_undirected(1,4,3);
//    g.add_undirected(1,3,2);
//    g.add_undirected(4,3,7);
//    g.add_undirected(1,2,9);
//    g.add_undirected(3,2,6);
//    g.add_undirected(2,5,5);
//    g.add_undirected(3,5,4);
//
//    g.undirected_dfs(1);

    return 0;
}