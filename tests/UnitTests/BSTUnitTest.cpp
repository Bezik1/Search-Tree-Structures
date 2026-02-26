#include <gtest/gtest.h>

#include "../../src/core/BinarySearchTree/BinarySearchTree.hpp"
#include "../../src/utils/comparators/DoubleComparator/DoubleComparator.hpp"

/**
 * @brief Tests for BinarySearchTree class.
 *
 * @todo
 * 1. Refactor this test to implement C++ 23;
 *
 * @test
 *
 */
class BSTUnitTest : public testing::Test
{
protected:
    DoubleComparator comparator;
    BinarySearchTree<double> *bst;

    void SetUp() override
    {
        bst = new BinarySearchTree<double>(&comparator);
    }

    void TearDown() override
    {
        delete bst;
    }
};

TEST_F(BSTUnitTest, IteratorGeneralTest)
{
    bst->add(5.0);
    bst->add(3.0);
    bst->add(7.0);

    auto iter = bst->iterator();
    ASSERT_TRUE(iter != NULL);

    ASSERT_TRUE(iter->hasNext());
    ASSERT_DOUBLE_EQ(iter->next(), 3.0);
    ASSERT_DOUBLE_EQ(iter->next(), 5.0);
    ASSERT_DOUBLE_EQ(iter->next(), 7.0);
    ASSERT_FALSE(iter->hasNext());
}

TEST_F(BSTUnitTest, RemovalGeneralTest)
{
    ASSERT_THROW(bst->remove(3.0), std::runtime_error);

    bst->add(4.0);
    ASSERT_EQ(bst->contains(4.0), true);

    bst->remove(4.0);
    ASSERT_EQ(bst->contains(4.0), false);

    bst->add(6.0);
    bst->add(7.0);
    bst->add(8.0);

    bst->remove(8.0);
    ASSERT_EQ(bst->contains(8.0), false);

    bst->remove(6.0);
    ASSERT_EQ(bst->contains(6.0), false);

    bst->remove(7.0);
    ASSERT_EQ(bst->contains(7.0), false);
}

TEST_F(BSTUnitTest, ExtremasGeneralTest)
{
    ASSERT_THROW(bst->maximum(), std::runtime_error);
    ASSERT_THROW(bst->minimum(), std::runtime_error);

    bst->add(5.0);
    ASSERT_EQ(bst->maximum(), 5.0);
    ASSERT_EQ(bst->minimum(), 5.0);

    bst->add(3.0);
    ASSERT_EQ(bst->maximum(), 5.0);
    ASSERT_EQ(bst->minimum(), 3.0);

    bst->add(11.0);
    ASSERT_EQ(bst->maximum(), 11.0);
    ASSERT_EQ(bst->minimum(), 3.0);

    bst->add(4.0);
    ASSERT_EQ(bst->maximum(), 11.0);
    ASSERT_EQ(bst->minimum(), 3.0);

    bst->add(2.0);
    ASSERT_EQ(bst->maximum(), 11.0);
    ASSERT_EQ(bst->minimum(), 2.0);

    bst->clear();
    ASSERT_THROW(bst->maximum(), std::runtime_error);
    ASSERT_THROW(bst->minimum(), std::runtime_error);
}