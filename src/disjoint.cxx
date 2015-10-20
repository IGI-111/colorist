#include "disjoint.h"
#include <memory>
#include <iostream>

Disjoint::Disjoint(Node *singleton)
{
    push_back(singleton);
    front()->parent = this;
}

Node *Disjoint::repr()
{
    return front();
}

std::size_t Disjoint::size() const
{
    return std::list<Node*>::size(); // should be O(1) since c++11
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

    // move all elements from second at the end of first
    first->splice(first->end(), *second);
}
