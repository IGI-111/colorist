#ifndef DISJOINT_H_ONOUD6RJ
#define DISJOINT_H_ONOUD6RJ

#include "color.h"
#include "matrix.h"
#include <memory>
#include <vector>
#include <list>

struct Node{
    Node() {}
    Node(const Coord &content) :
        content(content) {}
    Node *head;
    Coord content;
};

class Disjoint : public std::list<Node*>{
    public:
        Disjoint(Node *singleton);
        Disjoint() : std::list<Node*>() {}
        Node *repr();
        std::size_t size() const;

        static void unite(
                std::list<Disjoint>::iterator first,
                std::list<Disjoint>::iterator second,
                std::list<Disjoint> sets,
                ColorMatrix &bitmap);
};

typedef Matrix<std::shared_ptr<Disjoint>> DisjointMatrix;

#endif /* end of include guard: DISJOINT_H_ONOUD6RJ */
