#pragma once

/**
 * @brief This interface represents an iterator over collection.
 *
 * @details Class implementing this interface has an ability to traverse
 * given collection. To achievie it, it needs to use hasNext method:
 *
 * ```
 * while(iter->hasNext())
 * ```
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