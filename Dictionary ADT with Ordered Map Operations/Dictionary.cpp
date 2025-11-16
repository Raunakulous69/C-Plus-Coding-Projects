/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA7  
* Dictionary.cpp
* Source Code File with Dictionary Functions
***/ 

#include <iostream>
#include <string>
#include "Dictionary.h"

 
// Node Constructor
Dictionary::Node::Node(keyType k, valType v)
{
     key = k;
     val = v;
     parent = nullptr;
     left = nullptr;
     right = nullptr;
}  
 
 // Helper Functions                      ---------------------------------------------
void Dictionary::inOrderString(std::string& s, Node* R) const
{
     if (R != nil)
     {
          inOrderString(s, R->left);
          s += R->key + " : " + std::to_string(R->val) + "\n";
          inOrderString(s, R->right);        
     }
}

void Dictionary::preOrderString(std::string& s, Node* R) const
{
     if (R != nil)
     {
          s += R->key + "\n";
          preOrderString(s, R->left);
          preOrderString(s, R->right);        
     }
}

void Dictionary::preOrderCopy(Node* R, Node* N)
{
     if (R != nil || R != N)
     {
          setValue(R->key, R->val);
          preOrderCopy(R->left, N);
          preOrderCopy(R->right, N);            
     }
}

void Dictionary::postOrderDelete(Node* R)
{
     if (R != nil)
     {
          postOrderDelete(R->left);
          postOrderDelete(R->right);
          delete R;
     }  
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const
{
     if (R == nil)
     {
          return nil;
     }
     
     if (R->key == k)
     {
          return R;
     }
     
     else if (R->key > k)
     {
          return search(R->left, k);
     }
     
     else
     {
          return search(R->right, k);
     }
}

Dictionary::Node* Dictionary::findMin(Node* R)
{
     if (R == nil)
     { 
          return nil;
     }
     
     while (R->left != nil) 
     {
          R = R->left;
     }
     
     return R;
}

Dictionary::Node* Dictionary::findMax(Node* R)
{
     if (R == nil)
     { 
          return nil;
     }
     
     while (R->right != nil) 
     {
          R = R->right;
     }
     
     return R;
}

Dictionary::Node* Dictionary::findNext(Node* N)
{
     if (N == nil)
     {
          return nil;
     }
     
     // check if N has a right subtree, next is the minimum of that subtree
     if (N->right != nil)
     {
          return findMin(N->right);
     }
     
     // check if N is the left child of its parent
     Node *p = N->parent;
     while (p != nil && N == p->right)
     {
          N = p;
          p = N->parent;
     }
 
     return p; 
}

Dictionary::Node* Dictionary::findPrev(Node* N)
{
     if (N == nil)
     {
          return nil;
     }
     
     // check if N has a left subtree
     if (N->left != nil)
     {
          return findMax(N->left);
     }
     
     // check if N is the right child of its parent
     Node *p = N->parent;
     while (p != nil && N == p->left)
     {
          N = p;
          p = N->parent;
     }
 
     return p;    
}


// Class Constructors & Destructors    ----------------------------------------
Dictionary::Dictionary()
{
     nil = nullptr;
     root = nil;
     current = nil;
     num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D)
{
     nil = nullptr;
     root = nil;
     current = nil;
     num_pairs = 0;
     preOrderCopy(D.root, nil);
}

Dictionary::~Dictionary()
{
     clear();
}


// Access functions  --------------------------------------------------------
int Dictionary::size() const
{
     return num_pairs;
}

bool Dictionary::contains(keyType k) const
{
     return search(root,k) != nil;
}

valType& Dictionary::getValue(keyType k) const
{
     Node* N = search(root,k);
     
     if (N == nil)
     {
          throw std::logic_error("Key doesn't exist");
     }
     
     return N->val;
}

bool Dictionary::hasCurrent() const
{
     return current != nil;
}

keyType Dictionary::currentKey() const
{
     if (!hasCurrent())
     {
          throw std::logic_error("Current is undefined");
     }
     
     return current->key;
}

valType& Dictionary::currentVal() const
{
     if (!hasCurrent())
     {
          throw std::logic_error("Current is undefined");
     }
     
     return current->val;
}


// Manipulation procedures  -------------------------------------------------
void Dictionary::clear()
{
     postOrderDelete(root);
     root  = nil;
     current = nil;
     num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v)
{
     // p is parent of current 
     Node* p = nil;
     Node* curr = root;
     
     while (curr != nil)
     {
          // update the value if given key is same as current key
          if (curr->key == k)
          {
               curr->val = v;
               return;
          }
          
          // going leftward if the given key is less than current key
          else if (curr->key > k)
          {
               p = curr;
               curr = curr->left;
          }
          
          // going rightward if the given key is more than current key
          else 
          {
               p = curr;
               curr = curr->right;
          }
     }
     
     // if there is no root, then create a new node for the tree's root
     if (p == nil)
     {
          root = new Node(k,v);
     }
     
     // if given key is smaller than parent key,then add it to left side
     else if (k < p->key)
     {
          p->left = new Node(k,v);
          p->left->parent = p;
     }
     
     // if given key is larger than parent key,then add it to right side     
     else
     {
          p->right = new Node(k,v);
          p->right->parent = p;
     }
     
     num_pairs += 1;
}


void Dictionary::remove(keyType k)
{
     Node* N = search(root,k);
     
     
     if (N == nil)
     {
          throw std::logic_error("Key doesn't exist");
     }
     
     // reset the current if current is being deleted
     if (N == current)
     {
          current = nil;
     }
     
     // deleting a node with 2 children
     if (N->left != nil && N->right != nil)
     {
          // find the node with smallest key on the right subtree
          Node* q = findMin(N->right);    
          
          // save the key and value of q
          keyType q_key = q->key;
          valType q_val = q->val;
          
          // getting the node parent of q
          Node* p = q->parent;
          
          // delete q
          Node* child = (q->left == nil) ? q->right : q->left;           
          
          if (p == nil)
          {
               root = child;
               if (child != nil)
               {
                    child->parent = nil;
               }
          }
          
          // deleting the left child
          else if (q->key < p->key)
          {
               p->left = child;
               if (child != nil)
               {
                    child->parent = p;
               }
          }
          
          // deleting the right child
          else
          {
               p->right = child;
               if (child != nil)
               {
                    child->parent = p;
               }
          }
          
          delete q;
          num_pairs -= 1;
          
          // copy the key and value of q into N
          N->key = q_key;
          N->val = q_val;   
     }
     
     // deleting a node with 1 or 0 children
     else
     {
          Node* p = N->parent;
          Node* child = (N->left == nil) ? N->right : N->left;
          
          if (p == nil)
          {
               root = child;
               if (child != nil)
               {
                    child->parent = nil;
               }
          }
          
          // deleting the left child
          else if (N->key < p->key)
          {
               p->left = child;
               if (child != nil)
               {
                    child->parent = p;
               }
          }
          
          // deleting the right child
          else
          {
               p->right = child; 
               if (child != nil)
               {
                    child->parent = p;
               }
          }
          
          delete N;
          num_pairs -= 1;
     }         
}

void Dictionary::begin()
{
     current = findMin(root);
}

void Dictionary::end()
{
     current = findMax(root);
}

void Dictionary::next()
{
     if (!hasCurrent())
     {
          throw std::logic_error("Current is undefined");
     }
     
     current = findNext(current);
}

void Dictionary::prev()
{
     if (!hasCurrent())
     {
          throw std::logic_error("Current is undefined");
     }
     
     current = findPrev(current);
}


// Other Functions   ---------------------------------------------------------
std::string Dictionary::to_string() const
{
     std::string s;
     inOrderString(s,root);
     return s;
}

std::string Dictionary::pre_string() const
{
     std::string s;
     preOrderString(s,root);
     return s;
}

bool Dictionary::equals(const Dictionary& D) const
{
     if (num_pairs != D.num_pairs)
     {
          return false;
     }
     
     return to_string() == D.to_string();
}


// Overloaded Operators  ----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, Dictionary& D )
{
     return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B )
{
     return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D )
{
     if (this != &D)
     {
          clear();
          
          // make a copy of D
          Dictionary temp = D;
          
          //Swap the copied dictionary fields with this dictionary fields
          std::swap(nil, temp.nil);
          std::swap(root, temp.root);
          std::swap(current, temp.current);
          std::swap(num_pairs, temp.num_pairs);     
     }
     
     return *this;
}

