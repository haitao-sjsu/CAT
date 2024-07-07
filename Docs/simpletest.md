# simpletest

## Design Overview
- Not header file only, the project included one header file and one cpp file.
- It provided filter mechanism, group filter and name filter.
- The project provide three output mode: silent, normal and verbose.
- The project provide two integer output mode: default and Hexadecimal.
- The key class of this project is class `TestFixture`. It provides functionalities:
    - testcase registration
    - test result restoration and output
    - loop for every testcase
    - user option restoration (output mode and integer output mode)
    - Yes, I think this class could be refactored to several classes for better design.

## Code Walkthrough
1. Every `TEST` macro will generate a struct inherited from `TestFixture` and a corresponding instance. The registration will be done in its constructor, and the test code will be done in `RunTest()` method.

2. The execution stack for a simple testcase would be:
    - `main()`. The entry point of the code, and the wrapper function of `TestFixture::ExecuteAllTests()`.
    - `TestFixture::ExecuteAllTests()`. Check the filter and use a for loop to execute all the testcases.
    - `locExecuteTest()`. Not a method in `TestFixture`, but a function. To do the time measurement and the output.
    - `TestFixture::ExecuteTest()`. Initialize some variables.
    - `TestFixture::RunTest()`. Run the test and record the result including error messages.

## Code Explanation （Important classes, functions and macros）
- `class TestFixture`
    - The base class of all test classes. 

    - `TestFixture()`. testcase registration.
    - `static TestFixture* ourFirstTest, ourLastTest`. The pointer to the first and last TestFixture.
    - `TestFixture* myNextTest`. the pointer of the linked list pointing to the next testcase.

    - `ExecuteAllTests()`. All tests are run here. The for loop is:
        ```c++
        for (auto i = TestFixture::GetFirstTest(); i; i = i->GetNextTest())
        ```
    - `ExecuteTest()`. Run one single test.

    - `GetCurrentTest()`. This function is used by utility function `TypeToString()` to get the print method
    - `static thread_local TestFixture* ourCurrentTest`. Used in `GetCurrentTest()` to store the running `TestFixture` pointer.

    - `TestName()` and `TestGroup()`. Pure virtual method. The subclass must provide the names.
    - `RunTest()`. Pure virtual method. The subclass must provide the concrete method.
    - `TestStrings()`. You could see this as a specific version of `RunTest()` for string testing.

    - `TestError* myNextError`. In one testcase, there may exist more than one error. So this is the pointer of the linked list pointing to the next error.
    - `char myMessageSpace[MESSAGE_SPACE]`. This is the space to record error message string.
    - `GetFirstError()` and `GetLastError()`. To identify the beginning and the ending of the error message lists.
    - `LogMessage()`. You could view this method as the `snprintf()` version of class `TestFixture`.
    
- `struct TestError`. A linked list used for storing the error messages in one testcase. 

- `struct TempString`. It's a wrapper struct of char*. I guess the reason that the project does not use std::string is to accelerate the compiling time.

- `function TypeToString()`. Utility function that convert all types into `struct TempString`.

- `macro DEFINE_TEST_FULL`. The macro that generate the test struct and an instance.

- `macro TEST_OPERATOR`. The macro that generate the code in `RunTest()`.

## How to Section
- Q: How to do the registration?
  A: The registration process in `TestFixture` constructor is done by adding to a linked list. Related functions and data structure include:
        - `static TestFixture* TestFixture::ourFirstTest`
        - `static TestFixture* TestFixture::ourLastTest`
        - `TestFixture::TestFixture()`

- Q: How to measure the running time
  A: In `locExecuteTest()`, we used standard library function `clock()` to measure the time.

- Q: How to record file name, line number, etc
  A: `__FILE__` and `__LINE__` are used in macro `TEST_ERROR_PREFIX_`.

- Q: How to filter group and name
  A: We could set group and name filter in the parameter list of `TestFixture::ExecuteTestGroup()` and `TestFixture::ExecuteAllTests()`. The filter routine is implemented in `TestFixture::ExecuteAllTests()`.

- Q: How to implement three output mode
  A: The related routine is in `TestFixture::ExecuteAllTests()` and `locExecuteTest()`.
