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
 *   <tr><th>Operation</th><th>Average Time Complexity</th><th>Worst Time Complexity</th></tr>
 *   <tr><td>Addition</td><td>O(log n)</td><td>O(n)</td></tr>
 *   <tr><td>Deletion</td><td>O(log n)</td><td>O(n)</td></tr>
 *   <tr><td>Search</td><td>O(log n)</td><td>O(n)</td></tr>
 * </table>
 *
 * BST represents data by objects of class Node that stores data type T. Node's are
 * internally connected and to go deeper inside tree, we use IComparator object, to
 * easily determine the position of desired Node.
 *
 * @note In BST order of inserting elements matters and it influence the performance of
 * operations on it. It is happening, because BST may degenerate to the form of link list,
 * if order of elements is inefficient. To get familiar with implementation that resolve
 * this problem, see RedBlackTree.
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
     * @return IIterator<T>* - iterator.
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
     * with the root as the argument to activate it.
     *
     * @see getMinimumNode
     * @see IComparator
     *
     * @return T - minimum element.
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
     * with the root as the argument to activate it.
     *
     * @see getMaximumNode
     * @see IComparator
     *
     * @return T - maximum element.
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

    /**
     * @brief Clears the tree from all the elements.
     *
     * @details Clears the tree, by using {@link #deleteSubtree} on root. It
     * additionally nullifies the pointer to the {@link #root}.
     *
     * @see deleteSubtree
     * @see root
     *
     */
    void clear() override;

    /**
     * @brief Removes the node from the BST and free's the occupied memory.
     *
     * @details Removal process depends on three scenarios:
     * 1. Node does not have a left child;
     * 2. Node does not have a right child;
     * 3. Node has both children;
     *
     * In such cases, we perform following actions:
     * 1. We {@link #transplant} node with it's right child;
     * 2. We {@link #transplant} node with it's left child;
     * 3. We find the successor of the node and {@link #transplant} node
     * with it. The successor is selected using {@link #getNodeSuccessor}
     *
     * @see transplant
     * @see getNodeSuccessor
     *
     * @param el - reference to the desired element's value.
     */
    void remove(const T &el) override;

    /**
     * @brief Searches the BST to find if el is in the tree.
     *
     * @details To achievie it, BST uses it's core principles and IComparator
     * to compare the values of nodes in the tree to find the desired value.
     * This fact allows BST for average search time of O(log n).
     *
     * In fact this method invoke private method {@link #getNode} and compare, if
     * the result of it is null pointer or not. In such a way mentioned mechanic is being
     * used.
     *
     * @param el - value of searched element
     *
     * @see getNode
     *
     * @return true.
     * @return false.
     */
    bool contains(T el) const override;

    /**
     * @brief Returns the string representation of the tree.
     *
     * @details The string is build in the following format:
     *
     * ```
     * |--> [root]
     *         |--> [left subtree]
     *         |--> [right subtree]
     * ```
     *
     * @note In case of empty tree return string is just: {@link #EMPTY_TREE_MESSAGE}
     *
     * @return std::string - string representation of the tree.
     */
    std::string toString() const override;

    int getSize() const override;

private:
    static const std::string EMPTY_TREE_MESSAGE;

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
         * @brief Returns next object in order of insertion of BinarySearchTree.
         *
         * @details Returns the next value of object stored in the stack and
         * updates the Stack, with the leftmost children of right child of returned
         * Node.
         *
         * @return T - next element.
         */
        T next() override;
    };

    /**
     * @brief Delete and free the memory from the node and it's children.
     *
     * @details It is done by recursively calling and resolving the memory
     * of the children of the node with decreasing the size of the collection
     * and resolving the memory of current node.
     *
     * @param node the node of who's all children and itself will be deleted.
     */
    void deleteSubtree(Node *node);

    /**
     * @brief Transplant desired node with it's children.
     *
     * @details It is enough to swap references and the references of parent
     * pointing to it's children. In cases, when node is not the root it is also necessary
     * to swap child parent, with node parent.
     *
     * @param node - desired node.
     * @param child  - it's child.
     */
    void transplant(Node *node, Node *child);

    /**
     * @brief Finds the Node Successor object (e.g the smallest node that is bigger than the choosen one.
     *
     * @details The choice of the successor depends on two scenarious, if node either:
     * 1. Has the right subtree;
     * 2. Has not the right subtree;
     *
     * In such cases, we perform following actions:
     * 1. We return the minimum of the right subtree.
     * 2. We go up the tree via reference to the parent of the current node. We check, whether
     * node is the left child of it's parent and if in fact it is one, then we return it.
     *
     * @param node node for which we choose the successor.
     * @return Node* - successor.
     */
    Node *getNodeSuccessor(const Node *node) const;

    /**
     * @brief Returns the maximum node of the BST.
     *
     * @details It uses the key rule of BST, which is that
     * right child is always greater, than it's parent. One can
     * then observe that the rightmost child must be the maximum.
     *
     * For comparison BinarSearchTree uses {@link #comparator} object that
     * implements IComparator interface.
     *
     * @see getMaximumNode
     * @see IComparator
     *
     * @return T - maximum element.
     */
    Node *getMaximumNode(Node *current) const;

    /**
     * @brief Returns the minmimum node of the BST.
     *
     * @details It uses the key rule of BST, which is that
     * left child is always smaller, than it's parent. One can
     * then observe that the leftmost child must be the minimum.
     *
     * For comparison BinarSearchTree uses {@link #comparator} object that
     * implements IComparator interface.
     *
     *
     * @see getMinimumNode
     * @see IComparator
     *
     * @return T - minimum element.
     */
    Node *getMinimumNode(Node *current) const;

    /**
     * @brief Searches the BST to find if node is in the tree.
     *
     * @details To achievie it, BST uses it's core principles and IComparator
     * to compare the values of nodes in the tree to find the desired value.
     * This fact allows BST for average search time of O(log n).
     *
     * @param el - value of searched element
     *
     * @return Node* - pointer to desired Node.
     */
    Node *getNode(const T &el) const;

    /**
     * @brief Prints the current node of the tree and recursevily call this function on the level below.
     *
     * @param node - current node to print
     * @param level - current level of the tree
     *
     * @return std::string - string representation of current node
     */
    std::string toStringRecursive(const Node *node, int level) const;

    IComparator<T> *comparator;
    Node *root = NULL;
    int size = 0;
};

#include "BinarySearchTree.tpp"