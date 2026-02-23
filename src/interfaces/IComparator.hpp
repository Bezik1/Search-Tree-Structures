#pragma once

/**
 * @ingroup Interfaces
 *
 * @brief Used as universal comparator class to properly implement '<', '>', '==' relations.
 *
 * @details Specifies, whether elements are greater, smaller than or equal to other element. It
 * is done by returning int information about this comparison, where:
 * 1. 1  - el is greater, than the other;
 * 2. 0  - el is equal to other;
 * 3. -1 - el is smaller, than the other;
 *
 * @tparam T - type of compared elements.
 */
template <typename T>
class IComparator
{
public:
    virtual ~IComparator() = default;

    /**
     * @brief Compare the elements of type T.
     *
     * @details Main function of IComparator class that performs
     * comparison. It should be implemented, so the return values
     * are in the set: {-1, 0, 1}, where -1 informs that el is smaller,
     * 0 that is equal and 1 that is greater than the other element.
     *
     * @param el - left element of comparison.
     * @param other - right element of comparison.
     *
     * @see DoubleComparator
     *
     * @note Required method.
     *
     * @return int - comparison return inforamtion.
     */
    virtual int compare(const T &el, const T &other) const = 0;
};