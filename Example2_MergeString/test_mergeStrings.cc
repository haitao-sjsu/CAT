#include "../CAT.h"
using CAT::check_and_report;
using CAT::final_check_and_report;
using CAT::exec;

#include "mergeStrings.h"

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <tuple>
using std::tuple;
using std::get;

void test_simple() {
    check_and_report(mergeStrings({"ab", "cd", "ef"}), "acebdf");
}

void test_group() {
    vector<tuple<vector<string>, string>> cases {
        {
            {"ab", "cd", "ef"},
            "acebdf"
        },
        {
            {"ab", "cd", "ef", "g"},
            "acegbdf"
        },
        {
            {"ab", "cd", "ef", "g", "h"},
            "aceghbdf"
        }
    };
    for (auto& c : cases) {
        const auto& input = get<0>(c);
        const auto& expected = get<1>(c);
        check_and_report(mergeStrings(input), expected);
    }
}

void test_margin() {
    vector<tuple<vector<string>, string>> cases {
        {
            {"abc", "",},
            "abc"
        },
        {
            {"", "abc",},
            "abc"
        },
        {
            {"", "",},
            ""
        }
    };
    for (auto& c : cases) {
        const auto& input = get<0>(c);
        const auto& expected = get<1>(c);
        check_and_report(mergeStrings(input), expected);
    }
}

#define EXEC(test) exec(#test, test)

int main(int argc, char *argv[]) {
    EXEC(test_simple);
    EXEC(test_group);
    EXEC(test_margin);
    final_check_and_report();
}