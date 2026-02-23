#pragma once

#include <iostream>

#include "../../utils/stacks/Stack/Stack.hpp"

#include "../../interfaces/IStack.hpp"
#include "../../interfaces/ITree.hpp"
#include "../../interfaces/IIterator.hpp"
#include "../../interfaces/IComparator.hpp"

/**
 * @brief Dynamic and efficient implementation of ITree interface. It uses red and black
 * node categories to optimize the structure to operate in O(log n) strict time.
 *
 * @details Red black tree is the ITree structure with additional color field in Node struct.
 * This fact, also means that there are following rules that touch the topic of nodes color:
 * 1. Each node is either red or black;
 * 2. Root is always black;
 * 3. Red nodes cannot have red children;
 * 4. Every path from a node to its descendant leaves must have the same number of black nodes;
 * 5. All leafs are black.
 *
 * @todo
 * 1. Create a copy constructor;
 * 2. Create copy assignment operator;
 * 3. Implement comparator == NULL, checking where needed;
 *
 * @see ITree
 * @see IComparator
 * @see IIterator
 * @see Node
 *
 * @tparam T
 */
template <typename T>
class RedBlackTree : public ITree<T>
{
public:
    ~RedBlackTree();

    IIterator<T> *iterator() const override;

    T minimum();

    T maximum();

    void add() override;

    void clear() override;

    void remove(const T &el);

    void contains(const T &el);

    std::string toString() const;

    int getSize() const override;

private:
    static const std::string EMPTY_TREE_MESSAGE;

    /**
     * @brief It's the basic building block of RedBlackTree.
     *
     * @details Nodes store information in RedBlackTree. They are internally
     *
     *
     *
     */
    struct Node
    {
        T value;
        bool color;
        Node *left;
        Node *right;
        Node *parent;

        Node(const T &value)
            : value(value), left(NULL), right(NULL), parent(NULL), color(false) {};

        Node(const T &value,
             bool color,
             Node *left,
             Node *right,
             Node *parent)
            : value(value),
              color(color),
              left(left),
              right(right),
              parent(parent) {}
    };

    /**
     * @brief Implementation of IIterator interface for RedBlackTree.
     *
     * @details This implementation uses `InOrderWalk`, which returnes elements
     * in the tree in the sorted order. It did not implement remove
     * optional method, because it would be tricky to implement.
     *
     * In order to return in order elements in InOrderWalk method Iterator,
     * uses Stack of pointers to Node objects. This allows this class to collect
     * all leftmost child of root and then later collect all leftmost child of right
     * children of the returned by {@link #next} method Node.
     *
     * @see Stack
     * @see IIterator
     * @see Node
     *
     */
    class Iterator : public IIterator<T>
    {
    private:
        Stack<Node *> stack;
        Node *current;

    public:
        /**
         * @brief Construct a new Iterator object. It mainly initialize the Stack,
         * with the leftmost children of the root.
         *
         * @param root
         */
        Iterator(Node *root);

        /**
         * @brief Checks, if Stack is empty.
         *
         * @return true.
         * @return false.
         */
        bool hasNext() const override;

        /**
         * @brief Returns next object in sotred order of RedBlackTree.
         *
         * @details Returns the next value of object stored in the stack and
         * updates the Stack, with the leftmost children of right child of returned
         * Node.
         *
         * @return T - next element.
         */
        T next() override;
    };

    void deleteSubtree(Node *node);

    void transplant(Node *node, Node *child);

    Node *getNodeSuccessor(const Node *node) const;

    Node *getMaximumNode(Node *current) const;

    Node *getMinimumNode(Node *current) const;

    Node *getNode(const T &el) const;

    void leftRotate(const Node *node);

    void rightRotate(const Node *node);

    void fixTreeAfterInsertion(const Node *node);

    void fixTreeAfterDeletion(const Node *node);

    std::string
    toStringRecursive(const Node *node, int level) const;

    IComparator<T> *comparator;
    Node *root = NULL;
    int size = 0;
};

#include "RedBlackTree.tpp"