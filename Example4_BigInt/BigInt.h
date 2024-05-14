#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <vector>
#include <string>
#include <iostream>

class BigInt {

public:
  //Special member functions
  explicit BigInt ();
  explicit BigInt (int para);
  explicit BigInt (const std::string& para);

  //output support
  friend std::ostream& operator<< (std::ostream& out, const BigInt& obj);

  //operators support
  BigInt operator+ (const BigInt& opd) const;
  bool operator== (const BigInt& opd) const;
  
private:
  /*
  private members including data and helper functions. About the data representation, we have 3 option:
  
  1) bool flag and std::vector<int> rdata. In which, flag records wether a negative or positive number, rdata records the digits. For example, -123 could be represented: 

  flag = false, rdata = [1, 2, 3]
  
  Another choice is to use vector<char> to store the data. For example, -123 could be 
  represented: 

  flag = false, rdata =['1', '2', '3']
  
  Such data structure are very intuitive.

  2) std::vector<int> rdata. In which, the first number can be stored as a negative number.
  For example, -123 could be represented as: 

  rdata = [-1, 2, 3].

  However, I choose the 3) option:
  
  3) std::vector<int> rdata. In which, if negative, every digit should be negative, and, the data is stored in reverse order. For example, -123 could be represented as: 

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
