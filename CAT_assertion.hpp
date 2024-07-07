# ifndef _CAT_ASSERTION_HPP_
# define _CAT_ASSERTION_HPP_

#include <cmath>
#include <functional>

#include "CAT_util.hpp"

namespace CAT
{

const double DEFAULT_TOLERANCE = 1e-9;

class Assertion 
{
private:

template<typename T1, typename T2, typename Compare>
static inline void _assert(int line, const T1& result, const T2& expected, Compare cmp) 
{
    if (cmp(result, expected)) 
    {
        ++passNum, ++caseNum;
        simpleOutput();
    } 
    else 
    {
        ++failNum, ++caseNum;
        CAT::line = line;
        verboseOutput(result, expected);
    }
}

public:

template<typename T1, typename T2=T1>
static inline void assert_equal(int line, const T1 &result, const T2 &expected) 
{
    _assert(line, result, expected, std::equal_to<T1>());
}

static inline void assert_equal(int line, double result, double expected, double tolerance=DEFAULT_TOLERANCE) 
{
    _assert(line, result, expected, [=](double a, double b) { return std::abs(a - b) < tolerance; });
}

static inline void assert_true( int line, bool result) 
{
    _assert(line, result, true, std::equal_to<bool>());
}

static inline void assert_false(int line, bool result) 
{
    _assert(line, result, false, std::equal_to<bool>());
}

}; // class Assertion

} // namespace CAT

# endif // _CAT_ASSERTION_HPP_
