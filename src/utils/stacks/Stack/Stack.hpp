#pragma once

#include <iostream>
#include <vector>

#include "../../../interfaces/IStack.hpp"

template <typename T>
class Stack : public IStack<T>
{
private:
    std::vector<T> data;

public:
    Stack() = default;
    ~Stack() = default;

    void push(const T &el) override;
    T pop() override;
    const T &top() override;
    const bool isEmpty() const override;
    int getSize() const override;
};