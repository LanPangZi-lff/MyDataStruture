#pragma once
#include <iostream>
#include <list>
#include <stack>

template<typename T>
class BinaryTreeNode
{
public:
    BinaryTreeNode<T>* _left_child=nullptr;
    T _data;
    BinaryTreeNode<T>* _right_child=nullptr;
};

template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree<T>(){}
    template<typename Iterator>
    BinarySearchTree<T>(Iterator begin,const Iterator end); //创建二叉搜索树
    size_t size(){return _length;}
    void insert(T value) //插入元素
    {
        _root_node=insert(_root_node,value);
        _length++;
    }
    BinaryTreeNode<T>* find(BinaryTreeNode<T>* node,T value); //递归的方法查找
    BinaryTreeNode<T>* find_iteration(T value); //迭代的方法查找

    BinaryTreeNode<T>* erase(BinaryTreeNode<T>* node,T value); //递归的方法删除
    void erase_iteration(T value); //迭代的方法删除

    std::list<T> preorder_traversal_iteration(); //前序遍历
    BinaryTreeNode<T>* _root_node=nullptr; //二叉搜索树的根节点
private:
    
    size_t _length=0; //二叉搜索树节点个数
    BinaryTreeNode<T>* insert(BinaryTreeNode<T>* root,T value);
};

template<typename T>
template<typename Iterator>
BinarySearchTree<T>::BinarySearchTree(Iterator begin,const Iterator end)
{
    while(begin!=end)
    {
        insert(*begin);
        begin++;
    }
}

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::insert(BinaryTreeNode<T>* root,T value)
{
    if(root==nullptr)
    {
        BinaryTreeNode<T>* node=new BinaryTreeNode<T>;
        node->_data=value;
        return node;
    }
    if(root->_data>value)
    {
        root->_left_child=insert(root->_left_child,value);
    }
    else
    {
        root->_right_child=insert(root->_right_child,value);
    }
    return root;
}

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::find(BinaryTreeNode<T>* node,T value)
{
    if(node==nullptr)
        return nullptr;
    if(node->_data==value)
    {
        return node;
    }
    else if(node->_data>value)
    {
        return find(node->_left_child,value);
    }
    else
    {
        return find(node->_right_child,value);
    }
    return nullptr;
}

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::find_iteration(T value)
{
    BinaryTreeNode<T>* node=_root_node;
    while(node!=nullptr)
    {
        if(node->_data==value)
        {
            return node;
        }
        else if(node->_data>value)
        {
            node=node->_left_child;
        }
        else
        {
            node=node->_right_child;
        }
    }
    return node;
}

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::erase(BinaryTreeNode<T>* node,T value)
{
    if(node==nullptr)
        return nullptr;
    if(node->_data>value) //在左子树中查找
    {
        node->_left_child=erase(node->_left_child,value);
    }
    else if(node->_data<value) //在右子树中查找
    {
        node->_right_child=erase(node->_right_child,value);
    }
    else //找到了要删除的节点
    {
        if(node->_left_child==nullptr) //没有左子节点
        {
            BinaryTreeNode<T>* temp=node->_right_child;
            delete node;
            _length--;
            return temp;
        }
        else if(node->_right_child==nullptr) //没有右子节点
        {
            BinaryTreeNode<T>* temp=node->_left_child;
            delete node;
            _length--;
            return temp;
        }
        else //左右子节点都有
        {
            BinaryTreeNode<T>* temp=node->_right_child;
            while(temp->_left_child!=nullptr) 
            {
                temp=temp->_left_child; //找到右子树中最小的那个节点
            }
            node->_data=temp->_data;
            node->_right_child=erase(node->_right_child,temp->_data);
        }
    }
    return node;
}

template<typename T>
void BinarySearchTree<T>::erase_iteration(T value)
{
    BinaryTreeNode<T>* node=_root_node;
    BinaryTreeNode<T>* parent_node=node; //父节点
    while(node!=nullptr)
    {
        if(node->_data==value)
        {
            if(node->_left_child==nullptr&&node->_right_child==nullptr) //删除的节点没有子节点
            {
                if(parent_node->_left_child!=nullptr)
                {
                    if(parent_node->_left_child->_data==node->_data)
                        parent_node->_left_child=nullptr;
                }
                else
                {
                    parent_node->_right_child=nullptr;
                }
                delete node;
                node=nullptr;
            }
            else if(node->_left_child!=nullptr&&node->_right_child==nullptr) //只有一个子节点，直接替换掉
            {
                BinaryTreeNode<T>* temp=node->_left_child;
                node->_data=temp->_data;
                node->_left_child=temp->_left_child;
                node->_right_child=temp->_right_child;
                delete temp;
            }
            else if(node->_left_child==nullptr&&node->_right_child!=nullptr) //只有一个子节点，直接替换掉
            {
                BinaryTreeNode<T>* temp=node->_right_child;
                node->_data=temp->_data;
                node->_left_child=temp->_left_child;
                node->_right_child=temp->_right_child;
                delete temp;   
            }
            else //有两个子节点
            {
                BinaryTreeNode<T>* temp=node->_right_child;
                if(temp->_left_child==nullptr) //选择右子节点进行替换
                {
                    node->_right_child=temp->_right_child;
                    node->_data=temp->_data;
                    delete temp;
                }
                else
                {
                    while(temp->_left_child!=nullptr) 
                    {
                        parent_node=temp;
                        temp=temp->_left_child; //找到右子树中最小的那个节点
                    }
                    node->_data=temp->_data;
                    parent_node->_left_child=temp->_right_child;
                    delete temp;
                }

            }
            _length--;
        }
        else if(node->_data>value)
        {
            parent_node=node;
            node=node->_left_child;
        }
        else
        {
            parent_node=node;
            node=node->_right_child;
        }
    }
}

template<typename T>
std::list<T> BinarySearchTree<T>::preorder_traversal_iteration()
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