//
// Created by agno3 on 8/26/19.
//

#ifndef DATASTRUCTURE_TREE_TOOL_H
#define DATASTRUCTURE_TREE_TOOL_H

#include <iostream>
class tree_tool{
public:
    const static int count = 20;
    template <typename Node>
    static void print2DUtil(Node *root, int space)
    {
        // Base case
        if (root == nullptr)
            return;
        // Increase distance between levels
        space += count;
        // Process right child first
        print2DUtil(root->right, space);
        // Print current node after space
        // count
        std::cout<<std::endl;
        for (int i = count; i < space; i++)
            std::cout<<" ";
        std::cout<<"["<<root->element<<"]\n";
        // Process left child
        print2DUtil(root->left, space);
    }

// Wrapper over print2DUtil()
    template<typename Node>
    static void print2D(Node *root)
    {
        print2DUtil(root, 0);
    }
};

#endif //DATASTRUCTURE_TREE_TOOL_H
