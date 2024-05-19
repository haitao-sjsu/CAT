#include "../CAT.hpp"
using CAT::assert_equal;
using CAT::final_stats;
using CAT::exec;

#include "addVector.h"

void test_add_vector() {
    assert_equal(addVector({1, 2, 3}, {4, 5, 6}), {5, 7, 9});
    assert_equal(addVector({1, 2, 3}, {-4, -5, -6}), {-3, -3, -3});
}

int main(int argc, char *argv[]) {
    exec("test_add_vector", test_add_vector);
    final_stats();
}