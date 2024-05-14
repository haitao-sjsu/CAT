/*
Implementation Overview

Now lets talk about the implementation. About the instruction of data structure, 
you could refer to the last section of BigInt.h.

Since we use the data representation which is compliant to the algrebra, the implementation
is quite simple. If you want to add or sub two BigInt, you just do an element wise 
add or sub operation in these two vectors. For example, if you want to calculate 23 - 789,
you just do [3, 2] - [9, 8, 7] = [3-9, 2-8, 0-7] = [-6, -6, -7], which means the result 
would be -766.

If you want to do the multiply operation, it is a little complcated. We need to back to the
elementary school knowledge to see how to have that work done. For example, if we want to 
calculate 12 * 12, we basically do

      1   2
   *  1   2
   ----------
      2   4
  1   2
  -----------
  1   4   4

In our data representation, it should be written as:
[2, 1] * [2, 1] = [2 * 2, 1 * 2 + 2 * 1, 1 * 1] = [4, 4, 1]

That is why, in our implementation, the key process is just like this:

for (opd1[i] in opd1)
  for (opd2[j] in opd2)
    result[i + j] += opd1[i] * opd2[j];

However, there is one key problem need to be solved. The data representation of the results
is often in a what I call illegal status. For example, when you do 55 + 55:

[5, 5] + [5, 5] = [10, 10]. 

The result is right since [10, 10] just means 10 + 10 * 10 = 110, but such representation 
is illegal since every digit should be between -9 and 9.

Another example is when you do 19- 28:

[9, 1] - [8, 2] = [1, -1]

The result is right since [1, -1] just means 1 * 1 + (-1) * 10 = -9. But such representation
is still illegal since every digit should have the same sign. They should be simutaneously
non-negative or non-positive.

Yet another tricky exmaple is when you do 999 - 998:

[9, 9, 9] - [8, 9, 9] = [1, 0, 0]

Here we need to delete the tailing 0, otherwise it is still illegal.

Now we need to transform the illegal status to an illegal status, which I name it as "legalize"
function. The name is kind of embarrassing due to my poor vocab. If you have a better name,
pleas let me know. BTW, Naming is kind of pain to me.

Now let's dive into details.
*/

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <iterator>

#include "BigInt.h"

//<vector>
using std::vector;
//<string>
using std::string;
using std::to_string;
//<iostream>
using std::istream;
using std::ostream;
//<iterator>
using std::ostream_iterator;
//<algorithm>
using std::copy;
using std::transform;
using std::max;
//<functional>
using std::plus;
//<stdexcept>
using std::runtime_error;

//well, I am a lazy person.
using Vec = std::vector<int>;

//error message string
const std::string BigInt::csCheckErrorEmpty = "Runetime Error in BigInt::check. rdata is empty.";
const std::string BigInt::csCheckErrorTailingZero = "Runetime Error in BigInt::check. tailing zeros exists.";
const std::string BigInt::csCheckErrorInvalidDigitOutOfRange = "Runetime Error in BigInt::check. digit >= 10 or <= -10";
const std::string BigInt::csCheckErrorInvalideDigitMixed = "Runetime Error in BigInt::check. the digits are simutaneously non-negative or non-positive";
const std::string BigInt::csStringConstructorErrorIllegalChar ="Runtime Error in constructor. Illegal char: ";
const std::string BigInt::csStringConstructorErrorOnlyNegativeSign = "Runtime Error in constructor. only one negative sign is illegal";
const std::string BigInt::csIntConstructorIllegalInt = "Runtime Error in Constructor: illegal int: ";
/*
Sec1: Special member functions including two constructors required by the assignment.
The implementation is quite straightforwad.
Step 0: We deal with the margin situation, when para is an empty string
Step 1: check it is a legal string that chould represent an integer.
Step 2: transform every charactor to integer and store it into the vector.
*/
BigInt::BigInt(const string& para) {
  //Step 0: We deal with the margin situation, when para is an empty string
  if (para == "") {
    //In fact, we should not use other constructor in one constructor
    //But it works. Anyone knows why?
    BigInt();
    return;
  }
  
  int sign = 1;
  char firstChar = para[0];
  //Thanks to C++, we do not need to write many tiny functions anymore
  auto is_first_char_legal = [](char c) {
    return c == '-' || ('0' <= c && c <= '9');
  };
  auto is_char_legal = [](char c) {
    return '0' <= c && c <= '9';
  };
 
  //Step 1: we deal with the first character
  if (!is_first_char_legal(firstChar))
    throw runtime_error(csStringConstructorErrorIllegalChar + string(1, firstChar));
  else if (firstChar == '-' && para.size() == 1)
    throw runtime_error(csStringConstructorErrorOnlyNegativeSign);
  else if (firstChar == '-')
    sign = -1;
  else
    rdata.push_back (firstChar - '0');

  //Step 2: transform other charactors to integer and store it into the vector.
  for (const char& c : para.substr(1)) {
    if (!is_char_legal(c))
      throw runtime_error(csStringConstructorErrorIllegalChar + string(1, c));
    //We should be cautious that we use the reverse order storage. So we need
    //to use the insert() member function other than push_back().
    //For examle, "-123" should be transformed as [-3, -2, -1]
    rdata.insert(rdata.begin(), sign * (c - '0'));
  }
  //We should be careful since it may be possible that there are some unnecessary
  //zeros in the string.
  delete_tailing_zeros();
  
  //Make sure that the data representation is legal.
  check();
}

//The default constructor will generate the default value BigInt(0),
//just as other default value of C++.
BigInt::BigInt() :
  BigInt(0) {}

//Well, I am a lazy person.
BigInt::BigInt(int para) 
  : BigInt(to_string(para)){}

//The belowing process is very similar with the constructor BigInt(const string& para).
//You can refer to there.
BigInt::BigInt (const Vec& input) {
  if (input.empty()) {
    BigInt();
    return;
  }

  int sign = 1;
  int first = input.front();
  auto is_first_digit_legal = [](int digit) {
    return -10 < digit && digit < 10;
  };
  auto is_digit_legal = [](int digit) {
    return 0 <= digit && digit < 10;
  };

  if (!is_first_digit_legal(first))
    throw runtime_error(csIntConstructorIllegalInt + to_string(first));
  else if (first < 0)
    sign = -1;
  rdata.push_back(first);

  for (auto iter = input.cbegin() + 1; iter != input.cend(); iter++) {
    int digit = *iter;
    if (!is_digit_legal(digit))
      throw runtime_error(csIntConstructorIllegalInt + to_string(digit));
    rdata.insert(rdata.begin(), sign * digit);
  }
  delete_tailing_zeros();
  
  check();
}

//I am a lazy person, again
BigInt::BigInt (const std::vector<char>& para) : 
  BigInt(to_str(para)) {}

BigInt::BigInt (const char para[], unsigned int size) :
  BigInt(to_str(para, size)) {}

/*
Sec2: input and output support. we could input and output BigInt just like int types.
The implementation is quite straightforward. You can refer to the code.
*/
ostream& operator<< (ostream& out, const BigInt& obj) {
  //It is a non-negative number or negative number?
  //Why use the last digit(i.e., the highest digit) to determine?
  //Because the other digits may be zeros.
  switch (obj.rdata.back() >= 0 ? 1 : -1) {
    case 1:
    //Thanks to STL algorithm, we have the fancy way to output. For example,
    //[3 ,2, 1] should be output as 123.
    copy(obj.rdata.crbegin(), obj.rdata.crend(),
         ostream_iterator<int>(out, ""));
    break;
    case -1:
    //If it is a negative number, first we output the negative sign.
    out <<'-';
    //Then we output the number with negative sign eliminated in reverse order.
    for (int i = obj.rdata.size() - 1; i >= 0; i--)
      out << -obj.rdata[i];
  }
  return out;
}

//Honestly speaking, I do not have much experience on input.
//If I am wrong, pls tell me
istream& operator>> (istream& in, BigInt& obj) {
  string input;
  
  in >> input;
  obj = BigInt(input);

  return in;
}

/*
Sec3: arithmetic operators support.
In the overview part, I have explained the process.
Talk is cheap, now show me the code.
*/
BigInt BigInt::operator+ (const BigInt& opd) const {
  BigInt result;
  Vec lhs = this->rdata, rhs = opd.rdata;
  int size = max(lhs.size(), rhs.size());

  //First, we assure lhs and rhs has the same size
  lhs.resize(size, 0);
  rhs.resize(size, 0);
  //Second, We apply for enough spaces to store the result.
  result.rdata.resize(size + 1, 0);

  //Third, we use a fancy method to do element wise addition operation in two vectors
  //For example, [3, 2, 1] + [5, 4] = [3 + 5, 2 + 4, 1 + 0]
  transform(lhs.cbegin(), lhs.cend(),
            rhs.cbegin(),
            result.rdata.begin(),
            plus<int>());
  //illegal -> legal
  result.legalize();
  
  return result;
}

//such operator supports operation like BigInt a; BigInt b = -a;
BigInt BigInt::operator- (void) const {
  BigInt result;
  result.rdata.resize(this->rdata.size());

  //A fancy way to do operation like
  //[3, 2, 1] -> [-3, -2, -1]
  transform(this->rdata.cbegin(), this->rdata.cend(),
            result.rdata.begin(),
            [](int opd) {return -opd;});
  //It should be noted that we do not need the legalize() here.
  //If (*this) is legal, then -(*this) is also legal.
  
  return result;
}

//I am a lazy person, so it is a lazy implementation.
// a - b = a + (-b)
BigInt BigInt::operator- (const BigInt& opd) const {
  return (*this) + (-opd);
}

BigInt BigInt::operator* (const BigInt& opd) const {
  //We apply for enough spaces to store the result.
  //According to the multiply rules, the space we need is 
  //this->rdata.size() + opd.rdata.size()
  BigInt result;
  result.rdata.resize(this->rdata.size() + opd.rdata.size(), 0);

  //key process, as I explained in overview
  for (size_t i = 0; i < this->rdata.size(); i++)
    for (size_t j = 0; j < opd.rdata.size(); j++)
      result.rdata[i + j] += this->rdata[i] * opd.rdata[j];
  //illegal -> legal
  result.legalize();

  return result;
}

/*
Sec4: logical operators support.
*/
bool BigInt::operator== (const BigInt& opd) const {
  //thanks to STL algorithm, the vector template overload the == operator
  //what we need to do is use STL.
  return this->rdata == opd.rdata;
}

bool BigInt::operator!= (const BigInt& opd) const {
  return ! (*this == opd);
}

bool BigInt::operator> (const BigInt& opd) const {
  int size = max(this->rdata.size(), opd.rdata.size());
  Vec lhs = this->rdata, rhs = opd.rdata;

  lhs.resize(size, 0);
  rhs.resize(size, 0);
  for (int i = size - 1; i >= 0; i--) {
    if (lhs[i] > rhs[i])
      return true;
    else if (lhs[i] < rhs[i])
      return false;
  }
  return false;
}

bool BigInt::operator>= (const BigInt& opd) const {
  return (*this > opd) || (*this == opd);
}

bool BigInt::operator< (const BigInt& opd) const {
  return !(*this >= opd);
}

bool BigInt::operator<= (const BigInt& opd) const {
  return !(*this > opd);
}

bool BigInt::operator! (void) const {
  return *this == 0;
}

/*
Sec5: increment and decrement operators support.
*/
BigInt BigInt::operator++(void) {
  *this = *this + 1;
  return *this;
}

BigInt BigInt::operator++(int) {
  BigInt old = *this;
  *this = *this + 1;
  return old;
}

BigInt BigInt::operator--(void) {
  *this = *this - 1;
  return *this;
}

BigInt BigInt::operator--(int) {
  BigInt old = *this;
  *this = *this - 1;
  return old;
}

/*
Sec6: helper functions to handle operations beteween BigInt and int
*/
BigInt operator+ (const BigInt& lhs, int rhs) {
  return lhs + BigInt(rhs);
}

BigInt operator+ (int lhs, const BigInt& rhs) {
  return BigInt(lhs) + rhs;
}

BigInt operator- (const BigInt& lhs, int rhs) {
  return lhs - BigInt(rhs);
}

BigInt operator- (int lhs, const BigInt& rhs) {
  return BigInt(lhs) - rhs;
}

BigInt operator* (const BigInt& lhs, int rhs) {
  return lhs * BigInt(rhs);
}

BigInt operator* (int lhs, const BigInt& rhs) {
  return BigInt(lhs) * rhs;
}

bool operator== (const BigInt& lhs, int rhs) {
  return lhs == BigInt(rhs);
}

bool operator== (int lhs, const BigInt& rhs) {
  return BigInt(lhs) == rhs;
}

bool operator!= (const BigInt& lhs, int rhs) {
  return lhs != BigInt(rhs);
}

bool operator!= (int lhs, const BigInt& rhs) {
  return BigInt(lhs) != rhs;
}

bool operator> (const BigInt& lhs, int rhs) {
  return lhs > BigInt(rhs);
}

bool operator> (int lhs, const BigInt& rhs) {
  return BigInt(lhs) > rhs;
}

bool operator>= (const BigInt& lhs, int rhs) {
  return lhs >= BigInt(rhs);
}

bool operator>= (int lhs, const BigInt& rhs) {
  return BigInt(lhs) >= rhs;
}

bool operator< (const BigInt& lhs, int rhs) {
  return lhs < BigInt(rhs);
}

bool operator< (int lhs, const BigInt& rhs) {
  return BigInt(lhs) < rhs;
}

bool operator<= (const BigInt& lhs, int rhs) {
  return lhs <= BigInt(rhs);
}

bool operator<= (int lhs, const BigInt& rhs) {
  return BigInt(lhs) <= rhs;
}


/*
Sec7: private helper function to legalize a BigInt.

Ok. Now lets talk about how to legalize a BigInt. As you see below, 
there are 5 steps:

Step1: do the overflow process.We do not overflow DURING the calculation just as kids do, 
instead we do the overflow process AFTER the calculation.

Step2: delete the tailing zeros that may be generated by Step1.

Step3: do a process which I called standarize. That process will sure that
all the numbers are non-negative or non-positive. Sorry for my horrible naming again.

Step4: delete the tailing zeors that may be generated by Step3.

Step5: inner check that the BigInt is now legal.
*/
void BigInt::legalize(void) {
  //It should be noted that before overflow(), we should not delete tailing zeros,
  //those zeros are used for overflow, we should not delete them.
  //Otherwise, you may have miserable failure.
  
  //Step 1
  overflow();
  //Step 2
  delete_tailing_zeros();
  //Step 3
  standardize();
  //Step 4
  delete_tailing_zeros();
  //Step 5
  check();
}

//do the overflow process. 
//For example, [12, 13] -> [2, 14] -> [2, 4, 1]
//It should be noted that, the function assume that the vector has enough space
//aka., we do not increase or decrease the size of the vector
//If you do not set enough space before hand, you may have miserable failure.
void BigInt::overflow(void) {
  for (size_t i = 0; i < rdata.size(); i++) {
    int num = rdata[i];
    if (num >= 10 || num <= -10) {
      rdata[i] = num % 10;
      rdata[i + 1] += num / 10;
    } 
  }
}

//standardize process will sure that
//all the numbers are non-negative or non-positive.
void BigInt::standardize(void) {
  switch (rdata.back() > 0 ? 1 : -1) {
  case 1:
  for (size_t i = 0; i < rdata.size(); i++) 
      if (rdata[i] < 0) {
        rdata[i] += 10;
        rdata[i + 1] -= 1;
      }
  break;
  case -1:
  for (size_t i = 0; i < rdata.size(); i++) 
      if (rdata[i] > 0) {
        rdata[i] -= 10;
        rdata[i + 1] += 1;
      }
  }
}

//delete the tailing zeros
//For exmaple, [1, 2, 0, 0] -> [1, 2]
//We need to be very careful, because if the BigInt is 0, then
//[0, 0, 0] ->[0]
//You could not delete all the zeros!
void BigInt::delete_tailing_zeros(void) {
  while (rdata.size() >= 2 && rdata.back() == 0)
    rdata.pop_back();
}

//inner check
//make sure that (*this) is legal. Here the definition of "legal" is:
//1) the representation could not be empty
//2) tailing zeros does not exist.
//3) all the digits are between -9 and 9
//4) all the digits are simutaneously non-negative or non-positive
void BigInt::check(void) const {
  if (rdata.empty())
    throw runtime_error(csCheckErrorEmpty);
  if (rdata.size() > 1 && rdata.back() == 0)
    throw runtime_error(csCheckErrorTailingZero);

  int sign = rdata.back() > 0 ? 1 : -1;
  for (const int& i : rdata) { 
    if (i >= 10 || i <= -10)
      throw runtime_error(csCheckErrorInvalidDigitOutOfRange);
    if (sign * i < 0)
      throw runtime_error(csCheckErrorInvalideDigitMixed);
  }
}

string BigInt::to_str(const std::vector<char>& para) {
  string result;
  for (const char& c : para)
    result += c;
  return result;
}

string BigInt::to_str(const char para[], unsigned int size) {
  string result;
  for (size_t i = 0 ; i < size; i++)
    result += para[i];
  return result;
}
