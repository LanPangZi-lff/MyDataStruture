#pragma once
#include <iostream>

template<typename T>
class DoubleNode
{
public:
    DoubleNode<T>* _last=nullptr;
    T _data;
    DoubleNode<T>* _next=nullptr;
};

template<typename T>
class DoubleLinkedList
{
public:
    DoubleLinkedList<T>();
    void printf_list();
    void insert_head(T data); //头插法
    void insert_tail(T data); //尾插法
    void insert(size_t index,T data); //任意位置插入元素
    void erase(size_t index); //删除任意位置的元素
    void alter(size_t index,T data);
    T get_elem(size_t index);//得到指定位置的元素
    int find_elem(T data);//查找数据在链表中的位置

    size_t size()
    {
        return _length;
    }
    class iterator
    {
    public:
        DoubleNode<T>* _node=nullptr;
        DoubleLinkedList<T>* _list=nullptr; //用来记录迭代器是由谁创建的，确保双向链表类对象用自己的迭代器
    public:
        iterator(DoubleLinkedList<T>* list):_list(list){}
        iterator(DoubleLinkedList<T>* list,DoubleNode<T>* node):_list(list),_node(node){}
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
            iterator it(_list,_node);
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
            return _node == it._node&&_list==it._list;
        }

        const bool operator!=(const iterator& it) const
        {
            return _node != it._node||_list!=it._list;
        }

        T& operator*()
        {
            return _node->_data;
        }
    };

    class reverse_iterator
    {
    public:
        DoubleNode<T>* _node;
    public:
        reverse_iterator(){}
        reverse_iterator(DoubleNode<T>* node):_node(node){}
        reverse_iterator operator++() //先增加后返回
        {
            if(_node!=nullptr)
            {
                _node=_node->_last;
            }
            else
            {
                throw std::runtime_error("Out of range.");
            }
            return *this;
        }
        reverse_iterator operator++(int) //先返回，后增加
        {
            iterator it(_node); //复制一份迭代器对象，用于返回
            if (_node != nullptr)
            {
                _node = _node->_last;
            }
            else
            {
                throw std::runtime_error("Out of range.");
            }
            return it;
        }
        const bool operator==(const reverse_iterator& it) const
        {
            return it->_node==_node;
        }
        const bool operator!=(const reverse_iterator& it) const
        {
            return it->_node!=_node;
        }
        T& operator*()
        {
            return _node->_data;
        }
    };

    void insert(DoubleLinkedList<T>::iterator& it,T data);
    void erase(DoubleLinkedList<T>::iterator& it);
    void alter(DoubleLinkedList<T>::iterator& it,T data);
    T get_elem(DoubleLinkedList<T>::iterator& it);

    iterator begin()
    {
        return iterator(this,_head_pointer->_next);
    }
    iterator end()
    {
        return iterator(this,_tail_pointer->_next);
    }
private:
    size_t _length;
    DoubleNode<T> _head_node;//头结点
    DoubleNode<T>* _head_pointer;//头指针
    DoubleNode<T>* _tail_pointer;//尾指针
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList<T>()
{
    _head_pointer=&_head_node;
    _tail_pointer=_head_pointer;
    _length=0;
}

template<typename T>
void DoubleLinkedList<T>::printf_list()
{
    if(_length==0)
    {
        std::cout<<"list is empty"<<std::endl;
        return;
    }
    DoubleNode<T>* temp=_head_pointer;
    for(int i=0;i<_length-1;i++)
    {
        std::cout<<temp->_next->_data<<",";
        temp=temp->_next;
    }
    std::cout<<temp->_next->_data<<std::endl;

}

template<typename T>
void DoubleLinkedList<T>::insert_head(T data)
{
    DoubleNode<T>* node=new DoubleNode<T>;//创建一个指向节点的指针
    node->_data=data;
    node->_next=_head_pointer->_next;
    if(node->_next==nullptr) //插入的是第一个节点
    {
        _tail_pointer=node; //让尾指针始终指向尾节点
    }
    else
    {
        node->_next->_last=node; //让第一个节点的前指针指向创建的新节点
    }
    _head_pointer->_next=node;
    node->_last=_head_pointer;
    _length++;
}

template<typename T>
void DoubleLinkedList<T>::insert_tail(T data)
{
    DoubleNode<T>* node=new DoubleNode<T>;
    node->_data=data;
    node->_last=_tail_pointer;
    _tail_pointer->_next=node;
    _tail_pointer=node;
    _length++;
}

template<typename T>
void DoubleLinkedList<T>::insert(size_t index,T data)
{
    if(index>_length)
    {
        std::cout<<"List out of range"<<std::endl;
        return;
    }
    if(index==_length)
    {
        insert_tail(data);
        return;
    }
    DoubleNode<T>* node=new DoubleNode<T>;
    node->_data=data;
    DoubleNode<T>* temp=_head_pointer;
    while(index--) //通过遍历使得临时指针指向所要插入位置节点的上一个节点
    {
        temp=temp->_next;
    }
    node->_next=temp->_next;
    temp->_next->_last=node;
    node->_last=temp;
    temp->_next=node;
    _length++;
}

template<typename T>
void DoubleLinkedList<T>::erase(size_t index)
{
    if(index>_length-1)
    {
        std::cout<<"List out of range"<<std::endl;
        return;
    }
    if(index==_length-1)
    {
        DoubleNode<T>* t=_tail_pointer;
        _tail_pointer->_last->_next=nullptr;
        _tail_pointer=_tail_pointer->_last;
        delete t;
        _length--;
        return;
    }
    if(2*index<_length-2) //更加靠近头部，所以从前往后遍历
    {
        DoubleNode<T>* temp=_head_pointer;
        while(index--) //通过遍历使得临时指针指向所要删除位置节点的上一个节点
        {
            temp=temp->_next;
        }
        DoubleNode<T>* t=temp->_next;
        temp->_next->_next->_last=temp;
        temp->_next=temp->_next->_next;
        delete t;
        _length--;
        return;
    }
    else //从后往前遍历
    {
        DoubleNode<T>* temp=_tail_pointer;
        for(int i=0;i<_length-2-index;i++) //通过遍历使得临时指针指向所要删除位置节点的下一个节点
        {
            temp=temp->_last;
        }
        DoubleNode<T>* t=temp->_last;
        temp->_last->_last->_next=temp;
        temp->_last=temp->_last->_last;
        delete t;
        _length--;
        return;
    }   
}

template<typename T>
void DoubleLinkedList<T>::alter(size_t index,T data)
{
    if(index>_length-1)
    {
        std::cout<<"List out of range"<<std::endl;
        return;
    }
    if(index==_length-1)
    {
        _tail_pointer->_data=data;
        return;
    }
    if(2*index<_length-2) //更加靠近头部，所以从前往后遍历
    {
        DoubleNode<T>* temp=_head_pointer;
        while(index--) //通过遍历使得临时指针指向所要改变位置节点的上一个节点
        {
            temp=temp->_next;
        }
        temp->_next->_data=data;
        return;
    }
    else //从后往前遍历
    {
        DoubleNode<T>* temp=_tail_pointer;
        for(int i=0;i<_length-2-index;i++) //通过遍历使得临时指针指向所要改变位置节点的下一个节点
        {
            temp=temp->_last;
        }
        temp->_last->_data=data;
        return;
    } 
}

template<typename T>
T DoubleLinkedList<T>::get_elem(size_t index)
{
    if(index>_length-1)
    {
        std::cout<<"List out of range"<<std::endl;
        throw std::runtime_error("Out of range.");
    }
    if(index==_length-1)
    {
        return _tail_pointer->_data;
    }
    if(2*index<_length-2) //更加靠近头部，所以从前往后遍历
    {
        DoubleNode<T>* temp=_head_pointer;
        while(index--) //通过遍历使得临时指针指向所要改变位置节点的上一个节点
        {
            temp=temp->_next;
        }
        return temp->_next->_data;
    }
    else //从后往前遍历
    {
        DoubleNode<T>* temp=_tail_pointer;
        for(int i=0;i<_length-2-index;i++) //通过遍历使得临时指针指向所要改变位置节点的下一个节点
        {
            temp=temp->_last;
        }
        return temp->_last->_data;
    } 
}

template<typename T>
int DoubleLinkedList<T>::find_elem(T data)
{
    DoubleNode<T>* temp=_head_pointer;
    for(int i=0;i<_length;i++)
    {
        if(temp->_next->_data==data)
        {
            return i;
        }
        temp=temp->_next;
    }
    return -1;
}

template<typename T>
void DoubleLinkedList<T>::insert(DoubleLinkedList<T>::iterator& it,T data)
{
    if(it._list!=this)
    {
        return;
    }
    DoubleNode<T>* node=new DoubleNode<T>;
    DoubleNode<T>* temp=it._node;
    node->_data=data;
    node->_next=temp;
    node->_last=temp->_last;
    temp->_last->_next=node;
    temp->_last=node;
    it._node=node;
    _length++;
}

template<typename T>
void DoubleLinkedList<T>::erase(DoubleLinkedList<T>::iterator& it)
{
    if(it._list!=this)
    {
        return;
    }
    DoubleNode<T>* temp=it._node;
    if(temp->_next==nullptr)
    {
        temp->_last->_next=nullptr;
        it._node=temp->_last;
        _tail_pointer=it._node;
        delete temp;
        _length--;
        return;
    }
    temp->_last->_next=temp->_next;
    temp->_next->_last=temp->_last;
    it._node=temp->_last;
    delete temp;
    _length--; 
}

template<typename T>
void DoubleLinkedList<T>::alter(DoubleLinkedList<T>::iterator& it,T data)
{
    if(it._list!=this)
    {
        return;
    }
    *it=data;
}

template<typename T>
T DoubleLinkedList<T>::get_elem(DoubleLinkedList<T>::iterator& it)
{
    if(it._list!=this)
    {
        throw std::runtime_error("Out of range.");
    }
    return *it;
}