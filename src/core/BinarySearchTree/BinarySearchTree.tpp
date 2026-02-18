#pragma once

#include <iostream>

#include "BinarySearchTree.hpp"

template <typename T>
BinarySearchTree<T>::BinarySearchTree(IComparator<T> *comp)
    : comparator(comp), root(NULL), size(0) {}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree(){

};

template <typename T>
IIterator<T> *BinarySearchTree<T>::iterator() const
{
    return new InnerIterator(root);
}

template <typename T>
BinarySearchTree<T>::InnerIterator::InnerIterator(Node *root)
    : current(root)
{
    while (current != NULL)
    {
        stack.push(current);
        current = current->left;
    }
}

template <typename T>
bool BinarySearchTree<T>::InnerIterator::hasNext() const
{
    return !stack.isEmpty();
}

template <typename T>
T BinarySearchTree<T>::InnerIterator::next()
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
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getMinimum(const Node &currentNode) const
{
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getNode(const T &el) const
{
}

template <typename T>
typename BinarySearchTree<T>::Node *BinarySearchTree<T>::getNodeSuccessor(const T &el) const
{
}

template <typename T>
void BinarySearchTree<T>::add(T value)
{
    if (comparator == NULL)
        throw std::runtime_error("Comparator is undefined!");

    Node *currentParent = NULL;
    Node *currentEl = root;

    while (currentEl != NULL)
    {
        currentParent = currentEl;

        int comparison = comparator->compare(value, currentEl->value);
        if (comparison < 0)
            currentEl = currentEl->left;
        else
            currentEl = currentEl->right;
    }

    Node *newNode = new Node(value, NULL, NULL, currentParent);

    if (currentParent == NULL)
        root = newNode;
    else
    {
        int comparison = comparator->compare(value, currentParent->value);
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
    // TODO
}

template <typename T>
void BinarySearchTree<T>::remove(T el)
{
    // TODO
}

template <typename T>
bool BinarySearchTree<T>::contains(T el) const
{
    return false;
}

template <typename T>
int BinarySearchTree<T>::getSize() const
{
    return size;
}