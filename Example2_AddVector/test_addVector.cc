#include "../CAT.h"
using CAT::check_and_report;
using CAT::final_check_and_report;
using CAT::exec;

#include "addVector.h"

void test_add_vector() {
    check_and_report(addVector({1, 2, 3}, {4, 5, 6}), {5, 7, 9});
    check_and_report(addVector({1, 2, 3}, {-4, -5, -6}), {-3, -3, -3});
}

int main(int argc, char *argv[]) {
    exec("test_add_vector", test_add_vector);
    final_check_and_report();
}