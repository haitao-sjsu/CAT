#include "../CAT.hpp"
using CAT::assert_equal;
using CAT::final_stats;
using CAT::exec;

#include "add.h"

void test_add() {
    assert_equal(add(1, 1), 2);
    assert_equal(add(1, -1), 0);
    assert_equal(add(-1, -1) == -2, true);
}

int main(int argc, char *argv[]) {
    exec("test_add", test_add);
    final_stats();
}