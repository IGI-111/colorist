#include "disjoint.h"
#include <memory>
#include <iostream>

Disjoint::Disjoint(Node *singleton)
{
    push_back(singleton);
    front()->head = front();
}

Node *Disjoint::repr()
{
    return front();
}

std::size_t Disjoint::size() const
{
    return std::list<Node*>::size();
}

void Disjoint::unite(
        std::list<Disjoint>::iterator first,
        std::list<Disjoint>::iterator second,
        std::list<Disjoint> sets,
        ColorMatrix &bitmap)
{
    // union on yourself will only bring trouble
    if(first->repr() == second->repr())
        return;

    // redirect head pointers for second
    // and change colors accordingly
    auto reprCoord = first->repr()->content;
    auto newColor = bitmap.at(reprCoord);
    for(auto node : *second){
        node->head = first->front();
        auto pixelCoord = node->content;
        bitmap.at(pixelCoord) = newColor;
    }

    // move all elements from second at the end of first
    first->splice(first->end(), *second);

    // remove second list
    sets.erase(second);
}
