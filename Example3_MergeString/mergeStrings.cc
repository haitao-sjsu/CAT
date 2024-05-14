#include <algorithm>

#include "mergeStrings.h"

//<string>
using std::string;
using std::out_of_range;
//<vector>
using std::vector;
//<algorithm>
using std::for_each;
using std::max;

string mergeStrings (const vector<string>& strings) {
  string result;
  string::size_type maxLength = 0;

  for_each (strings.cbegin(), strings.cend(),
            [&maxLength] (const string& s) { maxLength = max(maxLength, s.length()); });
 
  for (int i = 0; i < maxLength; i++)
    for (const string& s : strings) 
      try {
        result += s.at(i);
      } catch (out_of_range e) {}

  return result;
}
