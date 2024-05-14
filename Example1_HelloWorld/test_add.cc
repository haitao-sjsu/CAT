#include "../CAT.h"
using CAT::check_and_report;
using CAT::final_check_and_report;
using CAT::exec;

#include "add.h"

void test_add() {
    check_and_report(add(1, 1), 2);
    check_and_report(add(1, -1), 0);
    check_and_report(add(-1, -1) == -2, true);
}

int main(int argc, char *argv[]) {
    exec("test_add", test_add);
    final_check_and_report();
}