# C++ Apprentice Tester(CAT) For Students

## Background
When I studied data structure and algorithms with C++ language in SJSU, 2023 fall, I tried to find some simple c++ testing libraries or frameworks to test my coding assignments. But I feel really frustrated because the so claimed simple testing libraries were so complicated that I had to spend much more time understanding them than finishing my homework. So during that semester I developed a mini c++ testing library(if it could be called a library), and decided to share it.

## Goals
1. Friendly to real beginners. Anyone could begin to use it in 10 minutes, understand it in 30 minutes. Examples and documents are provided. It only has very basic functionality, but enough for university assignments. I do not wanna make it perfect. This is not the goal of this tiny framework.
2. Educational purpose. I hope stduents don't only use this library, but also learn from the code to how to use cpp language to design and solve problem. 

## How to use it in 10 minutes
It is only one header file, in which several functions exist. The most frequently used functions are: 

`void assert_equal(const T1& result, const T2& expected)`: Compare whether result is equal to expected, and report the comparison result. For floating number, we have a slightly different version because of precising.

`summary()`: Output the testing statistics.

`void exec(const std::string& func_name,  void func_body(void))`: Utility function. You could decide whether use it or not. You could go to the example folder to see how to use it.

In you testing code, please add the following code, and there we go.
```c++
#include "CAT.hpp"
using CAT::assert_equal;
using CAT::summary;
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

Some examples are prvoded for further study. Please refer to see more details.

## How to understand it in 30 minutes
The basic idea behind testing is quite straightforwad: You compare the actual result of the function to be tested with the expected result, if they are the same, it would be great; if they are different, report the differences to programmers. After testing all cases, you could report the entire testing statistics. `assert_equal()` function implements the comparison process, and `summary()` function implements the final report. Besides, there are several utility functions:

`simpleOutput()` and `verboseOutput()`: As name indicated, such two functions are used for output. if testing is passed, then simpleOutput, otherwise, we need to verboseOutput.

`operator<<()`: Those utility functions are used for ouputing some often used data structures when the verboseOutput is needed. For example, you have two vectors to be compared, and when the results are different, then we need to output the vectors. But the STL does not provide a default output method, so we have to define it ourselves. 

It should be noted that If you defined your own classes or data structures and wanna compare them, you need to overload operator== and operator<< in your class.

You could refer to design and implementation document for further study.

## Contacts
If you have any ideas, please contact me haitao.long AT sjsu.edu.