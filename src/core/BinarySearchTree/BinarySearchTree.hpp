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
    T minimum();
    T maximum();
    void add(const T &el) override;
    void clear() override;
    void remove(const T &el) override;

    std::string toString() const override;
    bool contains(T el) const override;
    int getSize() const override;

private:
    class Iterator : public IIterator<T>
    {
    private:
        Stack<Node *> stack;
        Node *current;

    public:
        Iterator(Node *root);

        bool hasNext() const override;
        T next() override;
    };

    static const std::string EMPTY_TREE_MESSAGE;

    void deleteSubtree(Node *node);
    void transplant(Node *node, Node *child);
    Node *getMaximumNode(Node *current) const;
    Node *getMinimumNode(Node *current) const;
    Node *getNode(const T &el) const;
    Node *getNodeSuccessor(const Node *node) const;

    std::string toStringRecursive(const Node *node, int level) const;

    IComparator<T> *comparator;
    Node *root = NULL;
    int size = 0;
};

#include "BinarySearchTree.tpp"