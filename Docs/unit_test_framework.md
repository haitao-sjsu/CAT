# unit_test_framework

## Design Overview
- Header only project. No cpp file.
- There are three kernel classes in this project:
    - `Assertions` class: responsible for running every assertion.
    - `TestCase` class: a wrapper class of `Assertions`.
    - `TestSuite` class: responsible for every test function.
- Command line arguments accepted, including 1) quiet mode output; 2) running designated testcase, etc.
- 
## Code Walkthrough
1. Before into the `main()`, There are `TestRegisterer` to do the registration.

2. The execution stack would be:
    - `main()`: The entry point of the program. The `main()` function could be generated by using `TEST_MAIN()` macro.
    - `TestSuite::get()`: Get the `TestSuite` instance. singeleton design pattern.
    - `TestSuite::run_tests()`: Run every testcase.
    - `Testcase::run()`: Run single testcase.

## Code Explanation （Important classes, functions and macros）
- `Assertions` class: The class responsible for running every assertion. Basically this class does several things: 1. Check whether the types could be compared by using type trait technique; 2. check the assertion; 3. print out error message if failed or exceptions occured.
    - `struct safe_equals` This struct is used for do compiling-time type check and run-time assertion check.
    - `static assert` method family. use `struct safe_equals` to check the assertion and print out error message if needed.

- `TestCase` class: The class responsible for every assertion. Basically, it is a wrapper class of `Assertions`.
    - `run()` method. Run the assertion and print out the result.

- `TestSuite` class: The class responsible for every test function.
    - `run_tests()` method. Run the entire test function that may include more than one case/assertion.
    - `get_test_names_to_run` method. parse the command line and gather all the test function names. Users could desinate which test function to run. And Users may use regex expression if supported.
    - `std::map<std::string, TestCase> tests_` private member data, used for storing every <name, testcase> pair.

- `TEST` macro: To do the registration.

- `ASSERT` macro family: one macro responds to one static method in `Assertions` class.

## How to Section
- Q: How to parse the command line arguments
  A: It is implemented in `TestSuite::get_test_names_to_run()`. The project did not use `getopt()` function to deal with the command line, it just use `strcmp()` function to parse the command line.

- Q: How to implement the `ASSERT_SEQUENCE_EQUAL` macro
  A: It is implemented in `Assertions::assert_sequence_equal()` static method. The routine would be:
        1. compare the lengths of two sequences. If not equal, then output the result;
        2. If equal, then compare each element one by one.
        3. If some element is not euqal, then output the result.

- Q: How to design the output