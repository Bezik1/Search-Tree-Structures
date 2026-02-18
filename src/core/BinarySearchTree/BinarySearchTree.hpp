#pragma once

#include <iostream>

#include "../../utils/stacks/Stack/Stack.hpp"

#include "../../interfaces/ITree.hpp"
#include "../../interfaces/IComparator.hpp"
#include "../../interfaces/IIterator.hpp"

template <typename T>
class BinarySearchTree : public ITree<T>
{
public:
    struct Node
    {
        T value;
        Node *left;
        Node *right;
        Node *parent;

        Node(const T &value)
            : value(value), left(NULL), right(NULL), parent(NULL) {};

        Node(const T &value,
             Node *left,
             Node *right,
             Node *parent)
            : value(value),
              left(left),
              right(right),
              parent(parent) {}
    };

    ~BinarySearchTree();

    BinarySearchTree(IComparator<T> *comp = NULL);

    IIterator<T> *iterator() const override;
    void add(T value) override;
    void clear() override;
    void remove(T el) override;

    bool contains(T el) const override;
    int getSize() const override;

private:
    class InnerIterator : public IIterator<T>
    {
    private:
        Stack<Node *> stack;
        Node *current;

    public:
        InnerIterator(Node *root);

        bool hasNext() const override;
        T next() override;
    };

    Node *getMinimum(const Node &currentNode) const;
    Node *getNode(const T &el) const;
    Node *getNodeSuccessor(const T &el) const;

    IComparator<T> *comparator;
    Node *root = NULL;
    int size = 0;
};

#include "BinarySearchTree.tpp"