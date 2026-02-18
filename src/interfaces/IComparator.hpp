#pragma once

template <typename T>
class IComparator
{
public:
    virtual ~IComparator() = default;
    virtual int compare(const T &el, const T &other) const = 0;
};