#pragma once

#include "iostream"
#include "IIterator.hpp"

template <typename T>
class ITree
{
public:
    virtual IIterator<T> *iterator() const = 0;
    virtual ~ITree() = default;

    virtual void add(const T &el) = 0;
    virtual void clear() = 0;
    virtual void remove(const T &el) = 0;

    virtual bool contains(T el) const = 0;
    virtual int getSize() const = 0;

    virtual std::string toString() const = 0;
};