#include <iostream>

#include "core/BinarySearchTree/BinarySearchTree.hpp"
#include "core/RedBlackTree/RedBlackTree.hpp"
#include "utils/comparators/DoubleComparator/DoubleComparator.hpp"

int main()
{
    DoubleComparator comparator;
    RedBlackTree<double> rbt(&comparator);

    rbt.add(10.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(11.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(9.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.remove(10.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(13.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(7.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(5.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.remove(9.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.remove(11.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(14.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(15.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(16.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(17.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    rbt.add(18.0);
    std::cout << rbt.toString() << std::endl;
    std::cout << "Is valid RBT: " << (rbt.isValid() ? "TRUE" : "FALSE") << std::endl;

    return 0;
}