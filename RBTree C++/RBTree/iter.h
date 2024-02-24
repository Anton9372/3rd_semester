#ifndef ITER_H
#define ITER_H

#include "rbtree.h"
#include <iterator>

namespace rbt
{
    template <typename T>
    class ConstRbtIterator
    {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::bidirectional_iterator_tag;
    private:
        typename RBTree<T>::Node* node_;
    public:
        ConstRbtIterator();
        explicit ConstRbtIterator(typename RBTree<T>::Node* node);
        ConstRbtIterator(const ConstRbtIterator& other);
        ~ConstRbtIterator();
        ConstRbtIterator& operator=(const ConstRbtIterator& other);
        ConstRbtIterator& operator++();
        ConstRbtIterator operator++(int);
        ConstRbtIterator& operator--();
        ConstRbtIterator operator--(int);
        bool operator==(const ConstRbtIterator& other) const;
        bool operator!=(const ConstRbtIterator& other) const;
        reference operator*() const;
        pointer operator->() const;
    };

    template <typename T>
    ConstRbtIterator<T>::ConstRbtIterator() : node_(nullptr)
    {

    }

    template <typename T>
    ConstRbtIterator<T>::ConstRbtIterator(typename RBTree<T>::Node* node) : node_(node)
    {

    }

    template <typename T>
    ConstRbtIterator<T>::ConstRbtIterator(const ConstRbtIterator& other) : node_(other.node_)
    {

    }

    template <typename T>
    ConstRbtIterator<T>::~ConstRbtIterator()
    {

    }

    template <typename T>
    ConstRbtIterator<T>& ConstRbtIterator<T>::operator=(const ConstRbtIterator& other)
    {
        if (*this != other)
            this->node_ = other.node_;
        return *this;
    }

    template <typename T>
    ConstRbtIterator<T>& ConstRbtIterator<T>::operator++()
    {
        node_ = node_->next();
        return *this;
    }

    template <typename T>
    ConstRbtIterator<T> ConstRbtIterator<T>::operator++(int)
    {
        ConstRbtIterator temp = *this;
        ++(*this);
        return temp;
    }

    template <typename T>
    ConstRbtIterator<T>& ConstRbtIterator<T>::operator--()
    {
        node_ = node_->prev();
        return *this;
    }

    template <typename T>
    ConstRbtIterator<T> ConstRbtIterator<T>::operator--(int)
    {
        ConstRbtIterator temp = *this;
        --(*this);
        return temp;
    }

    template <typename T>
    bool ConstRbtIterator<T>::operator==(const ConstRbtIterator& other) const
    {
        return node_ == other.node_;
    }

    template <typename T>
    bool ConstRbtIterator<T>::operator!=(const ConstRbtIterator& other) const
    {
        return node_ != other.node_;
    }

    template <typename T>
    const T& ConstRbtIterator<T>::operator*() const
    {
        return node_->val;
    }

    template <typename T>
    const T* ConstRbtIterator<T>::operator->() const
    {
        return &(node_->val);
    }

}


#endif
