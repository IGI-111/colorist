#ifndef DISJOINT_H_ONOUD6RJ
#define DISJOINT_H_ONOUD6RJ

#include <memory>

template <class T> class Disjoint;

template <class T>
class Node{
    friend class Disjoint<T>;
    public:
        Node() {}
    private:
        Node<T> *head;
        T content;
        std::unique_ptr<Node<T>> next;
};

template <class T>
class Disjoint{
    public:
        Disjoint(const T &content);
        const T& repr() const;
    private:
        std::unique_ptr<Node<T>> head;
        Node<T> *tail;
};

#include "disjoint.hxx"

#endif /* end of include guard: DISJOINT_H_ONOUD6RJ */
