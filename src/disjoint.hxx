#ifndef DISJOINT_HXX_F4SXG1LJ
#define DISJOINT_HXX_F4SXG1LJ

#include <memory>

template <class T>
Disjoint<T>::Disjoint(const T &content)
{
    auto singleton = std::make_unique<Node>(content);
    singleton->head = singleton.get();
    singleton->next = nullptr;

    head = std::move(singleton);
    tail = head.get();
}

template <class T>
const T& Disjoint<T>::find() const
{
     return head->content;
}

template <class T>
void Disjoint<T>::unite(
        const std::shared_ptr<Disjoint<T>> &first,
        std::shared_ptr<Disjoint<T>> &second)
{
    if(second->find() == first->find()){
        // redirect head pointers for second
        for(Node *i = second->head.get();i != nullptr;i = i->next.get())
            i->head = first->head.get();
        // move toUnite list at the end of this list
        first->tail->next = std::move(second->head);
        // change tail pointer
        first->tail = second->tail;
        // redirect toUnite pointer to this list
        second = first;
    }
}

#endif /* end of include guard: DISJOINT_HXX_F4SXG1LJ */