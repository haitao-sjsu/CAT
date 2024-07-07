#ifndef _TESTFRAME_HPP_
#define _TESTFRAME_HPP_

#include "CAT_util.hpp"
#include "CAT_assertion.hpp"

namespace CAT 
{

#define TEST(name)                                \
    void name();                                  \
    CAT::TestSuite name##Instance(#name, name);   \
    void name()

#define ASSERT_EQUAL(result, expected)           CAT::Assertion::assert_equal(__LINE__, result, expected)
#define ASSERT_NEAR(result, expected, tolerance) CAT::Assertion::assert_equal(__LINE__, result, expected, tolerance)
#define ASSERT_TRUE(result)                      CAT::Assertion::assert_true(__LINE__, result)
#define ASSERT_FALSE(result)                     CAT::Assertion::assert_false(__LINE__, result)

class TestSuite
{
public:
    TestSuite(const char *func_name, void (*func_body)()) : 
        m_name(func_name),
        m_func(func_body)
    {
        suites.push_back(this);
    }

    void run()
    {
        caseNum = 0;
        std::cout << "TestSuite: " << m_name << '\n';
        m_func();
        std::cout << '\n';
    }
private:
    const char *m_name;
    void (*m_func)();
};

} // namespace CAT


int main(int argc, char *argv[]) 
{
    for (CAT::TestSuite *suite : CAT::suites) 
    {
        suite->run();
    }
    CAT::summary();
    return 0;
}

#endif