#include "addVector.h"

#include <vector>
using std::vector;

vector<int> addVector(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    for (size_t i = 0; i < a.size(); i++) {
        result.push_back(a[i] + b[i]);
    }
    return result;
}