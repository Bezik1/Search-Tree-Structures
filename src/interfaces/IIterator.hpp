#pragma once

template <typename T>
class IIterator
{
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};