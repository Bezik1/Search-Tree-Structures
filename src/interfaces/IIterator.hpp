#pragma once

/**
 * @ingroup Interfaces
 *
 * @brief Represents the general functionalities of iterator over collection.
 *
 * @details Class implementing this interface has an ability to traverse
 * given collection. To achievie it, it needs to use {@link #hasNext} method:
 *
 * ```cpp
 *  auto iter = [Collection<T>].iterator();
 *
 *  while(iter->hasNext())
 *  {
 *      T el = iter->next();
 *      Rest of the code...
 *  }
 * ```
 *
 * @todo
 * 1. Finish comments.
 * 2. Implement * operator;
 *
 * @tparam T - type of stored data inside collection of iterator.
 */
template <typename T>
class IIterator
{
public:
    virtual ~IIterator() = default;

    /**
     * @brief Removes current element from the collection.
     *
     */
    virtual void remove() {};

    /**
     * @brief Returns the boolean information about, wheter collection has
     * a next element or not (e.g wheter iterator can still traverse collection).
     *
     * @note Required method.
     *
     * @return true.
     * @return false.
     */
    virtual bool hasNext() const = 0;

    /**
     * @brief Returns the next object in the given collection.
     *
     * @note Required method.
     *
     * @return T next element in the collection.
     */
    virtual T next() = 0;
};