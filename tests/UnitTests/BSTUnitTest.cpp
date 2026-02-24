#include <gtest/gtest.h>

#include "../../src/core/BinarySearchTree/BinarySearchTree.hpp"
#include "../../src/utils/comparators/DoubleComparator/DoubleComparator.hpp"

/**
 * @brief Tests for BinarySearchTree class.
 *
 * @todo Create more reliable tests.
 *
 * @test
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

TEST_F(BSTUnitTest, InsertionAndSizeTest)
{
    bst->add(5.0);
    bst->add(10.0);
    bst->add(3.0);

    ASSERT_EQ(bst->getSize(), 3) << "Binary Search Tree size is not matching it's predicted value!";
}

TEST_F(BSTUnitTest, IteratorOrderTest)
{
    bst->add(5.0);
    bst->add(3.0);
    bst->add(7.0);

    auto iter = bst->iterator();

    EXPECT_TRUE(iter->hasNext());
    EXPECT_DOUBLE_EQ(iter->next(), 3.0);
    EXPECT_DOUBLE_EQ(iter->next(), 5.0);
    EXPECT_DOUBLE_EQ(iter->next(), 7.0);
    EXPECT_FALSE(iter->hasNext());

    delete iter;
}

TEST_F(BSTUnitTest, RemovalTest)
{
    bst->add(5.0);
    bst->add(3.0);
    bst->add(7.0);

    bst->remove(5.0);
    EXPECT_EQ(bst->getSize(), 2);

    auto iter = bst->iterator();
    EXPECT_DOUBLE_EQ(iter->next(), 3.0);
    EXPECT_DOUBLE_EQ(iter->next(), 7.0);
    delete iter;
}