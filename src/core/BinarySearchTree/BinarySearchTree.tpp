#pragma once

#include <iostream>

#include "BinarySearchTree.hpp"

template <typename T>
const std::string BinarySearchTree<T>::EMPTY_TREE_MESSAGE = "Empty Tree";

template <typename T>
BinarySearchTree<T>::BinarySearchTree(IComparator<T> *comp)
    : comparator(comp), root(NULL), size(0) {}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    deleteSubtree(root);
    root = NULL;
    size = 0;
};

template <typename T>
IIterator<T> *BinarySearchTree<T>::iterator() const
{
    return new Iterator(root);
}

template <typename T>
BinarySearchTree<T>::Iterator::Iterator(Node *root)
    : current(root)
{
    while (current != NULL)
    {
        stack.push(current);
        current = current->left;
    }
}

template <typename T>
bool BinarySearchTree<T>::Iterator::hasNext() const
{
    return !stack.isEmpty();
}

template <typename T>
T BinarySearchTree<T>::Iterator::next()
{
    if (!hasNext())
        throw std::runtime_error("No more elements in the tree!");

    Node *node = stack.pop();
    T result = node->value;

    if (node->right != NULL)
    {
        Node *temp = node->right;
        while (temp != NULL)
        {
            stack.push(temp);
            temp = temp->left;
        }
    }

    return result;
}

template <typename T>
std::string BinarySearchTree<T>::toString() const
{
    if (!root)
        return EMPTY_TREE_MESSAGE;
    return toStringRecursive(root, 0);
}

template <typename T>
std::string BinarySearchTree<T>::toStringRecursive(const Node *node, int level) const
{
    if (!node)
        return "";

    std::string result;

    for (int i = 0; i < level; ++i)
        result += "\t";

    result += "|--> " + std::to_string(node->value) + "\n";

    result += toStringRecursive(node->left, level + 1);
    result += toStringRecursive(node->right, level + 1);

    return result;
}

template <typename T>
void BinarySearchTree<T>::deleteSubtree(Node *node)
{
    if (!node)
        return;

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    size--;
    delete node;
}

template <typename T>
void BinarySearchTree<T>::transplant(Node *node, Node *child)
{
    if (node->parent == NULL)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    if (child != NULL)
        child->parent = node->parent;
}

template <typename T>
T BinarySearchTree<T>::maximum()
{
    return getMaximumNode(root)->value;
}

template <typename T>
T BinarySearchTree<T>::minimum()
{
    return getMinimumNode(root)->value;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getMinimumNode(Node *current) const
{
    if (!current)
        return NULL;

    Node *temp = current;

    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getMaximumNode(Node *current) const
{
    if (!current)
        return NULL;

    Node *temp = current;

    while (temp->right != NULL)
        temp = temp->right;
    return temp;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getNode(const T &el) const
{
    Node *current = root;

    while (current != NULL)
    {
        int comparison = comparator->compare(el, current->value);

        if (comparison == 0)
            return current;
        else if (comparison < 0)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getNodeSuccessor(const Node *node) const
{
    if (node == NULL)
        return NULL;

    if (node->right != NULL)
        return getMinimumNode(node->right);

    Node *parent = node->parent;

    while (parent != NULL && node == parent->right)
    {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

template <typename T>
void BinarySearchTree<T>::add(const T &el)
{
    if (comparator == NULL)
        throw std::runtime_error("Comparator is undefined!");

    Node *currentParent = NULL;
    Node *currentEl = root;

    while (currentEl != NULL)
    {
        currentParent = currentEl;

        int comparison = comparator->compare(el, currentEl->value);
        if (comparison < 0)
            currentEl = currentEl->left;
        else
            currentEl = currentEl->right;
    }

    Node *newNode = new Node(el, NULL, NULL, currentParent);

    if (currentParent == NULL)
        root = newNode;
    else
    {
        int comparison = comparator->compare(el, currentParent->value);
        if (comparison < 0)
            currentParent->left = newNode;
        else
            currentParent->right = newNode;
    }

    size++;
}

template <typename T>
void BinarySearchTree<T>::clear()
{
    deleteSubtree(root);
    root = NULL;
    size = 0;
}

template <typename T>
void BinarySearchTree<T>::remove(const T &el)
{
    Node *node = getNode(el);
    if (!node)
        return;

    if (!node->left)
        transplant(node, node->right);
    else if (!node->right)
        transplant(node, node->left);
    else
    {
        Node *successor = getNodeSuccessor(node);
        if (successor->parent != node)
        {
            transplant(successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        transplant(node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
    }
    delete node;
    size--;
}

template <typename T>
bool BinarySearchTree<T>::contains(const T &el) const
{
    return getNode(el) != NULL;
}

template <typename T>
int BinarySearchTree<T>::getSize() const
{
    return size;
}