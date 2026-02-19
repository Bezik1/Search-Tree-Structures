#include "DoubleComparator.hpp"

int DoubleComparator::compare(const double &el, const double &other) const
{
    if (el < other)
        return -1;
    else if (el > other)
        return 1;
    else
        return 0;
}