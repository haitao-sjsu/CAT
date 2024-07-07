#include "../CAT.hpp"

#include "mergeStrings.h"

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <tuple>
using std::tuple;
using std::get;

TEST(simple)
{
    ASSERT_EQUAL(mergeStrings({"ab", "cd", "ef"}), "acebdf");
}

TEST(group)
{
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
        ASSERT_EQUAL(mergeStrings(input), expected);
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
        ASSERT_EQUAL(mergeStrings(input), expected);
    }
}