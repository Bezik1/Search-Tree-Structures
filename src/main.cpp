#include <iostream>
#include "core/BinarySearchTree/BinarySearchTree.hpp"
#include "utils/comparators/DoubleComparator/DoubleComparator.hpp"

int main()
{
    DoubleComparator doubleComparator;
    BinarySearchTree<double> bst(&doubleComparator);

    bst.add(5.0);
    bst.add(3.0);
    bst.add(7.0);
    bst.add(1.0);
    bst.add(4.0);

    auto iter = bst.iterator();

    while (iter->hasNext())
    {
        double value = iter->next();
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << bst.getSize() << std::endl;
    return 0;
}