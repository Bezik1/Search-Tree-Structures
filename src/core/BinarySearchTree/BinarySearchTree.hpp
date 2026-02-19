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
 * @see Node
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
     * Node stores pointers to left, right and parent
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

    /**
     * @brief Returns the iterator for BinarySearchTree.
     *
     * @details Iterator usses `InOrderWalk` method of passing the
     * search tree. It returns the reference for the object implementing
     * IIterator interface, in this case it's Iterator private class.
     *
     * @see IIterator
     *
     * @return IIterator<T>* - iterator
     */
    IIterator<T> *iterator() const override;

    /**
     * @brief Returns the miniumum element of the BST.
     *
     * @details It uses the key rule of BST, which is that
     * left child is always smaller, than it's parent. One can
     * then observe that the leftmost child must be the miniumum.
     *
     * For comparison BinarSearchTree uses {@link #comparator} object that
     * implements IComparator interface.
     *
     * The real implementation invoke private {@link #getMinimumNode} method,
     * with the root as the argument to achievie it.
     *
     * @see getMinimumNode
     * @see IComparator
     *
     * @return T - minimum element
     */
    T minimum();

    /**
     * @brief Returns the maximum element of the BST.
     *
     * @details It uses the key rule of BST, which is that
     * right child is always greater, than it's parent. One can
     * then observe that the rightmost child must be the maximum.
     *
     * For comparison BinarSearchTree uses {@link #comparator} object that
     * implements IComparator interface.
     *
     * The real implementation invoke private {@link #getMaximumNode} method,
     * with the root as the argument to achievie it.
     *
     * @see getMaximumNode
     * @see IComparator
     *
     * @return T - maximum element
     */
    T maximum();

    /**
     * @brief Adds new element to the BinarySearchTree, by following the rules
     * of BST.
     *
     * @details Firstly method find the correct place for new Node, with the usage
     * of {@link #comparator}. Next it creates new Node, with the given new value of
     * type T and left and right child as NULL. It checks if the choosen place is root
     * and if it is i fact, then it replace the reference for the root, with reference
     * of the new object. However if it isn't than it sets either left or right children of
     * it's parent as the freshly created object.
     *
     * @see IComparator
     * @see Node
     *
     * @throws std::runtime_error - Comparator is undefined!
     *
     * @param el - reference for the value of new element to create.
     */
    void add(const T &el) override;

    void clear() override;

    void remove(const T &el) override;

    std::string toString() const override;
    bool contains(T el) const override;
    int getSize() const override;

private:
    /**
     * @brief Implementation of IIterator interface for BinarySearchTree.
     *
     * @details This implementation uses `InOrderWalk`, which returnes elements
     * in the tree in the order of their insertion. It did not implement remove
     * optional method, because it would be tricky to implement.
     *
     * In order to return in order elements in InOrderWalk method Iterator,
     * uses Stack of pointers to Node objects. This allows this class to collect
     * all leftmost child of root and then later collect all leftmost child of right
     * children of the returned by {@link #next} method Node.
     *
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
         * @return true
         * @return false
         */
        bool hasNext() const override;

        /**
         * @brief Returns next object in order of insertion of BinarySearchTree.
         *
         * @details Returns the next value of object stored in the stack and
         * updates the Stack, with the leftmost children of right child of returned
         * Node.
         *
         * @return T - next element
         */
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