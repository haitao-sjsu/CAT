#include "../CAT.hpp"

#include "add.h"

TEST(add) 
{
    ASSERT_EQUAL(add(1, 1), -2);
    ASSERT_NEAR(add(1.5, 1.5), 3.001, 0.01);
    ASSERT_TRUE(add(-1, -1) == -2);
}