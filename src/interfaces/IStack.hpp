#pragma once

/**
 * @ingroup Interfaces
 *
 * @brief It represents LIFO (e.g Last In First Out) collection.
 *
 * @details In this structure order of insertion of elements is inversely
 * proprtional to the order of removal of elements. The inner collection that
 * holds the elements is not specified, because there are various versions of
 * stacks.
 *
 * @see Stack
 *
 * @tparam T - represents type of stored data.
 */
template <typename T>
class IStack
{
public:
    /**
     * @brief Adds new element at the top of the stack.
     *
     * @note Required method.
     *
     * @param el value of new element.
     */
    virtual void push(const T &el) = 0;

    /**
     * @brief Removes the top element of the stack and returns its value.
     *
     * @note Required method.
     *
     * @return T element at the top of the stack.
     */
    virtual T pop() = 0;

    /**
     * @brief Returns the top element of the stack, without removing it.
     *
     * @note Required method.
     *
     * @return T address of element at the top of the stack.
     */
    virtual T &top() = 0;

    /**
     * @brief Returns the information, whether stack is empty.
     *
     * @note Required method.
     *
     * @return true.
     * @return false.
     */
    virtual const bool isEmpty() const = 0;

    /**
     * @brief Returns the count of all elements in the stack.
     *
     * @note Required method.
     *
     * @return int - count of all elements.
     */
    virtual int getSize() const = 0;
};