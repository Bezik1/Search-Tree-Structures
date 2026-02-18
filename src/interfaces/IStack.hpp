#pragma once

template <typename T>
class IStack
{
public:
    virtual void push(const T &el) = 0;
    virtual T pop() = 0;
    virtual T &top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
};