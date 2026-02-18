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
BinarySearchTree<T>::Node *BinarySearchTree<T>::getMinimum(const Node &currentNode) const
{
}

template <typename T>
BinarySearchTree<T>::Node *BinarySearchTree<T>::getNode(const T &el) const
{
}

template <typename T>
BinarySearchTree<T>::Node *BinarySearchTree<T>::getNodeSuccessor(const T &el) const
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