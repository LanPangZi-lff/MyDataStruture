#pragma once
#include <iostream>
#include <list>
#include <stack>
#include <queue>

template<typename T>
class BinaryTreeNode
{
public:
    BinaryTreeNode<T>* _left_child=nullptr;
    T _data;
    BinaryTreeNode<T>* _right_child=nullptr;
};

template<typename T>
class BinaryTree
{
public:
    BinaryTree<T>(){}
    void initialize(std::list<T>& values,const T &none)
    {
        _root_node=create_tree(values,none);
    }
    size_t size(){return _length;}
    std::list<T> preorder_traversal(){return preorder_traversal(_root_node);}
    std::list<T> inorder_traversal(){return inorder_traversal(_root_node);}
    std::list<T> postorder_traversal(){return postorder_traversal(_root_node);}
    std::list<T> preorder_traversal_iteration();
    std::list<T> inorder_traversal_iteration();
    std::list<T> postorder_traversal_iteration();
    std::list<T> sequence_traversal_iteration();
private:
    std::list<T> preorder_traversal(BinaryTreeNode<T>* node,std::list<T>& values=std::list<T>()); //前序遍历，中左右
    std::list<T> inorder_traversal(BinaryTreeNode<T>* node,std::list<T>& values=std::list<T>()); //中序遍历，左中右
    std::list<T> postorder_traversal(BinaryTreeNode<T>* node,std::list<T>& values=std::list<T>()); //后序遍历，左右中
    BinaryTreeNode<T>* create_tree(std::list<T>& values,const T &none);
    BinaryTreeNode<T>* _root_node; //二叉树的根节点
    size_t _length=0; //二叉树节点个数
};

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::create_tree(std::list<T>& values,const T &none)
{
    if(values.size()==0)
    {
        return nullptr;
    }
    if(values.front()==none)
    {
        values.pop_front();
        return nullptr;
    }
    BinaryTreeNode<T>* node=new BinaryTreeNode<T>;
    node->_data=values.front();
    _length++;
    values.pop_front();
    node->_left_child=create_tree(values,none);
    node->_right_child=create_tree(values,none);
    return node;
}

template<typename T>
std::list<T> BinaryTree<T>::preorder_traversal(BinaryTreeNode<T>* node,std::list<T>& values)
{
    if(node==nullptr)
    {
        return values;
    }
    values.emplace_back(node->_data);
    preorder_traversal(node->_left_child,values);
    preorder_traversal(node->_right_child,values);
    return values;
}

template<typename T>
std::list<T> BinaryTree<T>::inorder_traversal(BinaryTreeNode<T>* node,std::list<T>& values)
{
    if(node!=nullptr)
    {
        inorder_traversal(node->_left_child,values);
        values.emplace_back(node->_data);
        inorder_traversal(node->_right_child,values);
    }
    return values;
}

template<typename T>
std::list<T> BinaryTree<T>::postorder_traversal(BinaryTreeNode<T>* node,std::list<T>& values)
{
    if(node!=nullptr)
    {
        postorder_traversal(node->_left_child,values);
        postorder_traversal(node->_right_child,values);
        values.emplace_back(node->_data);
    }
    return values;
}

template<typename T>
std::list<T> BinaryTree<T>::preorder_traversal_iteration()
{
    std::list<T> values;
    std::stack<BinaryTreeNode<T>*> mystack;
    mystack.push(_root_node);
    while(!mystack.empty())
    {
        BinaryTreeNode<T>* node=mystack.top();
        mystack.pop();
        values.emplace_back(node->_data);
        if(node->_right_child!=nullptr)
            mystack.push(node->_right_child);
        if(node->_left_child!=nullptr)
            mystack.push(node->_left_child);
    }
    return values;
}

template<typename T>
std::list<T> BinaryTree<T>::inorder_traversal_iteration()
{
    std::list<T> values;
    std::stack<BinaryTreeNode<T>*> mystack;
    BinaryTreeNode<T>* node=_root_node;
    while(!mystack.empty()||node!=nullptr)
    {
        while(node!=nullptr) //寻找最左边的子节点，并把经过的所有节点入栈
        {
            mystack.push(node);
            node=node->_left_child;
        }
        node=mystack.top();
        mystack.pop();
        values.emplace_back(node->_data);
        node=node->_right_child;
    }
    return values;
}

template<typename T>
std::list<T> BinaryTree<T>::postorder_traversal_iteration()
{
    std::list<T> values;
    std::stack<BinaryTreeNode<T>*> mystack;
    BinaryTreeNode<T>* node=_root_node;
    BinaryTreeNode<T>* flag=nullptr; //用来记录访问过的右节点
    while(!mystack.empty()||node!=nullptr)
    {
        while(node!=nullptr) //寻找最左边的子节点，并把经过的所有节点入栈
        {
            mystack.push(node);
            node=node->_left_child;
        }
        node=mystack.top();
        mystack.pop();
        if(node->_right_child==nullptr||flag==node->_right_child) //如果这个节点没有右节点或者右节点已经被访问过，那么才存入其数据
        {
            values.emplace_back(node->_data);
            flag=node;
            node=nullptr;
        }
        else
        {
            mystack.push(node); //如果这个节点还有右节点，那么此节点还不能弹出栈，所以要重新入栈
            node=node->_right_child;
        }
    }
    return values;
}

template<typename T>
std::list<T> BinaryTree<T>::sequence_traversal_iteration()
{
    std::list<T> values;
    std::queue<BinaryTreeNode<T>*> myqueue;
    myqueue.push(_root_node);
    while(!myqueue.empty())
    {
        BinaryTreeNode<T>* node=myqueue.front();
        myqueue.pop();
        values.emplace_back(node->_data);
        if(node->_left_child!=nullptr)
            myqueue.push(node->_left_child);
        if(node->_right_child!=nullptr)
            myqueue.push(node->_right_child);
    }
    return values;
}