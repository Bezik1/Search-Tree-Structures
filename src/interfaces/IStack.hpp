#pragma once

template <typename T>
class IStack
{
public:
    virtual void push(const T &el) = 0;
    virtual T pop() = 0;
    virtual T &top() = 0;
    virtual const bool isEmpty() const = 0;
    virtual int getSize() const = 0;
};