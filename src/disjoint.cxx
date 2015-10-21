#include "disjoint.h"
#include <memory>
#include <iostream>

Disjoint::Disjoint(Node *singleton) :
    length(1)
{
    push_front(singleton);
    front()->parent = this;
}

Node *Disjoint::repr()
{
    return front();
}

std::size_t Disjoint::size() const
{
    return length;
}

void Disjoint::unite(
        Disjoint *first,
        Disjoint *second)
{
    // union on yourself will only bring trouble
    if(first->repr() == second->repr())
        return;

    // redirect head pointers for second
    // and change colors accordingly
    auto newColor = first->repr()->content;
    for(auto node : *second){
        node->parent = first;
        node->content = newColor;
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
