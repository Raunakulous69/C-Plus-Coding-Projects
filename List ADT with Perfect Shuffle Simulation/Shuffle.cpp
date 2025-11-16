/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA5  
* Shuffle.cpp
* Main Source File
***/ 

#include <iostream>
#include <iomanip>
#include <string>
#include "List.h"

void shuffle(List& D)
{
     List E;
     int mid = D.length()/2;
     
     // removing the 1st half from D and insert it into E
     D.moveFront();
     E.moveBack();
     for (int i = 0; i < mid; i++)
     {
          ListElement f = D.front();
          E.insertBefore(f);
          D.eraseAfter();          
     }
     
     // merging E into D
     D.moveFront();
     E.moveFront();
     
     for (int i = 0; i < mid; i++)
     {
          D.moveNext();
          ListElement e = E.peekNext();
          D.insertBefore(e);
          E.moveNext(); 
     }    
}


int main(int argc, char* argv[])
{
     if (argc != 2)
     {
          std::cerr << "Usage: " << argv[0] << " <number of shuffles>" << std::endl;
          return 1;
     }
     
     // converting the given string input into an integer value
     int n = std::stoi(argv[1]); 
     
     // if input is less than 1
     if (n < 1)
     {
          std::cerr << "Input Error: given input is less than 1" << std::endl;
          return 1;
     }
     
     // printing the output's header
     std::cout << "deck size       shuffle count" << std::endl;
     std::cout << "------------------------------" << std::endl;
     
     for (int i = 1; i <= n; i++)
     {
          // creating an empty list 
          List L;
          
          // insert the initial values from 1 to i into the list
          L.moveBack();
          for (int j = 1; j <= i; j++)
          {
               L.insertBefore(j);
          }
          
          // save the initial state of L into a local variable (list M)
          List M(L);
          
          // shuffle L until it reaches its original state
          int count = 0;
          
          while (true)
          {
               count += 1;
               shuffle(L);
               if (L == M)
               {
                    break;
               }
          }
          
          // printing the results for deck size and shuffle count
          std::cout << " " << std::left << std::setw(16) << i << count << std::endl;  
     }

     return 0;
}
