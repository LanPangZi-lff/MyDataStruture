#include <iostream>
#include <list>
#include "binary_search_tree.hpp"
int main(int, char**) 
{
    std::list<int> li({4,8,3,-1,9,2,5,6});
    std::list<int> li2;
    BinarySearchTree<int> tree(li.cbegin(),li.cend());
    tree.erase_iteration(6);
	tree.erase(tree._root_node,-1);
    tree.insert(7);
    std::cout<<tree.find(tree._root_node,7)->_data<<std::endl<<tree.find_iteration(3)->_data<<std::endl;
    li2=tree.preorder_traversal_iteration(); //前序遍历
    std::cout<<"前序遍历的结果为："<<std::endl;
    for(int i:li2)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
}

