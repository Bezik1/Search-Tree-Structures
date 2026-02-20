#pragma once

#include <iostream>

#include "../../interfaces/ITree.hpp"

template <typename T>
class RedBlackTree : public ITree<T>
{
}

#include "RedBlackTree.tpp"