#ifndef _TESTFRAME_H_
#define _TESTFRAME_H_

#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <queue>
#include <forward_list>
#include <ostream>
#include <iostream>
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

int caseNum = 0;
int passNum = 0;
int failNum = 0;

void simpleOutput() {
    passNum++;
    std::cout << "Testcase #" << ++caseNum << " " << sPassed << "\n";
}

template<typename T1, typename T2 = T1>
void verboseOutput(const T1& result, const T2& expected) {
    failNum++;
    std::cout << std::boolalpha
                << "Testcase #" << ++caseNum << " " << sFailed << "\n"
                << "result: " << result << "\n"
                << "expected: " << expected << "\n";
}

template<typename T1, typename T2 = T1>
void check_and_report(const T1& result, const T2& expected) {
    if (result == expected)
        simpleOutput();
    else
        verboseOutput(result, expected);
}

void check_and_report(double result, double expected) {
    if (std::abs(result - expected) < tolerance)
        simpleOutput();
    else
        verboseOutput(result, expected);
}

void final_check_and_report() {
    std::cout << "\nTotal " << passNum + failNum << " testcase(s). " << "\n"
              << sPassed << " " << passNum << "; " << sFailed << " " << failNum << '\n'
              << (failNum == 0 ? sFinalPassed : sFinalFailed) << "\n\n";
}

void exec(const std::string& func_name,  void func_body(void)) {
  std::cout << func_name << '\n';
  func_body();
  std::cout << '\n';
}

} // namespace CAT
#endif