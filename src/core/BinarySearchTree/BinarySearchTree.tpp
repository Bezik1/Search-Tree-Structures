#pragma once

#include <iostream>
#include <memory>

#include "BinarySearchTree.hpp"

template <typename T>
const std::string BinarySearchTree<T>::EMPTY_TREE_MESSAGE = "Empty Tree";

template <typename T>
BinarySearchTree<T>::BinarySearchTree(IComparator<T> *comp)
    : comparator(comp), root(nullptr), size(0) {}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    deleteSubtree(root);
    root = nullptr;
    size = 0;
};

template <typename T>
std::unique_ptr<IIterator<T>> BinarySearchTree<T>::iterator() const
{
    return std::make_unique<Iterator>(root);
}

template <typename T>
BinarySearchTree<T>::Iterator::Iterator(Node *root)
    : current(root)
{
    while (current != nullptr)
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

    if (node->right != nullptr)
    {
        Node *temp = node->right;
        while (temp != nullptr)
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
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    if (child != nullptr)
        child->parent = node->parent;
}

template <typename T>
T BinarySearchTree<T>::maximum()
{
    Node *node = getMaximumNode(root);
    if (!node)
        throw std::runtime_error("Tree is empty");
    return node->value;
}

template <typename T>
T BinarySearchTree<T>::minimum()
{
    Node *node = getMinimumNode(root);
    if (!node)
        throw std::runtime_error("Tree is empty");
    return node->value;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getMinimumNode(Node *current) const
{
    if (!current)
        return nullptr;

    Node *temp = current;

    while (temp->left != nullptr)
        temp = temp->left;
    return temp;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getMaximumNode(Node *current) const
{
    if (!current)
        return nullptr;

    Node *temp = current;

    while (temp->right != nullptr)
        temp = temp->right;
    return temp;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getNode(const T &el) const
{
    Node *current = root;

    while (current != nullptr)
    {
        int comparison = comparator->compare(el, current->value);

        if (comparison == 0)
            return current;
        else if (comparison < 0)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getNodeSuccessor(const Node *node) const
{
    if (node == nullptr)
        return nullptr;

    if (node->right != nullptr)
        return getMinimumNode(node->right);

    Node *parent = node->parent;

    while (parent != nullptr && node == parent->right)
    {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

template <typename T>
void BinarySearchTree<T>::add(const T &el)
{
    if (comparator == nullptr)
        throw std::runtime_error("Comparator is undefined!");

    Node *currentParent = nullptr;
    Node *currentEl = root;

    while (currentEl != nullptr)
    {
        currentParent = currentEl;

        int comparison = comparator->compare(el, currentEl->value);
        if (comparison < 0)
            currentEl = currentEl->left;
        else
            currentEl = currentEl->right;
    }

    Node *newNode = new Node(el, nullptr, nullptr, currentParent);

    if (currentParent == nullptr)
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
    root = nullptr;
    size = 0;
}

template <typename T>
void BinarySearchTree<T>::remove(const T &el)
{
    Node *node = getNode(el);

    if (node == nullptr)
        throw std::runtime_error("Didn't find desired node!");

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
    return getNode(el) != nullptr;
}

template <typename T>
int BinarySearchTree<T>::getSize() const
{
    return size;
}