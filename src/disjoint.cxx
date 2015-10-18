#include "disjoint.h"
#include <memory>

Disjoint::Disjoint(const Coord &content)
{
    auto singleton = std::make_unique<Node>(content);
    singleton->head = singleton.get();
    singleton->next = nullptr;

    head = std::move(singleton);
    tail = head.get();
}

const Coord &Disjoint::find() const
{
    return head->content;
}

std::size_t Disjoint::size() const
{
    std::size_t count(0);
    for(Node *i = head.get();i != nullptr;i = i->next.get())
        ++count;
    return count;
}

void Disjoint::unite(
        const std::shared_ptr<Disjoint> &first,
        std::shared_ptr<Disjoint> &second,
        ColorMatrix &bitmap)
{
    // redirect head pointers for second
    // and change colors accordingly
    auto reprCoord = first->head->content;
    auto newColor = bitmap.at(reprCoord);
    for(Node *i = second->head.get();i != nullptr;i = i->next.get()){
        i->head = first->head.get();
        auto pixelCoord = i->content;
        bitmap.at(pixelCoord) = newColor;
    }
    // move second at the end of first
    first->tail->next = std::move(second->head);
    // change tail pointer
    first->tail = second->tail;
    // redirect second pointer to first
    second = first;
}
