#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
void Stack<T>::push(const T &el)
{
    data.push_back(el);
    size++;
}

template <typename T>
T Stack<T>::pop()
{
    if (isEmpty())
        throw std::out_of_range("Stack is empty. Cannot pop.");

    T value = data.back();
    data.pop_back();
    size--;
    return value;
}

template <typename T>
T &Stack<T>::top()
{
    if (isEmpty())
        throw std::out_of_range("Stack is empty. Cannot access top.");

    return data.back();
}

template <typename T>
const bool Stack<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
int Stack<T>::getSize() const
{
    return size;
}