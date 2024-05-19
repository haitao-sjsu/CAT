# Instructions
This example demonstrates a slightly advanced use of CAT library. You should read Example 1 if you haven't.

## Files explained
Very similar to Example 1. Again, you should read Example 1 if you haven't.

## Codes explained
The key code line is as below:
```c++
assert_equal(addVector({1, 2, 3}, {4, 5, 6}), {5, 7, 9});
assert_equal(addVector({1, 2, 3}, {-4, -5, -6}), {-3, -3, -3});
```

We wanna demonstrate that our library could compare two vectors that whether the same or not. However, if we wanna do that, we need to do two things:
1. Make sure the data structure has overload operator==. As for std::vector, STL has done the job for us.
2. Make sure the data structure has overload operator<<. STL does not do that for us, so we implemented it in the library. That's why there are some operator<< functions in the CAT.hpp. You could add your own function to it if you defined your own data structure.

## Suggestions
You could change or add some testing cases to see what will happen, especially for the failed testing cases.