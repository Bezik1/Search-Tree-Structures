#pragma once

#include <iostream>
#include <vector>

#include "../../../interfaces/IStack.hpp"

/**
 * @brief Simple implementation of IStack interface, with std::vector, as
 * a storing collection.
 *
 * @tparam T
 */
template <typename T>
class Stack : public IStack<T>
{
private:
    std::vector<T> data;
    int size = 0;

public:
    Stack() = default;
    ~Stack() = default;

    void push(const T &el) override;
    T pop() override;
    T &top() override;
    const bool isEmpty() const override;
    int getSize() const override;
};

#include "Stack.tpp"