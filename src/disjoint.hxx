#ifndef DISJOINT_HXX_F4SXG1LJ
#define DISJOINT_HXX_F4SXG1LJ

#include <memory>

template <class T>
Disjoint<T>::Disjoint(const T &content)
{
    auto singleton = std::make_unique<Node<T>>();
    singleton->head = singleton.get();
    singleton->content = content;
    singleton->next = nullptr;

    head = std::move(singleton);
    tail = head.get();
}

template <class T>
const T& Disjoint<T>::repr() const
{
    return head->content;
}

#endif /* end of include guard: DISJOINT_HXX_F4SXG1LJ */
