#pragma once

#include "iostream"
#include "IIterator.hpp"

/**
 * @ingroup Interfaces
 *
 * @brief Represents functionalities of searching tree structure.
 *
 * @details Searching trees are being build, with the usage of nodes. Each node
 * has reference to it's parent, left and right children. Tree is using nodes to
 * store designated data in a given order. Trees usually decrease operation time complexity
 * to the logarithmic one.
 *
 * Nodes are splitted into three categories:
 * 1. root - the first node of the tree, with parent as a NULL reference;
 * 2. internal nodes - nodes that have parent, left, right or left and right references;
 * 3. leaf nodes - nodes with nullified left and right references;
 *
 * @see BinarySearchTree
 * @see RedBlackTree
 *
 * @tparam T - represents type of stored data.
 */
template <typename T>
class ITree
{
public:
    virtual ~ITree() = default;

    /**
     * @brief Returns iterator over ITree collection.
     *
     * @details Usually this iterator uses one of three methods of traversing the
     * tree: InOrderWalk, PostOrderWalk, PreOrderWalk.
     *
     * @see <a href="https://www.geeksforgeeks.org/dsa/tree-traversals-inorder-preorder-and-postorder/">Methods of traversing searching tree</a>
     *
     * @note Required method.
     *
     * @return IIterator<T>* iterator.
     */
    virtual IIterator<T> *iterator() const = 0;

    /**
     * @brief Adds new element to the tree.
     *
     * @note Required method.
     *
     * @param el - value of new element.
     */
    virtual void add(const T &el) = 0;

    /**
     * @brief Clears the tree from all elements.
     *
     * @note Required method.
     */
    virtual void clear() = 0;

    /**
     * @brief Removes given element from the tree.
     *
     * @note Required method.
     *
     * @param el - given element.
     */
    virtual void remove(const T &el) = 0;

    /**
     * @brief Gives information about, whether element belongs to the tree or not.
     *
     * @note Required method.
     *
     * @param el given element.
     *
     * @return true
     * @return false
     */
    virtual bool contains(const T &el) const = 0;

    /**
     * @brief Returns the count of all elements in the tree.
     *
     * @note Required method.
     *
     * @return int - count of all elements.
     */
    virtual int getSize() const = 0;

    /**
     * @brief Returns stringified tree.
     *
     * @return std::string
     */
    virtual std::string toString() {};
};