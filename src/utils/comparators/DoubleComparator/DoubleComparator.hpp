#pragma once

#include "../../../interfaces/IComparator.hpp"

/**
 * @brief Implementation of IComparator interface for the double type.
 *
 */
class DoubleComparator : public IComparator<double>
{
public:
    DoubleComparator() = default;
    int compare(const double &el, const double &other) const override;
};