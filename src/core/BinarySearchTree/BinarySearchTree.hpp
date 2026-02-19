#pragma once

#include <iostream>

#include "../../utils/stacks/Stack/Stack.hpp"

#include "../../interfaces/ITree.hpp"
#include "../../interfaces/IComparator.hpp"
#include "../../interfaces/IIterator.hpp"

/**
 * @brief Dynamic simple binary search tree implementation of interface ITree.
 *
 * @details BST's are sorted binary tree's, in which each node follows the rule that:
 * - left child, should be lesser than it's parent;
 * - right child, should be greater than it's parent;
 *
 * This fact allows BST for quick data access, removal and addition time. To be specific it
 * operates at O(log n) logarithmic time.
 *
 *
 * <table>
 *   <tr><th>Operation</th><th>Time complexity</th></tr>
 *   <tr><td>Addition</td><td>O(log n)</td></tr>
 *   <tr><td>Deletion</td><td>O(log n)</td></tr>
 *   <tr><td>Search</td><td>O(log n)</td></tr>
 * </table>
 *
 * BST represents data by objects of class Node that stores data type T. Node's are
 * internally connected and to go deeper inside tree, we use IComparator object, to
 * easily determine the position of desired Node.
 *
 * @note In BST order of inserting elements matters and it influence the performance of
 * operations on it. It is happening, because BST may degenerate to the form of link list,
 * if order of elements is inefficient.
 *
 * @see ITree
 * @see IComparator
 * @see IIterator
 *
 * @tparam T - represents type of stored data.
 *
 * @author Mateusz Adamowicz
 */
template <typename T>
class BinarySearchTree : public ITree<T>
{
public:
    /**
     * @brief It's the basic building block of BinarySearchTree.
     *
     * @details Nodes store informations in BST. They are internally connected, via
     * pointers to {@link #left}, {@link #right} and {@link #parent}. Left child of the node is smaller than it's parent
     * and right child is greater than the given node.
     *
     * This implementation represents Nodes as a struct, because I didn't see the purpose in creating
     * the implementation of additional functions inside Node that would be present in class representation.
     *
     *
     */
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