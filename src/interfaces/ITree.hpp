#pragma once

#include "IIterator.hpp"

template <typename T>
class ITree
{
public:
    virtual IIterator<T> *iterator() const = 0;
    virtual ~ITree() = default;

    virtual void add(T value) = 0;
    virtual void clear() = 0;
    virtual void remove(T el) = 0;

    virtual bool contains(T el) const = 0;
    virtual int getSize() const = 0;
};