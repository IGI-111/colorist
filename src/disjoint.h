#ifndef DISJOINT_H_ONOUD6RJ
#define DISJOINT_H_ONOUD6RJ

#include "color.h"
#include "matrix.h"
#include <memory>
#include <vector>
#include <forward_list>

class Disjoint;

struct Node{
    Node() {}
    Node(const Color &content) :
        content(content) {}
    Disjoint *parent;
    Color content;
};

class Disjoint : public std::forward_list<Node*>{
    public:
        Disjoint(Node *singleton);
        Disjoint() : std::forward_list<Node*>() {}
        Node *repr();
        std::size_t size() const;

        static void unite(
                Disjoint *first,
                Disjoint *second);
    private:
        std::size_t length;
};

typedef Matrix<std::shared_ptr<Disjoint>> DisjointMatrix;

#endif /* end of include guard: DISJOINT_H_ONOUD6RJ */
