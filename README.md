# C++ Apprentice Tester(CAT) For Students

## Background
When I studied data structure and algorithms with C++ language in SJSU, 2023 fall, I tried to find some simple c++ testing libraries or frameworks to test my coding assignments. But I feel really frustrated because the so claimed simple testing libraries were so complicated that I had to spend much more time understanding them than finishing my homework. So during that semester I developed a mini c++ testing library(if it could be called a library), and decided to share it.

## Goals
1. Friendly to real beginners. Anyone could begin to use it in 10 minutes, understand it in 30 minutes. Examples and documents are provided.
2. It only has very basic functionality, but enough for university assignments. I do not wanna make it perfect. This is not the goal of this tiny framework.

## How to use it in 10 minutes
It is only one header file, in which several functions exist. The most frequently used functions are: 

`void assert_equal(const T1& result, const T2& expected)`: Compare whether result is equal to expected, and report the comparison result. For floating number, we have a slightly different version because of precising.

`final_stats()`: Output the testing statistics.

`void exec(const std::string& func_name,  void func_body(void))`: Utility function. You could decide whether use it or not. You could go to the example folder to see how to use it.

In you testing code, please add the following code, and there we go.
```c++
#include "CAT.hpp"
using CAT::assert_equal;
using CAT::final_stats;
using CAT::exec;
```

For example, you have a function add() to test:
```c++
int add(int a, int b);
```

You could write the following testing code:
```c++
assert_equal(add(1, 1) 2);
assert_equal(add(-1, -1) == -2, true);
```

Please refer to Example1_Add to see more details.

## How to understand it in 30 minutes
The basic idea behind testing is quite straightforwad: You compare the actual result of the function to be tested with the expected result, if they are the same, it would be great; if they are different, report the differences to programmers. After testing all cases, you could report the entire testing statistics. `assert_equal()` function implements the comparison process, and `final_stats()` function implements the final report. Besides, there are several utility functions:

`simpleOutput()` and `verboseOutput()`: As name indicated, such two functions are used for output. if testing is passed, then simpleOutput, otherwise, we need to verboseOutput.

`operator<<()`: Those utility functions are used for ouputing some often used data structures when the verboseOutput is needed. For example, you have two vectors to be compared, and when the results are different, then we need to output the vectors. But the STL does not provide a default output method, so we have to define it ourselves. 

It should be noted that If you defined your own classes or data structures and wanna compare them, you need to overload operator== and operator<< in your class.

## Implementation Discussions
We use the following c++ features to build it:
- following c++ 11 standard. I think it should cover most university requirements.
- using c++ templates not too heavily. I know some guys hate c++ templates because the error messages output by compiler are disgusting. So we use it in moderation.
- We use namespace to avoid name confliction.
- We used some non standard colorful characters on the terminal. I think colorful output is a good idea to enhance readability.

We do NOT use the following techniques:
- c++ macros. I am exhausted in macros. I hate that.
- make, cmake or any building tools. I do not want to spend time learning other tools. Afterall, it is for real beginners.

Some techniques that need to be discussed:
- Some testing frameworks use registration mechanisim. I do not think it is needed for simple tasks.


## Some other testing frameworks
There are some popular c++ framework for references. The information is provided by Gemini. By the way, I have no experience about them.

- Catch2: is a modern, single-header library known for its ease of use and expressive syntax. It's a great choice for students due to its simplicity and clear documentation.

- Doctest: is another beginner-friendly option with a similar single-header design and focus on readability. It's known for its fast compilation times, making it ideal for rapid feedback cycles.

- Google Test (gtest): is a widely used framework from Google. It offers a rich set of features including support for various test types (unit, death tests, etc.), advanced assertions, and easy test discovery. While powerful, it might have a slightly steeper learning curve for beginners.

- Boost.Test: is a mature framework part of the Boost C++ Libraries. It provides extensive functionality including test fixtures, test registration macros, and support for different test runners. It offers a good balance of features and complexity.

- simpletest: A super simple framwork for implementing Unit Tests
Link: https://github.com/kudaba/simpletest

- Unit Test Framework: A lightweight, easy to use, C++11 unit testing framework implemented in a single .hpp file.
Link: https://github.com/eecs280staff/unit_test_framework/

## Contacts
If you have any ideas, please contact me haitao.long AT sjsu.edu.