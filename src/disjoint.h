#ifndef DISJOINT_H_ONOUD6RJ
#define DISJOINT_H_ONOUD6RJ

#include <memory>

template <class T>
class Disjoint{
    public:
        Disjoint(const T &content);
        const T& find() const;
        static void unite(
                const std::shared_ptr<Disjoint<T>> &first,
                std::shared_ptr<Disjoint<T>> &second);
    private:
        struct Node{
            Node(const T &content) :
                content(content) {}
            Node *head;
            T content;
            std::unique_ptr<Node> next;
        };

        std::unique_ptr<Node> head;
        Node *tail;
};

#include "disjoint.hxx"

#endif /* end of include guard: DISJOINT_H_ONOUD6RJ */
