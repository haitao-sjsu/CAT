/*
overview: BigInt.h defines the functionality of the BigInt class. According to the
requirement, BigInt class could handle very large integers that cannot be accommodated 
by standard integer data types. Some programming lanuages provide built-in support to
BigInt, however, in C++, we need to design the class ourselves.

The content of BigInt.h are divided into the following sections. It should be noted that
the mainly implementation detail is explained in cpp file.

Sec1: Special member functions including two constructors required by the assignment.

Sec2: input and output support.

Sec3: arithmetic operators support.

Sec4: logical operators support.

Sec5: increment and decrement operators support.

Sec6: in order to support the operations between BigInt and primitive int, a bunch of 
several helper functions are declared.

Sec7: private members including data and helper functions. In such section, 
I will explain the big int representation in detail.

*/

#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <vector>
#include <string>
#include <iostream>

class BigInt {

public:
  /*
  Sec1: Special member functions including three constructors required by the assignment.
  Our class does not have special data structrue related to resource, hence it does not 
  require resource management. Therefore, we do not need to overload the special member
  functions, such copy assignment and move assignment. Those functions are set to be default.
  */
  BigInt ();
  BigInt (int para);
  BigInt (const std::string& para);
  //three constructors required by assignment. Honestly speaking, I don't think these are good designs.
  BigInt (const std::vector<int>& input); 
  BigInt (const std::vector<char>& para);
  BigInt (const char para[], unsigned int size);

  /*
  Sec2: input and output support. we could input and output BigInt just like int types.
  */
  friend std::ostream& operator<< (std::ostream& out, const BigInt& obj);
  friend std::istream& operator>> (std::istream& in, BigInt& obj);

  /*
  Sec3: arithmetic operators support.
  */
  BigInt operator+ (const BigInt& opd) const;
  //such operator supports operation like BigInt a; BigInt b = -a; 
  BigInt operator- (void) const;
  BigInt operator- (const BigInt& opd) const;
  BigInt operator* (const BigInt& opd) const;

  /*
  Sec4: logical operators support.
  */
  bool operator== (const BigInt& opd) const;
  bool operator!= (const BigInt& opd) const;
  bool operator> (const BigInt& opd) const;
  bool operator>= (const BigInt& opd) const;
  bool operator< (const BigInt& opd) const;
  bool operator<= (const BigInt& opd) const;
  bool operator! (void) const; 
  /*
  Sec5: increment and decrement operators support.
  */
  //pre-increment, like ++i
  //for example, if x is 5,and a = ++x; then a is 6 and x is 6 
  BigInt operator++ (void);
  //post-increment, like i++
  //for example, if x is 5,and a = x++; then a is 5 and x is 6 
  BigInt operator++ (int);
  //pre-decrement, like --i
  //for example, if x is 5,and a = --x; then a is 4 and x is 4 
  BigInt operator-- (void);
  //post-decrement, like i--
  //for example, if x is 5,and a = x--; then a is 5 and x is 4 
  BigInt operator-- (int);
 
  /*
  Sec6: helper functions to handle operations beteween BigInt and int
  */
  friend BigInt operator+ (const BigInt& lhs, int rhs);
  friend BigInt operator+ (int lhs, const BigInt& rhs);
  friend BigInt operator- (const BigInt& lhs, int rhs);
  friend BigInt operator- (int lhs, const BigInt& rhs);
  friend BigInt operator* (const BigInt& lhs, int rhs);
  friend BigInt operator* (int lhs, const BigInt& rhs);
  
  friend bool operator== (const BigInt& lhs, int rhs); 
  friend bool operator== (int lhs, const BigInt&  rhs); 
  friend bool operator!= (const BigInt& lhs, int rhs); 
  friend bool operator!= (int lhs, const BigInt&  rhs); 
  friend bool operator> (const BigInt& lhs, int rhs); 
  friend bool operator> (int lhs, const BigInt& rhs); 
  friend bool operator>= (const BigInt& lhs, int rhs); 
  friend bool operator>= (int lhs, const BigInt&  rhs); 
  friend bool operator< (const BigInt& lhs, int rhs); 
  friend bool operator< (int lhs, const BigInt&  rhs); 
  friend bool operator<= (const BigInt& lhs, int rhs); 
  friend bool operator<= (int lhs, const BigInt& rhs); 
 
private:
  /*
  Sec7: private members including data and helper functions.
  
  About the data representation, we have 3 option:
  
  1) bool flag + std::vector<int> rdata. In which, flag records wether a negative or positive number,
  rdata records the digits. For example, -123 could be represented: 

  flag = false, rdata = [1, 2, 3]
  
  Another choice is to use vector<char> to store the data. For example, -123 could be 
  represented: 

  flag = false, rdata =['1', '2', '3']
  
  Such data structure are very intuitive.

  2) std::vector<int> rdata. In which, the first number can be stored as a negative number.
  For example, -123 could be represented as: 

  rdata = [-1, 2, 3].

  However, I choose the 3) option:
  
  3) std::vector<int> rdata. In which, if negative, every digit should be negative, and, the data is
  stored in reverse order. For example, -123 could be represented as: 

  rdata= [-3, -2, -1].
  
  Such design will lower the implementation complexity, because it is compliant with the
  basic algebra rules:
  
  ab = 10 * a + b; cd = 10 * c + d;
  ab + cd = 10 * (a + c) + (b + d).
  
  You could refer to BigInt.cc for more implementation details.

  As for the helper functions, pls refer to BigInt.cpp.
  */
  std::vector<int> rdata;
  //helper functons used to legalize the inner representation.
  void legalize(void);
  void overflow(void);
  void standardize(void);
  void delete_tailing_zeros(void);
  void check(void) const;
  //helper functions used by constructor.
  std::string to_str(const std::vector<char>& para);
  std::string to_str(const char para[], unsigned int size);
  //For test. Implemented in test.cc. 
  friend class UTestBigInt;

//error message string
public:
  static const std::string csCheckErrorEmpty;
  static const std::string csCheckErrorTailingZero;
  static const std::string csCheckErrorInvalidDigitOutOfRange;
  static const std::string csCheckErrorInvalideDigitMixed;
  static const std::string csStringConstructorErrorIllegalChar;
  static const std::string csStringConstructorErrorOnlyNegativeSign;
  static const std::string csIntConstructorIllegalInt;
};

#endif
