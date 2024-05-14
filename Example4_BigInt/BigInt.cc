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

bool BigInt::operator== (const BigInt& opd) const {
  //thanks to STL algorithm, the vector template overload the == operator
  //what we need to do is use STL.
  return this->rdata == opd.rdata;
}

/*
private helper function to legalize a BigInt.

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