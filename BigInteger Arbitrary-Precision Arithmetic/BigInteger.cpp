/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA6  
* BigInteger.cpp
* Source Code File with BigInteger Functions
***/ 

#include <iostream>
#include <string>
#include <iomanip>
#include "BigInteger.h"

#define ZERO_STATE 0
#define POSITIVE 1
#define NEGATIVE -1
#define BASE 1000000000
#define POWER 9

using namespace std;

// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m)
{
     L.moveFront();
     
     while (L.position() < L.length())
     {
          L.setAfter(m * L.peekNext());
          L.moveNext();
     }
}

// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L)
{
     scalarMultList(L, -1);
}

// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn)
{
     S.clear();
     
     S.moveFront();
     A.moveFront();
     B.moveFront();
     
     while (A.position() < A.length() && B.position() < B.length())
     {
          S.insertBefore(A.moveNext() + (sgn * B.moveNext()));
     }
     
     // adding any remaining elements from A
     while (A.position() < A.length())
     {
          S.insertBefore(A.moveNext());
     }
     
     // adding any remaining elements from (sgn * B)
     while (B.position() < B.length())
     {
          S.insertBefore(sgn * B.moveNext());
     }
}

// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L)
{
     ListElement carry = 0;
     L.moveFront();
     
     // adding up process of the integers
     while (L.position() < L.length())
     {
          ListElement x = L.moveNext();
          x += carry;
          
          // if this* number is negative
          if (x < 0)
          {
               x = x + BASE;
               carry = -1;
          }
          
          // if x is greater than or equal to the BASE
          else if (x >= BASE)
          {
               carry = x / BASE;
               x = x % BASE; 
          }
          
          // if x is smaller than BASE
          else 
          {
               carry = 0;
          }  
          
          // set the x value into list at the end b/c x may have changed
          // if you do not set it, it will cause problems
          L.setBefore(x);
     }
     
     
     // if carry is greater than 0, insert it into the back of the list)
     int sign = POSITIVE;
     
     if (carry < 0)
     {
          sign = NEGATIVE;
          carry = -carry;
     }
      
     if (carry != 0)
     {
          L.insertBefore(carry);
     }
     
     
     // delete any trailing zeros (0045 should become 45)
     L.moveBack();
     while (L.position() > 0 && L.back() == 0)
     {
          L.eraseBefore();
     }
     
     if (L.length() == 0)
     {
          sign = ZERO_STATE;
     }
     
     return sign;
}

// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p)
{
     ListElement x = 0;
     L.moveFront();     
     
     for (int i = 0; i < p; i++)
     {
          L.insertAfter(x);
     }
}



// Class Constructors & Destructors
BigInteger::BigInteger()
{
     signum = ZERO_STATE;
     digits = List();    
}


BigInteger::BigInteger(long x)
{
     signum = ZERO_STATE;
     digits = List();
     
     // 1st decide on the integer sign (if 0, it can't be added to the list)
     if (x < 0)
     {
          signum = NEGATIVE;
          x = -x;
          digits.insertBefore(x);
     }
     
     else if (x > 0)
     {
          signum = POSITIVE;
          digits.insertBefore(x);
     }      
}


BigInteger::BigInteger(std::string s)
{
     signum = ZERO_STATE;
     digits = List();
     
     // if string is empty
     if (s.length() == 0)
     {
          throw std::invalid_argument("BigInteger: Construcgtor: empty string");
     }
     
     // determining the sign of the given number
     int curr_index = 0;
     int final_signum = POSITIVE;
     
     if (s[curr_index] == '-')
     {
          final_signum = NEGATIVE;
          curr_index += 1;
     }   
     
     else if (s[curr_index] == '+')
     {
          final_signum = POSITIVE;
          curr_index += 1;
     }
     
     
     
     // Removing the non-signifant zeros (001 becomes 1)
     while (s[curr_index] == '0')
     {
          curr_index += 1;
     }
     
     int s_len = s.length();
     if (curr_index >= s_len)
     {
          throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
     }
     
     for (int i = curr_index; i < s_len; i++)
     {
          if (s[i] < '0' || s[i] > '9')
          {
               throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
          }
     }
     
     // determine how many digits we have in the string
     int num_char = s_len - curr_index;
     int num_digits = num_char / POWER;
     int ms_digit_len = num_char - (num_digits * POWER);
     std::string digit_string;
     
     // extract the most significant digit (leftmost digit)
     if (ms_digit_len > 0)
     {
          digit_string = s.substr(curr_index, ms_digit_len);
          ListElement x = std::stol(digit_string);
          digits.insertAfter(x);
          curr_index += ms_digit_len;
     }
     
     // now extract rest of the digits in the string
     while (curr_index < s_len)
     {
          digit_string = s.substr(curr_index, POWER);
          ListElement x = std::stol(digit_string);
          digits.insertAfter(x);
          curr_index += POWER; 
     }
     
     if (normalizeList(digits) == 0)
     {
          signum = ZERO_STATE;
     }   
     
     else
     {
          signum = final_signum;
     }        
}


BigInteger::BigInteger(const BigInteger& N)
{
     signum = N.signum;
     digits = N.digits;
}



// Access functions
int BigInteger::sign() const
{
     return signum;     
}

int BigInteger::compare(const BigInteger& N) const
{
     // checking the length of each number
     if (digits.length() != N.digits.length())
     {
          if (digits.length() > N.digits.length())
          {
               return signum * POSITIVE;      
          }
          
          else
          {
               return N.signum * NEGATIVE;
          }  
     }
     
     // checking if both are 0
     if (signum == 0 && N.signum == 0)
     {
          return ZERO_STATE;
     }
     
     // checking if this number is postive and N is negative, then this is 
     // bigger
     if (signum >= 0 && N.signum < 0)
     {
         return POSITIVE;
     }
     
     // checking if this number is negative and N is positive, then N is 
     // bigger
     if (signum < 0 && N.signum >= 0)
     {
         return NEGATIVE;
     }
     
     // at this point, we have 2 numbers with same # of digits and same 
     // sign, so compare each digit at a time
     List A = digits;
     List B = N.digits;
      
     A.moveBack();
     B.moveBack();
     
     while (A.position() > 0 && B.position() > 0)
     {
          ListElement x = A.movePrev(); 
          ListElement y = B.movePrev();
          
          if (x > y)
          {
                return signum * POSITIVE;     
          }
          
          else if (x < y)
          {
               return signum * NEGATIVE;
          }
     }
     
     // if this digit is exactly the same in magnitude and sign as N's list, 
     // return 0 
     return ZERO_STATE;    
}



// Manipulation procedures
void BigInteger::makeZero()
{
     signum = ZERO_STATE;
     digits.clear();
}

void BigInteger::negate()
{
     if (signum != ZERO_STATE)
     {
          signum = -signum;   
     }
}


// BigInteger Arithmetic operations
BigInteger BigInteger::add(const BigInteger& N) const
{
     // if this number is 0
     if (signum == ZERO_STATE)
     {
          return N;
     }
     
     // if N is 0
     if (N.signum == ZERO_STATE)
     {
          return *this;
     }
     
     BigInteger result;
     List A = digits;
     List B = N.digits;
     
     // if both numbers have the same signs
     if ((signum * N.signum) == POSITIVE)
     {
          sumList(result.digits, A, B, POSITIVE);
          normalizeList(result.digits);
          result.signum = signum;
          return result;
     }
     
     
     // if the numbers have different signs from each other
     // if this number is negative, make every digit of A negative
     if (signum == NEGATIVE)
     {
          BigInteger I = *this;
          I.negate();
          int r = I.compare(N);
          
          if (r < 0)
          {
               // -A + B (where absolute value of A is smaller than B)
               sumList(result.digits, B, A, NEGATIVE);
               normalizeList(result.digits);
               result.signum = POSITIVE;
          }
          
          else if (r > 0)
          {
               // -A + B (where absolute value of A is greater than B)
               sumList(result.digits, A, B, NEGATIVE);
               normalizeList(result.digits);
               result.signum = NEGATIVE;
          }
          
          else
          {
               result = BigInteger(0);
          }               
     }
     
     // if N is negative, make every digit of B negative
     if (N.signum == NEGATIVE)
     {
          BigInteger I = N;
          I.negate();
          int r = compare(I);
          
          if (r < 0)
          {
               // A - B (where absolute value of A is smaller than B)
               sumList(result.digits, B, A, NEGATIVE);
               normalizeList(result.digits);
               result.signum = NEGATIVE;
          }
          
          else if (r > 0)
          {
               // A - B (where absolute value of A is greater than B)
               sumList(result.digits, A, B, NEGATIVE);
               normalizeList(result.digits);
               result.signum = POSITIVE;
          }
          
          else
          {
               result = BigInteger(0);
          }    
     }
     return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const
{        
     BigInteger M = N;
     M.negate();
     return add(M); 
}


BigInteger BigInteger::mult(const BigInteger& N) const
{
    int final_signum = signum * N.signum;
    BigInteger result;
    
    // if the product equals 0
    if (final_signum == 0)
    {
         return result;
    }
    
    // General Multiplication Process
    List A = digits;
    List B = N.digits;
    
    A.moveFront();
    B.moveFront();
    
    int shift = 0;
    
    while (B.position() < B.length())
    {
         ListElement x = B.moveNext();
         List C = A;
         scalarMultList(C,x);
         
         normalizeList(C);
         shiftList(C, shift);
         
         sumList(result.digits, result.digits, C, POSITIVE);
         normalizeList(result.digits);
         
         shift += 1;
    }
    
    result.signum = final_signum;
    return result;
}



// Other Functions
std::string BigInteger::to_string()
{
     std::stringstream result;
     
     // if the number is 0
     if (signum == ZERO_STATE) 
     {
          return "0";
     }

     // if the number is negative
     else if (signum == NEGATIVE) 
     {
          result << "-";
     }

     // general process for any non-zero number 
     digits.moveBack();
     result << std::to_string(digits.movePrev());
     
     while (digits.position() > 0) 
     {
          result << std::setfill('0') 
                 << std::setw(POWER) 
                 << std::to_string(digits.movePrev());
     }

     return result.str();
}



// Overriden Operators
std::ostream& operator<<( std::ostream& stream, BigInteger N )
{
     return stream << N.BigInteger::to_string();     
}

bool operator==( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::compare(B) == 0;
}

bool operator<( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::compare(B) < 0; 
}

bool operator<=( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::compare(B) <= 0;
}

bool operator>( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::compare(B) > 0;
}

bool operator>=( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::compare(B) >= 0;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B )
{
     A = A.add(B);
     return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B )
{
     A = A.sub(B);
     return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B )
{
     return A.BigInteger::mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B )
{
     A = A.mult(B);
     return A;
}
