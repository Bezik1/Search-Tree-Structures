#pragma once

#include "../../../interfaces/IComparator.hpp"

class DoubleComparator : public IComparator<double>
{
public:
    DoubleComparator() = default;
    int compare(const double &el, const double &other) const override;
};