#ifndef DISJOINT_HXX_LUKY53GS
#define DISJOINT_HXX_LUKY53GS

#include "disjoint.h"
#include <memory>
#include <iostream>

template <typename T>
Disjoint<T>::Disjoint(const T &singleton) :
    length(1)
{
    this->emplace_front(this, singleton);
}

template <typename T>
Node<T> *Disjoint<T>::repr()
{
    return &this->front();
}

template <typename T>
std::size_t Disjoint<T>::size() const
{
    return length;
}

template <typename T>
void Disjoint<T>::unite(
        Disjoint<T> *first,
        Disjoint<T> *second)
{
    // union on yourself will only bring trouble
    if(first->repr() == second->repr())
        return;

    if(first->size() < second->size())
        std::swap(first, second);

    // redirect head pointers for second
    // and change colors accordingly
    auto newColor = first->repr()->content;
    for(auto node : *second){
        node.parent = first;
        node.content = newColor;
    }

    // move all elements from second inside the first
    // naive approach is to use a tail pointer
    // but since we don't care about order and insertion is O(1),
    // we can just put them at the beginning
    first->splice_after(first->begin(), *second);

    // update size values
    first->length = first->length + second->length;
    second->length = 0;
}

#endif /* end of include guard: DISJOINT_HXX_LUKY53GS */
