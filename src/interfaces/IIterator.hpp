#pragma once

template <typename T>
class IIterator
{
public:
    virtual bool hasNext();
    virtual T next();
};