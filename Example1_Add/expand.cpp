int add(int a, int b);
double add(double a, double b);
# 4 "test_add.cc" 2

void add(); 
CAT::TestSuite addInstance("add", add); 
void add()
{
    CAT::Assertion::assert_equal(7, add(1, 1), -2);
    CAT::Assertion::assert_equal(8, add(1.5, 1.5), 3.001, 0.01);
    CAT::Assertion::assert_true(9, add(-1, -1) == -2);
}
