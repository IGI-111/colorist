#ifndef DISJOINT_H_ONOUD6RJ
#define DISJOINT_H_ONOUD6RJ

#include "color.h"
#include "matrix.h"
#include <memory>
#include <vector>
#include <list>

class Disjoint;

struct Node{
    Node() {}
    Node(const Color &content) :
        content(content) {}
    Disjoint *parent;
    Color content;
};

class Disjoint : public std::list<Node*>{
    public:
        Disjoint(Node *singleton);
        Disjoint() : std::list<Node*>() {}
        Node *repr();
        std::size_t size() const;

        static void unite(
                Disjoint *first,
                Disjoint *second);
};

typedef Matrix<std::shared_ptr<Disjoint>> DisjointMatrix;

#endif /* end of include guard: DISJOINT_H_ONOUD6RJ */
