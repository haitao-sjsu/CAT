#include "../CAT.hpp"
#include "addVector.h"


TEST(test_add_vector) 
{
    std::vector<int> v1 = addVector({1, 2, 3}, {4, 5, 6});
    std::vector<int> v2 = {5, 7, 9};
    ASSERT_EQUAL(v1, v2);

    v1 = addVector({1, 2, 3}, {-4, -5, -6});
    v2 = {-3, -3, -3};
    ASSERT_EQUAL(v1, v2);
}