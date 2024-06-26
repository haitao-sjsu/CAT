#ifndef _TESTFRAME_H_
#define _TESTFRAME_H_

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <forward_list>
#include <ostream>
#include <iostream>
#include <functional>
#include <utility>
#include <cmath>

namespace CAT {

template<typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
    for (const T& item : v)
        os << item << ", ";
    os << "end";
    return os;
}

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, const std::pair<T1, T2>& p) {
    os << p.first << ", " << p.second << "\n";
    return os;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const std::stack<T>& cstk) {
    std::stack<T> stk {cstk};
    os << "Bottom -> ";
    while (!stk.empty()) {
        os << stk.top() << " ";
        stk.pop();
    }
    os << "-> top";
    return os;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const std::queue<T>& cqueue) {
    std::queue<T> queque {cqueue};
    os << "Front <- ";
    while (!queque.empty()) {
        os << queque.front() << " ";
        queque.pop();
    }
    os << "<- End";
    return os;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const std::forward_list<T>& clist) {
    for (const T& item : clist)
        os << item << " -> ";    
    os << "end";

    return os;
}

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";
const std::string sPassed = GREEN + "PASS" + RESET;
const std::string sFailed = RED + "FAIL" + RESET;
const std::string sFinalPassed = GREEN + "Congratulations! All tests passed!" + RESET;
const std::string sFinalFailed = RED + "Some tests failed. Pls check." + RESET;
const double tolerance = 1e-8;

int caseNumTotal = 0;
int caseNum = 0;
int passNum = 0;
int failNum = 0;

void simpleOutput() {
    std::cout << "Testcase #" << caseNum << " " << sPassed << "\n";
}

template<typename T1, typename T2=T1>
void verboseOutput(const T1& result, const T2& expected) {
    std::cout << std::boolalpha
              << "Testcase #" << caseNum << " " << sFailed << "\n"
              << "result: " << result << "\n"
              << "expected: " << expected << "\n";
}

template<typename T1, typename T2=T1, typename Compare>
void _assert(const T1& result, const T2& expected, Compare cmp) {
    ++caseNum, ++caseNumTotal;
    if (cmp(result, expected)) {
        ++passNum;
        simpleOutput();
    } else {
        ++failNum;
        verboseOutput(result, expected);
    }
}

template<typename T1, typename T2=T1>
inline void assert_equal(const T1& result, const T2& expected) {
    _assert(result, expected, std::equal_to<T1>());
}

inline void assert_equal(double result, double expected) {
    auto almost_equal = [](double result, double expected) 
                        {return std::abs(result - expected) < tolerance;};
    _assert(result, expected, almost_equal);
}

template<typename T1, typename T2=T1>
inline void assert_no_equal(const T1& result, const T2& expected) {
    _assert(result, expected, std::not_equal_to<T1>());
}

inline void assert_true(bool result) {
    _assert(result, true, std::equal_to<bool>());
}

inline void assert_false(bool result) {
    _assert(result, false, std::equal_to<bool>());
}

void final_stats() {
    std::cout << "\nTotal " << passNum + failNum << " testcase(s). " << "\n"
              << sPassed << " " << passNum << "; " << sFailed << " " << failNum << '\n'
              << (failNum == 0 ? sFinalPassed : sFinalFailed) << "\n\n";
}

void exec(const std::string& func_name,  void func_body(void)) {
  caseNum = 0;
  std::cout << func_name << '\n';
  func_body();
  std::cout << '\n';
}

} // namespace CAT
#endif