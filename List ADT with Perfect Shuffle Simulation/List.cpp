/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA5  
* List.cpp
* Source File with List Functions 
***/

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

// Creates a new node
List::Node::Node(ListElement x)
{
     data = x;
     prev = nullptr;
     next = nullptr;
}

// Creates a new list
List::List()
{
     frontDummy = new Node(0);
     backDummy = new Node(-1); 
     
     frontDummy->next = backDummy; // setting the list up (double-linked)
     frontDummy->prev = backDummy;  
     backDummy->next = frontDummy;
     backDummy->prev = frontDummy;
      
     beforeCursor = frontDummy;
     afterCursor = backDummy;
     
     pos_cursor = 0;
     num_elements = 0;
}

/*List::List(const List& L)
{
     moveBack();
     Node* n = L.frontDummy->next;
     
     while (n != L.backDummy)
     {
          insertBefore(n->data);
          n = n->next;
     }
}*/

// Copy Constructor
List::List(const List& L)
{
     // clear current list (this is a pointer to self, which is our list)
     //clear();
     
     frontDummy = new Node(0);
     backDummy = new Node(-1); 
     
     frontDummy->next = backDummy; // setting the list up (double-linked)
     frontDummy->prev = backDummy;  
     backDummy->next = frontDummy;
     backDummy->prev = frontDummy;
      
     beforeCursor = frontDummy;
     afterCursor = backDummy;
     
     pos_cursor = 0;
     num_elements = 0;
  
     // move to front of given list (L) and assign it a node
     Node* n = L.frontDummy->next;
     moveBack();
     
     while(n != L.backDummy)
     {
          insertBefore(n->data);
          n = n->next;
     }
     
     pos_cursor = L.pos_cursor;
     num_elements = L.num_elements;
}


// destroys and wipes out an entire list
List::~List()
{
     clear(); 
     delete frontDummy;
     delete backDummy;
}

int List::length() const
{
     return num_elements;
}

ListElement List::front() const
{
     if (length() > 0)
     {
          return frontDummy->next->data;
     }
     
     else
     {
          throw std::length_error("List Error: Given List is Empty");
     }
}

ListElement List::back() const
{
     if (length() > 0)
     {
          return backDummy->prev->data;
     }
     
     else
     {
          throw std::length_error("List Error: Given List is Empty");
     }
}

int List::position() const
{
     return pos_cursor;
}

ListElement List::peekNext() const
{
     if (position() < length() && position() >= 0)
     {
            return afterCursor->data;
     }
     
     else
     {
          throw std::range_error("List Error: position is out of range");
     }
}

ListElement List::peekPrev() const
{
     if (position() <= length() && position() > 0)
     {
            return beforeCursor->data;
     }
     
     else
     {
          throw std::range_error("List Error: position is out of range");
     }
}

// Manipulation procedures 
void List::clear()
{     
     // cursor's position (right before back dummy node) stays the same
     moveBack();
     while (pos_cursor > 0)
     {
          eraseBefore();
     }
}

void List::moveFront()
{
      pos_cursor = 0;
      beforeCursor = frontDummy;
      afterCursor = beforeCursor->next;          
}

void List::moveBack()
{
     pos_cursor = length();
     afterCursor = backDummy;
     beforeCursor = afterCursor->prev;

}

ListElement List::moveNext()
{
     if (position() < length())
     {
          pos_cursor += 1;
          beforeCursor = beforeCursor->next;
          afterCursor = afterCursor->next;
          return beforeCursor->data;
     }
     
     else
     {
          throw std::range_error("List Error: position is out of range");
     }
}

ListElement List::movePrev()
{
     if (position() > 0)
     {
          pos_cursor -= 1;
          beforeCursor = beforeCursor->prev;
          afterCursor = afterCursor->prev;
          return afterCursor->data;
     }
     
     else
     {
          throw std::range_error("List Error: position is out of range");
     }
}

void List::insertAfter(ListElement x)
{
     // create a new node
     Node* n = new Node(x);
     
     // place new node between beforeCursor and afterCursor
     beforeCursor->next = n;
     
     n->prev = beforeCursor;
     n->next = afterCursor;
     
     afterCursor->prev = n; 
     
     // since we placed a new node after the position cursor, this new node 
     // should be the afterCursor node (not position cursor node)
     afterCursor = n;
     
     // increase number of elements
     num_elements += 1;
}

void List::insertBefore(ListElement x)
{     
     // create a new node
     Node* n = new Node(x);
     
     // place new node between beforeCursor and afterCursor (double-linked)
     beforeCursor->next = n;
     afterCursor->prev = n;     
     n->next = afterCursor;
     n->prev = beforeCursor;
      
     // since we placed a new node after the position cursor, this new node 
     // should be the beforeCursor node (not position cursor node)
     beforeCursor = n;
     
     // adjust the position cursor index
     pos_cursor += 1;
     
     // increase number of elements
     num_elements += 1;
}

void List::setAfter(ListElement x)
{
     if (position() < length())
     {
          afterCursor->data = x;
     }
     
     else
     {
          throw std::range_error("List Error: position is out of range");
     }
}

void List::setBefore(ListElement x)
{
     if (position() > 0)
     {
          beforeCursor->data = x;
     }
     
     else
     {
          throw std::range_error("List Error: position is out of range");
     }
}

void List::eraseAfter()
{     
     if (position() >= length())
     {
          throw std::range_error("List Error: position is out of range");
     }
     
     beforeCursor->next = afterCursor->next;
     afterCursor->next->prev = beforeCursor;
     
     delete afterCursor;
     
     // doing adjustments (beforeCursor exists, but afterCursor doesn't)
     afterCursor = beforeCursor->next;
     num_elements -= 1;         
}

void List::eraseBefore()
{
     if (position() <= 0)
     {
          throw std::range_error("List Error: position is out of range");
     }
     
     afterCursor->prev = beforeCursor->prev;
     beforeCursor->prev->next = afterCursor;
     
     delete beforeCursor;
     
     // doing adjustments (beforeCursor exists, but afterCursor doesn't)
     beforeCursor = afterCursor->prev;
     num_elements -= 1;
     pos_cursor -= 1;
}

// Other Functions 
int List::findNext(ListElement x)
{
     while (position() < length())
     {
          if (afterCursor->data == x)
          {
               moveNext();
               return pos_cursor;
          }
          
          else
          {
               moveNext();               
          }                
     }
     
     return -1;
}

int List::findPrev(ListElement x)
{
     while (position() > 0)
     {
          if (beforeCursor->data == x)
          {
               movePrev();
               return pos_cursor;
          }
          
          else
          {
               movePrev();               
          }                
     }
     
     return -1;
}

void List::cleanup()
{
     Node* p = frontDummy->next;
     int p_Pos = 0;
          
     while (p != backDummy)
     { 
          p_Pos += 1;
          Node* q = p->next;
          int q_Pos = p_Pos + 1;
          
          while (q != backDummy)
          {
               q_Pos += 1;
               
               if (p->data == q->data)
               {
                   // check if we are deleting node pointed by beforeCursor
                   if (q == beforeCursor)
                   {
                        beforeCursor = q->prev;
                        pos_cursor -= 1;
                   }
                   
                   // check if we are deleting node pointed by afterCursor
                   if (q == afterCursor)
                   {
                        afterCursor = q->next;
                   }
                   
                   // delete the node pointed by q
                   Node* temp = q;
                   temp->prev->next = temp->next;
                   temp->next->prev = temp->prev;
                   
                   // updating the q before we delete the node pointed by it
                   q = q->next;
                   
                   delete temp;
                   num_elements -= 1;
                   
                   // if we are removing a node before current position 
                   // cursor, decrement its value by 1;
                   if (q_Pos <= pos_cursor)
                   {
                        pos_cursor -= 1;
                   }
               }
               
               else 
               {
                   q = q->next;
               }
          }
          
          p = p->next;
     }
} 
   
List List::concat(const List& L) const 
{
     List L1;
     
     Node* N = frontDummy->next;
     while (N != backDummy)
     {
          L1.moveBack();
          L1.insertBefore(N->data);
          N = N->next;
     }
     
     Node* M = L.frontDummy->next;
     while (M != L.backDummy)
     {
          L1.moveBack();
          L1.insertBefore(M->data);          
          M = M->next;
     }
     
     L1.moveFront();
     return L1;     
}
   
std::string List::to_string() const 
{
     std::string s = "(";
     
     Node* N = frontDummy->next;    
     while (N != backDummy)
     {
          s = s + std::to_string(N->data);
          
          if (N->next != backDummy)
          { 
               s = s + ",";
          }
          
          N = N->next;
     }
     
     s = s + ")";
     return s;
}
   
bool List::equals(const List& R) const
{
     if (length() != R.length())
     {
          return false;
     }
     
     Node* p = frontDummy->next;
     Node* q = R.frontDummy->next;
     
     while (p != backDummy && q != R.backDummy)
     {
          if (p->data != q->data)
          {
               return false;
          }
          
          else
          {
               p = p->next;
               q = q->next; 
          }
     }
     
     return true;
}
 
// Overriden Operators
std::ostream& operator<<( std::ostream& stream, const List& L )
{
     return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B )
{
     return A.List::equals(B);
}

List& List::operator=( const List& L )
{
      if (this != &L)
      {
           // copy everything from L into local variable, temp
           List temp = L;
           
           // now swap everything between temp and this
           std::swap(frontDummy, temp.frontDummy);
           std::swap(backDummy, temp.backDummy);
           std::swap(beforeCursor, temp.beforeCursor);
           std::swap(afterCursor, temp.afterCursor);
           std::swap(num_elements, temp.num_elements);
      }
      
      // at this point, temp got out of scope, so list destructor will be 
      // called and everything pointed by temp is freed by destructor 
      // returning value of this list
      return *this;      
}     

