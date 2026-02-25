#pragma once

#include "RedBlackTree.hpp"

template <typename T>
const std::string RedBlackTree<T>::EMPTY_TREE_MESSAGE = "Empty Tree";

template <typename T>
RedBlackTree<T>::RedBlackTree(IComparator<T> *comp) : comparator(comp)
{
    NIL = new Node(T(), true, NULL, NULL, NULL);
    NIL->left = NIL->right = NIL->parent = NIL;

    root = NIL;
    size = 0;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree()
{
    deleteSubtree(root);
    root = NULL;
    size = 0;

    delete NIL;
}

template <typename T>
void RedBlackTree<T>::clear()
{
    deleteSubtree(root);
    root = NIL;
    size = 0;
}

template <typename T>
IIterator<T> *RedBlackTree<T>::iterator() const
{
    return new Iterator(root, NIL);
}

template <typename T>
RedBlackTree<T>::Iterator::Iterator(Node *root, Node *nil)
    : current(root), nil(nil)
{
    while (current != nil)
    {
        stack.push(current);
        current = current->left;
    }
}

template <typename T>
bool RedBlackTree<T>::Iterator::hasNext() const
{
    return !stack.isEmpty();
}

template <typename T>
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

template <typename T>
std::string RedBlackTree<T>::toString() const
{
    if (root == NIL)
        return EMPTY_TREE_MESSAGE;
    return toStringRecursive(root, 0);
}

template <typename T>
std::string RedBlackTree<T>::toStringRecursive(const Node *node, int level) const
{
    if (node == NIL)
        return "";

    std::string result;

    for (int i = 0; i < level; ++i)
        result += "\t";

    result +=
        "|--> " +
        std::to_string(node->value) +
        (node->color ? " [BLACK]" : " [RED]") +
        "\n";

    result += toStringRecursive(node->left, level + 1);
    result += toStringRecursive(node->right, level + 1);

    return result;
}

template <typename T>
void RedBlackTree<T>::deleteSubtree(Node *node)
{
    if (node == NIL)
        return;

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    size--;
    delete node;
}

template <typename T>
void RedBlackTree<T>::transplant(Node *node, Node *child)
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

template <typename T>
T RedBlackTree<T>::maximum()
{
    Node *node = getMaximumNode(root);
    if (node == NIL)
        throw std::runtime_error("Tree is empty");
    return node->value;
}

template <typename T>
T RedBlackTree<T>::minimum()
{
    Node *node = getMinimumNode(root);
    if (node == NIL)
        throw std::runtime_error("Tree is empty");
    return node->value;
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::getMinimumNode(Node *current) const
{
    if (current == NIL || current == NULL)
        return NIL;

    Node *temp = current;

    while (temp->left != NIL)
        temp = temp->left;
    return temp;
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::getMaximumNode(Node *current) const
{
    if (current == NIL || current == NULL)
        return NIL;

    Node *temp = current;

    while (temp->right != NIL)
        temp = temp->right;
    return temp;
}

template <typename T>
bool RedBlackTree<T>::contains(const T &el) const
{
    return getNode(el) != NULL;
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::getNode(const T &el) const
{
    Node *current = root;

    while (current != NIL)
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
typename RedBlackTree<T>::Node *RedBlackTree<T>::getNodeSuccessor(const Node *node) const
{
    if (node == NIL)
        return NULL;

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

template <typename T>
void RedBlackTree<T>::add(const T &el)
{
    if (comparator == NULL)
        throw std::runtime_error("Comparator is undefined!");

    Node *currentParent = NIL;
    Node *currentEl = root;

    while (currentEl != NIL)
    {
        currentParent = currentEl;

        int comparison = comparator->compare(el, currentEl->value);
        if (comparison < 0)
            currentEl = currentEl->left;
        else
            currentEl = currentEl->right;
    }

    Node *newNode = new Node(el, false, NIL, NIL, currentParent);

    if (currentParent == NIL)
    {
        newNode->color = true;
        root = newNode;
    }
    else
    {
        int comparison = comparator->compare(el, currentParent->value);
        if (comparison < 0)
            currentParent->left = newNode;
        else
            currentParent->right = newNode;

        fixTreeAfterInsertion(newNode);
    }
    size++;
}

template <typename T>
void RedBlackTree<T>::remove(const T &el)
{
    Node *node = getNode(el);

    if (node == NULL || node == NIL)
        throw std::runtime_error("Didn't find desired node!");

    Node *nodeToFix;
    Node *originalNode = node;
    bool originalNodeColor = node->color;

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

    if (originalNodeColor)
        fixTreeAfterRemoval(nodeToFix);

    delete originalNode;
    size--;
}

template <typename T>
void RedBlackTree<T>::leftRotate(Node *node)
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

template <typename T>
void RedBlackTree<T>::rightRotate(Node *node)
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

template <typename T>
void RedBlackTree<T>::fixTreeAfterInsertion(Node *node)
{
    while (node != root && isRed(node->parent))
    {
        Node *parent = node->parent;
        Node *grandparent = parent->parent;

        if (grandparent == NULL)
            break;

        if (parent == grandparent->left)
        {
            Node *uncle = grandparent->right;

            if (isRed(uncle))
            {
                // Case 1
                parent->color = true;
                uncle->color = true;
                grandparent->color = false;
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
                parent->color = true;
                grandparent->color = false;
                rightRotate(grandparent);
            }
        }
        else
        {
            Node *uncle = grandparent->left;

            if (isRed(uncle))
            {
                // Case 1
                parent->color = true;
                uncle->color = true;
                grandparent->color = false;
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
                parent->color = true;
                grandparent->color = false;
                leftRotate(grandparent);
            }
        }
    }
    root->color = true;
}

template <typename T>
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
                sibling->color = true;
                node->parent->color = false;
                leftRotate(node->parent);
                sibling = node->parent->right;
            }

            // Case 2
            if (!isRed(sibling->left) && !isRed(sibling->right))
            {
                sibling->color = false;
                node = node->parent;
            }
            else
            {
                // Case 3
                if (!isRed(sibling->right))
                {
                    if (sibling->left != NIL)
                        sibling->left->color = true;

                    sibling->color = false;
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }

                // Case 4
                sibling->color = node->parent->color;
                node->parent->color = true;

                if (sibling->right != NIL)
                    sibling->right->color = true;

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
                sibling->color = true;
                node->parent->color = false;
                rightRotate(node->parent);
                sibling = node->parent->left;
            }

            // Case 2
            if (!isRed(sibling->left) && !isRed(sibling->right))
            {
                sibling->color = false;
                node = node->parent;
            }
            else
            {
                // Case 3
                if (!isRed(sibling->left))
                {
                    if (sibling->right != NIL)
                        sibling->right->color = true;

                    sibling->color = false;
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }

                // Case 4
                sibling->color = node->parent->color;
                node->parent->color = true;

                if (sibling->left != NIL)
                    sibling->left->color = true;

                rightRotate(node->parent);
                node = root;
            }
        }
    }

    if (node != NIL)
        node->color = true;
}

template <typename T>
bool RedBlackTree<T>::isValid() const
{
    if (root == NIL)
        return true;
    if (root->color == false)
        return false;

    int blackHeight = -1;
    return validateRules(root, 0, blackHeight);
}

template <typename T>
bool RedBlackTree<T>::validateRules(Node *node, int currentBlackCount, int &expectedBlackCount) const
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

template <typename T>
bool RedBlackTree<T>::isRed(Node *node) const
{
    if (node == NIL)
        return false;
    return !node->color;
}

template <typename T>
int RedBlackTree<T>::getSize() const
{
    return size;
}