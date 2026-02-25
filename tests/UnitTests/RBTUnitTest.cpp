#include <gtest/gtest.h>

#include "../../src/core/RedBlackTree/RedBlackTree.hpp"
#include "../../src/utils/comparators/DoubleComparator/DoubleComparator.hpp"

/**
 * @brief Tests for RedBlackTree class.
 *
 * @todo
 * 1. Create more reliable tests;
 *
 * @test
 */
class RBTUnitTest : public testing::Test
{
protected:
    DoubleComparator comparator;
    RedBlackTree<double> *rbt;

    void SetUp() override
    {
        rbt = new RedBlackTree<double>(&comparator);
    }

    void TearDown() override
    {
        delete rbt;
    }
};

TEST_F(RBTUnitTest, IteratorGeneralTest)
{
    rbt->add(5.0);
    rbt->add(3.0);
    rbt->add(8.0);
    rbt->add(10.0);
    rbt->add(11.0);
    rbt->add(7.0);

    auto iter = rbt->iterator();
    ASSERT_TRUE(iter != NULL);

    ASSERT_TRUE(iter->hasNext());
    ASSERT_DOUBLE_EQ(iter->next(), 3.0);
    ASSERT_DOUBLE_EQ(iter->next(), 5.0);
    ASSERT_DOUBLE_EQ(iter->next(), 7.0);
    ASSERT_DOUBLE_EQ(iter->next(), 8.0);
    ASSERT_DOUBLE_EQ(iter->next(), 10.0);
    ASSERT_DOUBLE_EQ(iter->next(), 11.0);
    ASSERT_FALSE(iter->hasNext());

    delete iter;
}

TEST_F(RBTUnitTest, RemovalGeneralTest)
{
    ASSERT_THROW(rbt->remove(3.0), std::runtime_error);

    rbt->add(4.0);
    ASSERT_EQ(rbt->contains(4.0), true);

    rbt->remove(4.0);
    ASSERT_EQ(rbt->contains(4.0), false);

    rbt->add(6.0);
    rbt->add(7.0);
    rbt->add(8.0);

    rbt->remove(8.0);
    ASSERT_EQ(rbt->contains(8.0), false);

    rbt->remove(6.0);
    ASSERT_EQ(rbt->contains(6.0), false);

    rbt->remove(7.0);
    ASSERT_EQ(rbt->contains(7.0), false);
}

TEST_F(RBTUnitTest, ExtremasGeneralTest)
{
    ASSERT_THROW(rbt->maximum(), std::runtime_error);
    ASSERT_THROW(rbt->minimum(), std::runtime_error);

    rbt->add(5.0);
    ASSERT_EQ(rbt->maximum(), 5.0);
    ASSERT_EQ(rbt->minimum(), 5.0);

    rbt->add(3.0);
    ASSERT_EQ(rbt->maximum(), 5.0);
    ASSERT_EQ(rbt->minimum(), 3.0);

    rbt->add(11.0);
    ASSERT_EQ(rbt->maximum(), 11.0);
    ASSERT_EQ(rbt->minimum(), 3.0);

    rbt->add(4.0);
    ASSERT_EQ(rbt->maximum(), 11.0);
    ASSERT_EQ(rbt->minimum(), 3.0);

    rbt->add(2.0);
    ASSERT_EQ(rbt->maximum(), 11.0);
    ASSERT_EQ(rbt->minimum(), 2.0);

    rbt->clear();
    ASSERT_THROW(rbt->maximum(), std::runtime_error);
    ASSERT_THROW(rbt->minimum(), std::runtime_error);
}