#pragma once

#include <iostream>

#include "../../utils/stacks/Stack/Stack.hpp"

#include "../../interfaces/IStack.hpp"
#include "../../interfaces/ITree.hpp"
#include "../../interfaces/IIterator.hpp"
#include "../../interfaces/IComparator.hpp"

/**
 * @brief Dynamic and efficient implementation of ITree interface. It uses red and black
 * node categories to optimize the structure to operate in O(log n) strict time.
 *
 * @details Red black tree is the ITree structure with additional color field in Node struct.
 * This fact, also means that there are following rules that touch the topic of nodes color:
 * 1. Each node is either red or black;
 * 2. Root is always black;
 * 3. Red nodes cannot have red children;
 * 4. Every path from a node to its descendant leafs must have the same number of black nodes;
 * 5. All leafs are black.
 *
 * @todo
 * 1. Create a copy constructor;
 * 2. Create copy assignment operator;
 * 3. Create [NIL  / Leaf] Node that will be used instead of NULL Nodes. This problem is specificly visible in
 * {@link #fixTreeAfterRemoval}
 * 4. Update {@link #toString} method to include information about node color.
 *
 *
 * @see ITree
 * @see IComparator
 * @see IIterator
 * @see Node
 *
 * @tparam T
 *
 * @author Mateusz Adamowicz
 */
template <typename T>
class RedBlackTree : public ITree<T>
{
public:
    ~RedBlackTree();

    RedBlackTree(IComparator<T> *comp = NULL);

    /**
     * @brief Returns the iterator for RedBlackTree.
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
     * @brief Returns the miniumum element of the RBT.
     *
     * @details It uses the key rule of RBT, which is that
     * left child is always smaller, than it's parent. One can
     * then observe that the leftmost child must be the miniumum.
     *
     * For comparison RedBlackTree uses {@link #comparator} object that
     * implements IComparator interface.
     *
     * The real implementation invoke private {@link #getMinimumNode} method,
     * with the root as the argument to activate it.
     *
     * @see getMinimumNode
     * @see IComparator
     *
     * @throws std::runtime_error - Tree is empty!
     *
     * @return T - minimum element.
     */
    T minimum();

    /**
     * @brief Returns the maximum element of the RBT.
     *
     * @details It uses the key rule of RBT, which is that
     * right child is always greater, than it's parent. One can
     * then observe that the rightmost child must be the maximum.
     *
     * For comparison RedBlackTree uses {@link #comparator} object that
     * implements IComparator interface.
     *
     * The real implementation invoke private {@link #getMaximumNode} method,
     * with the root as the argument to activate it.
     *
     * @see getMaximumNode
     * @see IComparator
     *
     * @throws std::runtime_error - Tree is empty!
     *
     * @return T - maximum element.
     */
    T maximum();

    /**
     * @brief Adds new element to RBT.
     *
     * @details New node is inserted to the tree, by using the basic properties of Searching Trees.
     * After that program checks, whether the additional conditions implemented according to RBT
     * architecture are not broken. To fix eventual bugs program invoke {@link #fixTreeAfterInsertion} method,
     * which repairs tree after insertion and further repairs it up to the root node.
     *
     * @see IComparator
     * @see Node
     *
     * @throws std::runtime_error - Comparator is undefined!
     *
     * @param el - value of the new element
     */
    void add(const T &el) override;

    /**
     * @brief Removes element from RBT.
     *
     * @details Node is removed from the tree. This action can break the rules of RBT and BST. To avoid
     * incorrect structure, we invoke {@link #fixTreeAfterRemoval} to repair occured errors.
     *
     * @see transplant
     * @see getNodeSuccessor
     *
     * @throws std::runtime_error - Didn't find desired node!
     *
     * @param el - element to remove.
     */
    void remove(const T &el);

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
     * @brief Searches the RBT to find if el is in the tree.
     *
     * @details To achievie it, RBT uses it's core principles and IComparator
     * to compare the values of nodes in the tree to find the desired value.
     * This fact allows RBT for average search time of O(log n).
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
    bool contains(const T &el) const;

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
    std::string toString() const;

    int getSize() const override;

private:
    static const std::string EMPTY_TREE_MESSAGE;

    /**
     * @brief It's the basic building block of RedBlackTree.
     *
     * @details Nodes store information in RedBlackTree. They are internally connect via
     * reference to {@link #parent}, {@link #left} and {@link #right} child. In RedBlackTree
     * Node additionaly has field color, which is used in order to optimize this collection.
     *
     * This implementation represents Nodes as a struct, because I didn't see the purpose in creating
     * the implementation of additional functions inside Node that would be present in class representation.
     *
     * Color of the Node is boolean type variable, where boolean values mean:
     * false - red;
     * true - black;
     *
     *
     */
    struct Node
    {
        T value;
        bool color;
        Node *left;
        Node *right;
        Node *parent;

        Node(const T &value)
            : value(value), left(NULL), right(NULL), parent(NULL), color(true) {};

        Node(const T &value,
             bool color,
             Node *left,
             Node *right,
             Node *parent)
            : value(value),
              color(color),
              left(left),
              right(right),
              parent(parent) {}
    };

    /**
     * @brief Implementation of IIterator interface for RedBlackTree.
     *
     * @details This implementation uses `InOrderWalk`, which returnes elements
     * in the tree in the sorted order. It did not implement remove
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
         * @brief Returns next object in sotred order of RedBlackTree.
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
     * @brief Returns the maximum node of the RBT.
     *
     * @details It uses the key rule of RBT, which is that
     * right child is always greater, than it's parent. One can
     * then observe that the rightmost child must be the maximum.
     *
     * For comparison RedBlackTree uses {@link #comparator} object that
     * implements IComparator interface.
     *
     * @see getMaximumNode
     * @see IComparator
     *
     * @return T - maximum element.
     */
    Node *getMaximumNode(Node *current) const;

    /**
     * @brief Returns the minmimum node of the RBT.
     *
     * @details It uses the key rule of RBT, which is that
     * left child is always smaller, than it's parent. One can
     * then observe that the leftmost child must be the minimum.
     *
     * For comparison RedBlackTree uses {@link #comparator} object that
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
     * @brief Searches the RBT to find if node is in the tree.
     *
     * @details To achievie it, RBT uses it's core principles and IComparator
     * to compare the values of nodes in the tree to find the desired value.
     * This fact allows RBT for average search time of O(log n).
     *
     * @param el - value of searched element
     *
     * @return Node* - pointer to desired Node.
     */
    Node *getNode(const T &el) const;

    /**
     * @brief Rotates the desired subtree to the left.
     *
     * @details To properly discuss this type of rotation, lets
     * consider following scheme:
     *
     *         x                        y
     *           \                     / \
     *            y         =>        x   b
     *           / \                   \
     *          a   b                   a
     *
     * To properly perform this rotation, we need to:
     * 1. Detach Subtree: Move y's left subtree to become x's new right subtree;
     * 2. Shift Parent Link: Update y’s parent to be x’s current parent;
     * 3. Relink Parent: Update x’s parent to point to y instead of x;
     * 4. Promote Child: Set y’s left child to x;
     * 5. Finalize Parent: Set x’s parent to y;
     *
     * @param node - current pivot node of rotation.
     *
     */
    void leftRotate(Node *node);

    /**
     * @brief Rotates the desired subtree to the right.
     *
     * @details To properly discuss this type of rotation, lets
     * consider following scheme:
     *
     *         x                    y
     *        /                    / \
     *       y          =>        a   x
     *      / \                      /
     *     a   b                    b
     *
     * To properly perform this rotation, we need to:
     * 1. Detach Subtree: Move y’s right subtree to become x’s new left subtree.
     * 2. Shift Parent Link: Update y’s parent to be x’s current parent.
     * 3. Relink Parent: Update x’s parent to point to y instead of x.
     * 4. Promote Child: Set y’s right child to x.
     * 5. Finalize Parent: Set x’s parent to y
     *
     * @param node - current pivot node of rotation.
     *
     */
    void rightRotate(Node *node);

    /**
     * @brief Insertion of element can break the rules of RBT, so this function repairs it.
     *
     * @details We distinguish following categories of breaking RBT rules, by instertion:
     * 1. The parent and the uncle are red;
     * 2. The [left / right] child of [right / left] child of the node are both red;
     * 3. The [left / right] child of [left / right] child of the node are both red;
     *
     * For each case to fix tree, we:
     * 1. We set the color of parent, uncle to black and the color of grandfather to red and we
     * go up the tree to grandparent to fix it further if necessary;
     * 2. We [leftRotate / rightRotate] the parent and we go to case 3;
     * 3. We set the color of parent to black, grandfather to red and we [rightRotate / leftRotate] him;
     *
     * @param node - freshly added node.
     *
     */
    void fixTreeAfterInsertion(Node *node);

    /**
     * @brief Removal of element can break the rules of RBT, so this function repairs it.
     *
     * @details We distinguish following categories of breaking RBT rules, by removal:
     * 1. Brother of succesor node is red;
     * 2. Brother of succesor node is black and both of his children are black;
     * 3. Brother of succesor node is black, his left child is red and the right one is black;
     * 4. Brother of succesor node is black and his right children is red;
     *
     * For each case to fix tree, we:
     * 1. We change the color of brother of sucessor node to black, color of his parent to red and
     * we [leftRotate / rightRotate] it's parent. After that we go to either cases: [2 / 3 / 4].
     * 2. We change the color of brother of sucessor node to red and we analyze errors further in the tree.
     * 3. We swap the color of the left child of brother of sucessor node to the color
     * of the succesor, we [leftRotate / rightRotate] the succesor node and we go to case 4.
     * 4. We change the color of brother of the succesor node to it's parent one, we set the parent
     * and the right child of the brother of succesor node to black, then we [rotateLeft / rotateRight]
     * the parent and finally we set succesor node to the root.
     *
     * @param node - successor of deleted node.
     *
     */
    void fixTreeAfterRemoval(Node *node);

    /**
     * @brief
     *
     * @param node
     * @return true
     * @return false
     */
    bool isRed(Node *node) const;

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

#include "RedBlackTree.tpp"