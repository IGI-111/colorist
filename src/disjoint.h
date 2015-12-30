#ifndef DISJOINT_H_ONOUD6RJ
#define DISJOINT_H_ONOUD6RJ

#include <forward_list>

template <typename T> class Disjoint;

template <typename T> struct Node {
  Node() {}
  Node(Disjoint<T> *parent, const T &content)
      : parent(parent), content(content) {}
  Disjoint<T> *parent;
  T content;
};

template <typename T> class Disjoint : private std::forward_list<Node<T>> {
public:
  Disjoint(const T &singleton); // MakeSet()
  Node<T> *repr();              // FindSet()
  std::size_t size() const;

  static void unite(Disjoint *first, Disjoint *second); // Union()
private:
  std::size_t length;
};

#include "disjoint.hxx"

#endif /* end of include guard: DISJOINT_H_ONOUD6RJ */
