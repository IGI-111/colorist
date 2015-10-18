#ifndef DISJOINT_H_ONOUD6RJ
#define DISJOINT_H_ONOUD6RJ

#include "color.h"
#include "matrix.h"
#include <memory>
#include <vector>

class Disjoint{
    public:
        Disjoint(std::size_t x, std::size_t y) : Disjoint(Coord(x,y)) {}
        Disjoint(const Coord &content);
        const Coord &find() const;
        std::size_t size() const;

        static void unite(
                const std::shared_ptr<Disjoint> &first,
                std::shared_ptr<Disjoint> &second,
                ColorMatrix &bitmap);
    private:
        struct Node{
            Node(const Coord &content) :
                content(content) {}
            Node *head;
            Coord content;
            std::unique_ptr<Node> next;
        };

        std::unique_ptr<Node> head;
        Node *tail;
};

typedef Matrix<std::shared_ptr<Disjoint>> DisjointMatrix;

#endif /* end of include guard: DISJOINT_H_ONOUD6RJ */
