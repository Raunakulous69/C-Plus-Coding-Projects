/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA8  
* WordFrequency.cpp
* Main Source File for Dictionary ADT
***/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[])
{
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " 
           << argv[0] << " <input file> <output file>" 
           << endl;
      
      return 1;
   }

   // Opening the input file for reading 
   in.open(argv[1]);
   if(!in.is_open())
   {
      cerr << "Unable to open file " << argv[1] 
           << " for reading" 
           << endl;
      
      return 1;
   }

   // Opening the output file for writing 
   out.open(argv[2]);
   if( !out.is_open() )
   {
      cerr << "Unable to open file " << argv[2] 
           << " for writing" 
           << endl;
      
      return 1;
   }

   // Reading each line of input file, then counting and printing tokens 
   Dictionary dict;
   
   while(getline(in,line))  
   {
      len = line.length();
     
      // get starting index of the tokem
      begin = min(line.find_first_not_of(delim, 0), len);
      
      // get end index of the token 
      end   = min(line.find_first_of(delim, begin), len);
      
      // get the token itself
      token = line.substr(begin, end-begin);
      
      while (token != "")
      {  
         // convert the token into lowercase
         transform(token.begin(), token.end(), token.begin(), 
                   [] (unsigned char c)
                   {
                        return tolower(c);
                   });
         
         // insert the token into the dictionary
         if (dict.contains(token))
         {
              // get current value associated with the key from the token
              valType val = dict.getValue(token);
              val += 1;
              dict.setValue(token, val);
         }
         
         
         // when adding a token/key for the 1st time for a particular word
         else 
         {
              dict.setValue(token, 1);
         }
         
         // getting the next token from the dictionary
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }  
   }
   
   // saving the dictionary to the output file and printing it out
   out << dict << endl;
   

   // closing both of the files 
   in.close();
   out.close();

   return 0;
}

