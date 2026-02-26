#pragma once

#include <format>
#include <memory>

#include "../../concepts/Comparable.hpp"

#include "RedBlackTree.hpp"

template <Comparable T>
const std::string RedBlackTree<T>::EMPTY_TREE_MESSAGE = "Empty Tree";

template <Comparable T>
RedBlackTree<T>::RedBlackTree() noexcept
{
    NIL = new Node(T(), NodeColor::Black, nullptr, nullptr, nullptr);
    NIL->left = NIL->right = NIL->parent = NIL;

    root = NIL;
    size = 0;
}

template <Comparable T>
RedBlackTree<T>::~RedBlackTree() noexcept
{
    deleteSubtree(root);
    root = nullptr;
    size = 0;

    delete NIL;
}

template <Comparable T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree &other)
{
    NIL = new Node(T(), NodeColor::Black, nullptr, nullptr, nullptr);
    root = copySubtree(other.root, nullptr);
    size = other.size;
}

template <Comparable T>
RedBlackTree<T> &RedBlackTree<T>::operator=(RedBlackTree other)
{
    std::swap(root, other.root);
    std::swap(NIL, other.NIL);
    std::swap(size, other.size);
    return *this;
}

template <Comparable T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::copySubtree(Node *node, Node *parent)
{
    if (node == nullptr || node == NIL)
        return NIL;

    Node *newNode = new Node(node->value, node->color, nullptr, nullptr, parent);
    newNode->left = copySubtree(node->left, newNode);
    newNode->right = copySubtree(node->right, newNode);
    return newNode;
}

template <Comparable T>
RedBlackTree<T>::RedBlackTree(RedBlackTree &&other) noexcept
    : root(other.root), NIL(other.NIL), size(other.size)
{
    other.root = nullptr;
    other.NIL = nullptr;
    other.size = 0;
}

template <Comparable T>
RedBlackTree<T> &RedBlackTree<T>::operator=(RedBlackTree &&other) noexcept
{
    if (this != &other)
    {
        clear();
        delete NIL;
        root = other.root;
        NIL = other.NIL;
        size = other.size;
        other.root = nullptr;
        other.NIL = nullptr;
    }
    return *this;
}

template <Comparable T>
void RedBlackTree<T>::clear()
{
    deleteSubtree(root);
    root = NIL;
    size = 0;
}

template <Comparable T>
std::unique_ptr<IIterator<T>> RedBlackTree<T>::iterator() const noexcept
{
    return std::make_unique<Iterator>(root, NIL);
}

template <Comparable T>
RedBlackTree<T>::Iterator::Iterator(Node *root, Node *nil)
    : current(root), nil(nil)
{
    while (current != nil)
    {
        stack.push(current);
        current = current->left;
    }
}

template <Comparable T>
bool RedBlackTree<T>::Iterator::hasNext() const
{
    return !stack.isEmpty();
}

template <Comparable T>
T RedBlackTree<T>::Iterator::next()
{
    if (!hasNext())
        throw std::runtime_error("No more elements in the tree!");

    Node *node = stack.pop();
    T result = node->value;

    if (node->right != nil)
    {
        Node *temp = node->right;
        while (temp != nil)
        {
            stack.push(temp);
            temp = temp->left;
        }
    }

    return result;
}

template <Comparable T>
std::string RedBlackTree<T>::toString() const
{
    if (root == NIL)
        return EMPTY_TREE_MESSAGE;
    return toStringRecursive(root, 0);
}

template <Comparable T>
std::string RedBlackTree<T>::toStringRecursive(const Node *node, int level) const
{
    if (node == NIL)
        return "";

    std::string result;

    for (int i = 0; i < level; ++i)
        result += "\t";

    result += std::format("|--> {} [{}]\n",
                          node->value,
                          node->color == NodeColor::Black
                              ? "BLACK"
                              : "RED");

    result += toStringRecursive(node->left, level + 1);
    result += toStringRecursive(node->right, level + 1);

    return result;
}

template <Comparable T>
void RedBlackTree<T>::deleteSubtree(Node *node)
{
    if (node == NIL)
        return;

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    size--;
    delete node;
}

template <Comparable T>
void RedBlackTree<T>::transplant(Node *node, Node *child) noexcept
{
    if (node->parent == NIL)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    if (child != NIL)
        child->parent = node->parent;
}

template <Comparable T>
T RedBlackTree<T>::maximum()
{
    Node *node = getMaximumNode(root);
    if (node == NIL)
        throw std::runtime_error("Tree is empty");
    return node->value;
}

template <Comparable T>
T RedBlackTree<T>::minimum()
{
    Node *node = getMinimumNode(root);
    if (node == NIL)
        throw std::runtime_error("Tree is empty");
    return node->value;
}

template <Comparable T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::getMinimumNode(Node *current) const
{
    if (current == NIL || current == nullptr)
        return NIL;

    Node *temp = current;

    while (temp->left != NIL)
        temp = temp->left;
    return temp;
}

template <Comparable T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::getMaximumNode(Node *current) const
{
    if (current == NIL || current == nullptr)
        return NIL;

    Node *temp = current;

    while (temp->right != NIL)
        temp = temp->right;
    return temp;
}

template <Comparable T>
bool RedBlackTree<T>::contains(const T &el) const
{
    return getNode(el) != nullptr;
}

template <Comparable T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::getNode(const T &el) const
{
    Node *current = root;
    while (current != NIL)
    {
        if (el == current->value)
            return current;

        current = (el < current->value)
                      ? current->left
                      : current->right;
    }
    return nullptr;
}

template <Comparable T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::getNodeSuccessor(const Node *node) const
{
    if (node == NIL)
        return nullptr;

    if (node->right != NIL)
        return getMinimumNode(node->right);

    Node *parent = node->parent;

    while (parent != NIL && node == parent->right)
    {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

template <Comparable T>
void RedBlackTree<T>::add(const T &el)
{
    Node *parent = NIL;
    Node *current = root;

    while (current != NIL)
    {
        parent = current;
        if (el < current->value)
            current = current->left;
        else
            current = current->right;
    }

    Node *newNode = new Node(el, NodeColor::Red, NIL, NIL, parent);

    if (parent == NIL)
        root = newNode;
    else if (newNode->value < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixTreeAfterInsertion(newNode);
    size++;
}

template <Comparable T>
void RedBlackTree<T>::remove(const T &el)
{
    Node *node = getNode(el);

    if (node == nullptr || node == NIL)
        throw std::runtime_error("Didn't find desired node!");

    Node *nodeToFix;
    Node *originalNode = node;
    NodeColor originalNodeColor = node->color;

    if (node->left == NIL)
    {
        nodeToFix = node->right;
        transplant(node, node->right);
    }
    else if (node->right == NIL)
    {
        nodeToFix = node->left;
        transplant(node, node->left);
    }
    else
    {
        Node *successor = getMinimumNode(node->right);
        originalNodeColor = successor->color;
        nodeToFix = successor->right;

        if (successor->parent == node)
            nodeToFix->parent = successor;
        else
        {
            transplant(successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }

        transplant(node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
        successor->color = node->color;
    }

    if (originalNodeColor == NodeColor::Black)
        fixTreeAfterRemoval(nodeToFix);

    delete originalNode;
    size--;
}

template <Comparable T>
void RedBlackTree<T>::leftRotate(Node *node) noexcept
{
    Node *rightSubtree = node->right;
    node->right = rightSubtree->left;

    if (rightSubtree->left != NIL)
        rightSubtree->left->parent = node;

    rightSubtree->parent = node->parent;

    if (node->parent == NIL)
        root = rightSubtree;
    else if (node == node->parent->left)
        node->parent->left = rightSubtree;
    else
        node->parent->right = rightSubtree;

    rightSubtree->left = node;
    node->parent = rightSubtree;
}

template <Comparable T>
void RedBlackTree<T>::rightRotate(Node *node) noexcept
{
    Node *leftSubtree = node->left;
    node->left = leftSubtree->right;

    if (leftSubtree->right != NIL)
        leftSubtree->right->parent = node;

    leftSubtree->parent = node->parent;

    if (node->parent == NIL)
        root = leftSubtree;
    else if (node == node->parent->right)
        node->parent->right = leftSubtree;
    else
        node->parent->left = leftSubtree;

    leftSubtree->right = node;
    node->parent = leftSubtree;
}

template <Comparable T>
void RedBlackTree<T>::fixTreeAfterInsertion(Node *node)
{
    while (node != root && isRed(node->parent))
    {
        Node *parent = node->parent;
        Node *grandparent = parent->parent;

        if (grandparent == nullptr)
            break;

        if (parent == grandparent->left)
        {
            Node *uncle = grandparent->right;

            if (isRed(uncle))
            {
                // Case 1
                parent->color = NodeColor::Black;
                uncle->color = NodeColor::Black;
                grandparent->color = NodeColor::Red;
                node = grandparent;
            }
            else
            {
                if (node == parent->right)
                {
                    // Case 2
                    node = parent;
                    leftRotate(node);
                }
                // Case 3
                parent->color = NodeColor::Black;
                grandparent->color = NodeColor::Red;
                rightRotate(grandparent);
            }
        }
        else
        {
            Node *uncle = grandparent->left;

            if (isRed(uncle))
            {
                // Case 1
                parent->color = NodeColor::Black;
                uncle->color = NodeColor::Black;
                grandparent->color = NodeColor::Red;
                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    // Case 2
                    node = parent;
                    rightRotate(node);
                }

                // Case 3
                parent->color = NodeColor::Black;
                grandparent->color = NodeColor::Red;
                leftRotate(grandparent);
            }
        }
    }
    root->color = NodeColor::Black;
}

template <Comparable T>
void RedBlackTree<T>::fixTreeAfterRemoval(Node *node)
{
    while (node != root && !isRed(node))
    {
        if (node == node->parent->left)
        {
            Node *sibling = node->parent->right;

            // Case 1
            if (isRed(sibling))
            {
                sibling->color = NodeColor::Black;
                node->parent->color = NodeColor::Red;
                leftRotate(node->parent);
                sibling = node->parent->right;
            }

            // Case 2
            if (!isRed(sibling->left) && !isRed(sibling->right))
            {
                sibling->color = NodeColor::Red;
                node = node->parent;
            }
            else
            {
                // Case 3
                if (!isRed(sibling->right))
                {
                    if (sibling->left != NIL)
                        sibling->left->color = NodeColor::Black;

                    sibling->color = NodeColor::Red;
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }

                // Case 4
                sibling->color = node->parent->color;
                node->parent->color = NodeColor::Black;

                if (sibling->right != NIL)
                    sibling->right->color = NodeColor::Black;

                leftRotate(node->parent);
                node = root;
            }
        }
        else
        {
            Node *sibling = node->parent->left;

            // Case 1
            if (isRed(sibling))
            {
                sibling->color = NodeColor::Black;
                node->parent->color = NodeColor::Red;
                rightRotate(node->parent);
                sibling = node->parent->left;
            }

            // Case 2
            if (!isRed(sibling->left) && !isRed(sibling->right))
            {
                sibling->color = NodeColor::Red;
                node = node->parent;
            }
            else
            {
                // Case 3
                if (!isRed(sibling->left))
                {
                    if (sibling->right != NIL)
                        sibling->right->color = NodeColor::Black;

                    sibling->color = NodeColor::Red;
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }

                // Case 4
                sibling->color = node->parent->color;
                node->parent->color = NodeColor::Black;

                if (sibling->left != NIL)
                    sibling->left->color = NodeColor::Black;

                rightRotate(node->parent);
                node = root;
            }
        }
    }

    if (node != NIL)
        node->color = NodeColor::Black;
}

template <Comparable T>
bool RedBlackTree<T>::isValid() const
{
    if (root == NIL)
        return true;
    if (root->color == NodeColor::Red)
        return false;

    int blackHeight = -1;
    return validateRules(root, 0, blackHeight);
}

template <Comparable T>
bool RedBlackTree<T>::validateRules(Node *node, int currentBlackCount, int &expectedBlackCount) const noexcept
{
    if (node == NIL)
    {
        if (expectedBlackCount == -1)
        {
            expectedBlackCount = currentBlackCount;
        }
        return currentBlackCount == expectedBlackCount;
    }

    if (isRed(node))
    {
        if (isRed(node->left) || isRed(node->right))
            return false;
    }

    if (!isRed(node))
        currentBlackCount++;

    return validateRules(node->left, currentBlackCount, expectedBlackCount) &&
           validateRules(node->right, currentBlackCount, expectedBlackCount);
}

template <Comparable T>
bool RedBlackTree<T>::isRed(Node *node) const noexcept
{
    if (node == NIL)
        return false;
    return (node->color == NodeColor::Red);
}

template <Comparable T>
int RedBlackTree<T>::getSize() const
{
    return size;
}