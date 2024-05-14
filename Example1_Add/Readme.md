# Instructions
This example demonstrates the basic use of CAT library.

## Files explained

`add.h`: The function that we want to test. Here is the add() function.

`add.c`: The implementation of add.h

`test_add.cc`: The testing code file.

`build_and_test.sh`: Simple shell script to compile and run the testing. If you do not know what a shell script is, just open it to see what commands included. If you encounter the following error messages:
```
permission denied: ./build_and_test.sh
```
Do not foget to make it executable:
```
chmod +x build_and_test.sh
```

## Codes explained
The key code line is as below:
```c++
check_and_report(add(1, 1), 2);
check_and_report(add(1, -1), 0);
check_and_report(add(-1, -1) == -2, true);
```
Here we build three testing cases, in short:
We expect that add(1, 1) equals to 2;
We expect that add(1, -1) equals to 0;
We expect that add(-1, -1) == -2 is true.

## Output
You should see the following output to the terminal with colors. Isn't it great!
```
test_add
Testcase #1 PASS
Testcase #2 PASS
Testcase #3 PASS


Total 3 testcase(s). 
PASS 3; FAIL 0
Congratulations! All tests passed!
```

## Suggestions
You could change or add some testing cases to see what will happen.