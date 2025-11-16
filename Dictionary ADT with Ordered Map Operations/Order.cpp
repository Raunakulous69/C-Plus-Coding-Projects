/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA7  
* Order.cpp
* Main Source File
***/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) 
{
     if (argc != 3) 
     {
          cerr << "Usage: " 
               << argv[0] << " <input file> <output file>" 
               << endl;
          return 1;
     }

     ifstream in(argv[1]);
     if (!in.is_open()) 
     {
          cerr << "Error: Cannot open the input file." << endl;
          return 1;
     }
    
     ofstream out(argv[2]);
     if (!out.is_open()) 
     {
          cerr << "Error: Cannot open the output file." << endl;
          return 1;
     }
    
     Dictionary dict;
     string line;
     int lineNumber = 1;
    
     while (getline(in, line)) 
     {
          dict.setValue(line, lineNumber);
          lineNumber++;
     }
    
     // Output Dictionary in order
     out << dict.to_string() << endl;
    
     // Output Dictionary in pre-order traversal
     out << dict.pre_string() << endl;
    
     // closing both of the files
     in.close();
     out.close();
    
     return 0;
}

