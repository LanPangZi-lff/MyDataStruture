#pragma once
#include <iostream>

template<typename T>
class Node
{
public:
    Node<T>(){}
    T _data;
    Node<T>* _next;
};

template<typename T>
class SingleLinkedList
{
public:
    SingleLinkedList();
    ~SingleLinkedList(){};
    void insert_head(T data);//头插法
    void insert_tail(T data);//尾插法
    void insert(size_t index,T data);
    void erase(size_t index);
    void alter(size_t index,T data);
    void list_printf();
    T get_elem(size_t index);//得到指定位置的元素
    int find_elem(T data);//查找数据在链表中的位置
    size_t size()
    {
        return _length;
    }

    class iterator
    {
    private:
        Node<T>* _node = nullptr;

    public:
        iterator(){}

        iterator(Node<T>* node)
        {
            _node = node;
        }
        
        ~iterator(){};

        iterator operator++() //++it,前缀，先增加后返回
        {
            if (_node != nullptr)
            {
                _node = _node->_next;
            }
            else
            {
                throw std::runtime_error("Out of range.");
            }
            return *this;
        }

        iterator operator++(int) //it++，后缀，先返回后增加
        {
            iterator it(_node);
            if (_node != nullptr)
            {
                _node = _node->_next;
            }
            else
            {
                throw std::runtime_error("Out of range.");
            }
            return it;
        }
    
        const bool operator==(const iterator& it) const
        {
            return _node == it._node;
        }

        const bool operator!=(const iterator& it) const
        {
            return _node != it._node;
        }

        T& operator*()
        {
            return _node->_data;
        }
    };
    
    iterator begin()
    {
        return iterator(_head_pointer->_next);
    }

    iterator end()
    {
        return iterator(_tail_pointer->_next);
    }

private:
    size_t _length;//链表的长度
    Node<T> _head_node;//头结点
    Node<T>* _head_pointer;//头指针
    Node<T>* _tail_pointer;//尾指针
};

template<typename T>
SingleLinkedList<T>::SingleLinkedList()
{
    _head_pointer=&_head_node;
    _head_node._next=_head_pointer;
    _tail_pointer=_head_pointer;
    _length=0;
}

template<typename T>
void SingleLinkedList<T>::insert_head(T data)
{
    Node<T>* s=new Node<T>;//创建新节点
    s->_data=data;
    s->_next=_head_pointer->_next;//将新节点的指针域赋值为头结点的指针域
    _head_pointer->_next=s;//将头节点的指针域指向新节点
    if(_length==0)
    {
        _tail_pointer=s;
    }
    _length++;//链表长度加一
}

template<typename T>
void SingleLinkedList<T>::insert_tail(T data)
{
    Node<T>* s=new Node<T>;//创建新节点
    s->_data=data;
    _tail_pointer->_next=s;//尾节点的指针域指向新节点
    _tail_pointer=s;//尾指针指向新的尾节点
    _length++;//链表长度加一
}

template<typename T>
void SingleLinkedList<T>::list_printf()
{
    Node<T>* temp=_head_pointer->_next;
    for(int i=0;i<_length-1;i++)
    {
        std::cout<<temp->_data<<",";
        temp=temp->_next;
    }
    std::cout<<temp->_data<<std::endl;
}

template<typename T>
void SingleLinkedList<T>::insert(size_t index,T data)
{
    if(index==0)
    {
        insert_head(data);
        return;
    }
    if(index==_length)
    {
        insert_tail(data);
        return;
    }  
    if(index>_length)
    {
        throw std::logic_error("Location out of range of list");
        return;
    }
    Node<T>* temp=_head_pointer->_next;//构建指针，指向第0个节点
    Node<T>* s=new Node<T>;//创建新节点
    while(--index)
    {
        temp=temp->_next;
    }
    s->_data=data;
    s->_next=temp->_next;
    temp->_next=s;
    ++_length;
}

template<typename T>
void SingleLinkedList<T>::erase(size_t index)
{
    if(index>_length-1)
    {
        throw std::logic_error("Location out of range of list");
        return;
    }
    Node<T>* temp=_head_pointer;//构建指针，指向头节点
    while(index--)
    {
        temp=temp->_next;
    }
    if(index==_length-1) //如果删除尾节点，那么尾指针需要改变
    {
        _tail_pointer=temp;
    }
    Node<T>* temp2=temp->_next;
    temp->_next=temp->_next->_next;
    _length--;
    delete temp2;
}

template<typename T>
void SingleLinkedList<T>::alter(size_t index,T data)
{
    if(index>_length-1)
    {
        throw std::logic_error("Location out of range of list");
        return;
    }
    Node<T>* temp=_head_pointer;//构建指针，指向头节点
    while(index--)
    {
        temp=temp->_next;
    }
    temp->_next->_data=data;
}

template<typename T>
T SingleLinkedList<T>::get_elem(size_t index)
{
    if(index>_length-1)
    {
        std::cout<<"Location out of range of list"<<std::endl;
        throw std::logic_error("Location out of range of list");
    }
    Node<T>* temp=_head_pointer->_next;
    while(index--)
    {
        temp=temp->_next;
    }
    return temp->_data;
}

template<typename T>
int SingleLinkedList<T>::find_elem(T data)
{
    Node<T>* temp=_head_pointer->_next;
    for(size_t i=0;i<_length;i++)
    {
        if(temp->_data==data)
            return i;
        temp=temp->_next;
    }
    return -1;
}
