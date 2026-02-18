#include <iostream>
#include "core/BinarySearchTree/BinarySearchTree.hpp"
#include "utils/comparators/DoubleComparator/DoubleComparator.hpp"

int main()
{
    DoubleComparator doubleComparator;
    BinarySearchTree<double> bst(&doubleComparator);

    bst.add(1.0f);

    std::cout << bst.getSize() << std::endl;
    return 0;
}