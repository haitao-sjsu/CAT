#ifndef _CAT_UTIL_HPP_
#define _CAT_UTIL_HPP_

#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <forward_list>

namespace CAT
{

using std::ostream;

template<typename T>
ostream& operator<< (ostream& os, const std::vector<T>& v) 
{
    for (const T& item : v)
        os << item << ", ";
    os << "end";
    return os;
}

template<typename T1, typename T2>
ostream& operator<< (ostream& os, const std::pair<T1, T2>& p) 
{
    os << p.first << ", " << p.second << "\n";
    return os;
}

template<typename T>
ostream& operator<< (ostream& os, const std::stack<T>& cstk) 
{
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
ostream& operator<< (ostream& os, const std::queue<T>& cqueue) 
{
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
ostream& operator<< (ostream& os, const std::forward_list<T>& clist) 
{
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

int caseNumTotal = 0;
int caseNum = 0;
int passNum = 0;
int failNum = 0;
int line = 0;

class TestSuite;
std::vector <TestSuite *> suites;

void simpleOutput() 
{
    std::cout << "Testcase #" << caseNum << " " << sPassed << "\n";
}

template<typename T1, typename T2=T1>
void verboseOutput(const T1& result, const T2& expected) 
{
    std::cout << std::boolalpha
              << "TestCase #" << caseNum << " " << sFailed 
              << " Line: " << line << "\n"
              << "result: " << result << "\n"
              << "expected: " << expected << "\n\n";
}

void summary() 
{
    std::cout << "\nTotal " << passNum + failNum << " testcase(s). " << "\n"
            << sPassed << " " << passNum << "; " << sFailed << " " << failNum << '\n'
            << (failNum == 0 ? sFinalPassed : sFinalFailed) << "\n\n";
}


} // namespace CAT

#endif // _CAT_UTIL_HPP_