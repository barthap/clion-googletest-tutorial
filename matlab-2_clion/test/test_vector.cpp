#include "gtest/gtest.h"

#include "matlab.hpp"

TEST(MatlabVectorTest, createWithSize) {
    MatVect v(2U);

    ASSERT_EQ(v.size(), 2U);
    EXPECT_EQ(v.getElem(0), 0);
    EXPECT_EQ(v.getElem(1), 0);
}

//my test
TEST(MatlabVectorTest, createFromVector) {
    std::vector<int> v1 { 5, 2};

    MatVect vect(v1);

    ASSERT_EQ(vect.size(), 2);
    EXPECT_EQ(vect.getElem(0), 5);
    EXPECT_EQ(vect.getElem(1), 2);
}

TEST(MatlabVectorTest, add) {
    std::vector<int> v1{ 1, 2 };
    MatVect mv1(v1);
    std::vector<int> v2{ 4, 5 };
    MatVect mv2(v2);

    MatVect mv3 = add_vectors(mv1, mv2);

    ASSERT_EQ(mv3.size(), 2U);
    EXPECT_EQ(mv3.getElem(0), 5);
    EXPECT_EQ(mv3.getElem(1), 7);
}
