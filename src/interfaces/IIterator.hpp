#pragma once

/**
 * @brief 
 * 
 * @tparam T 
 */
template <typename T>
class IIterator
{
public:
    virtual ~IIterator() = default;
    virtual void remove() {};
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};