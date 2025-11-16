/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA6  
* Arithmetic.cpp
* Main Source File
***/

#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    // Checking for the correct number of arguments
    if (argc != 3) 
    {
         cerr << "Usage: "<< argv[0] << "<input file> <output file>" << endl;
         return 1;
    }

    // Opening the input file
    ifstream in(argv[1]);
    if (!in.is_open()) 
    {
         cerr << "Error: Couldn't open input file " << argv[1] << endl;
         return 1;
    }

    // Opening the output file
    std::ofstream out(argv[2]);
    if (!out.is_open()) 
    {
         cerr << "Error: Couldn't open output file " << argv[2] << endl;
         return 1;
    }

    // Reading the two large integers from input file 
    string line1;
    getline(in, line1);
    BigInteger A(line1);
    out << A.to_string() << endl << endl;
    
    string line2;
    getline(in, line2);
    
    string line3;
    getline(in, line3);
    BigInteger B(line3);
    out << B.to_string() << endl << endl;
    
    // Performing arithmetic operations and putting results to output file
    BigInteger sum = A + B;
    out << sum.to_string() << endl << endl;
    
    BigInteger diff = A - B;
    out << diff.to_string() << endl << endl;
        
    BigInteger A_minus_A = A - A;
    out << A_minus_A.to_string() << endl << endl;
    
    BigInteger two(2);
    BigInteger three(3);
    BigInteger A3_B2 = (three * A) - (two * B);
    out << A3_B2.to_string() << endl << endl;
    
    BigInteger AB = A * B;
    out << AB.to_string() << endl << endl;
    
    BigInteger A2 = A * A;
    out << A2.to_string() << endl << endl;
    
    BigInteger B2 = B * B;
    out << B2.to_string() << endl << endl;
    
    BigInteger nine(9);
    BigInteger sixteen(16);
    BigInteger A9_B16 = (nine)*(A2 * A2) + (sixteen)*(B2 * B2 * B);
    out << A9_B16.to_string() << endl << endl;

    
    // Closing the files
    in.close();
    out.close();

    return 0;
}
