#pragma once
#include "MyAllocator.h"
#include <iterator>

template<class T> struct _ListNode
{
    _ListNode<T>* prev;
    _ListNode<T>* next;
    T             data;
};

template<class T> class _ListIterator
{
public:
    using value_type        = T;
    using pointer           = value_type*;
    using reference         = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;

    using Node     = _ListNode<T>;
    using iterator = _ListIterator<T>;

private:
    Node* m_pNode;

public:
    _ListIterator()
        : m_pNode(nullptr)
    {}
    _ListIterator(Node* const m_pNode)
        : m_pNode(m_pNode)
    {}
    _ListIterator(const iterator& other)
        : m_pNode(other.m_pNode)
    {}

    reference operator*() const { return m_pNode->data; }
    reference operator->() const { return m_pNode; }
    bool      operator==(const iterator& other) const { return m_pNode == other.m_pNode; }
    bool      operator!=(const iterator& other) const { return !(*this == other); }
    iterator& operator++()
    {
        m_pNode = m_pNode->next;
        return *this;
    }
    iterator operator++(int)
    {
        Node* tmp = m_pNode;
        m_pNode   = m_pNode->next;
        return tmp;
    }

    iterator& operator--()
    {
        m_pNode = m_pNode->prev;
        return *this;
    }
    iterator operator--(int)
    {
        Node* tmp = m_pNode;
        m_pNode   = m_pNode->prev;
        return tmp;
    }
};

template<class T, class Alloc = MyAllocator<_ListNode<T>>> class MyList
{
public:
    using value_type = T;
    using pointer    = value_type*;
    using reference  = value_type&;

    using Node     = _ListNode<T>;
    using iterator = _ListIterator<T>;

private:
    Node* m_pDummy;

    static pointer allocNode() const { return Alloc::allocate(1); }
    static void    deallocNode(pointer p) const { return Alloc::deallocate(p); }

public:
    MyList() {}
};
