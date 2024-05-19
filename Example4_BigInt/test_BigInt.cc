#include "BigInt.h"

#include "../CAT.hpp"
using CAT::assert_equal;
using CAT::final_stats;
using CAT::exec;

#include <vector>
using std::vector;
#include <tuple>
using std::tuple;
using std::get;
#include <string>
using std::string;

void test_addition() {
{
  vector<tuple<int, int, int>> cases = {
    {1, 2, 1 + 2},
    {9, 999, 9 + 999},
    {-99, -90, -99 + (-90)}
  };

  for (const auto& c : cases) {
    int opd1 = get<0>(c);
    int opd2 = get<1>(c);
    int expected = get<2>(c);
    assert_equal(BigInt(opd1) + BigInt(opd2), BigInt(expected));
  }
}
{
  vector<tuple<string, string, string>> cases {
    {
      "123456789123456789",
      "123456789123456789",
      "246913578246913578",
    },
    {
      "123456789012345678901234567890",
      "-987654321098765432109876543210",
      "-864197532086419753208641975320",
    },
  };
  for (const auto& c : cases) {
    string opd1 = get<0>(c);
    string opd2 = get<1>(c);
    string expected = get<2>(c);
    assert_equal(BigInt(opd1) + BigInt(opd2), BigInt(expected));
  }
}
}

#define EXEC(test) exec(#test, test)

int main(int argc, char *argv[]) {
    EXEC(test_addition);
    final_stats();
}