/***
* Raunak Anwar
* ranwar3
* 2025 Winter CSE101 PA8  
* Dictionary.cpp
* Source Code File with Dictionary Functions
***/ 

#include <iostream>
#include <string>
#include "Dictionary.h"

#define RED 0
#define BLACK -1


// Node constructor
Dictionary::Node::Node(keyType k, valType v)
{
     key = k;
     val = v;
     parent = nullptr;
     left = nullptr;
     right = nullptr;
     color = BLACK;
}


// Helper Functions                               ---------------------------------------------
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
          if (R->color == BLACK)
          {
               s += R->key + "\n";
          }
          
          else 
          {
               s += R->key + " (RED)\n";
          }
          preOrderString(s, R->left);
          preOrderString(s, R->right);        
     }
}

void Dictionary::BST_insert(Node* M)
{
     Node* z = new Node(M->key, M->val);
     
     Node* y = nil; // parent of x 
     Node* x = root; // current node
     
     while (x != nil)
     {
          y = x;
          
          if (z->key < x->key)
          {
               // make x node go leftward until it reaches same key as z
               x = x->left;
          }
          
          // if z->key is greater than x->key
          else 
          { 
               // make x node go rightward until it reaches same key as z
               x = x->right;
          }
     }
          
     z->parent = y;
     
     if (y == nil)
     {    // this dictionary is was empty
          root = z;
     }    
   
     else if (z->key < y->key)
     {
          y->left = z;
     }
     
     else 
     {
          y->right = z;
     }
     
     z->left = nil;
     z->right = nil;
     z->color = RED;     
     RB_InsertFixUp(z);
     
     num_pairs++;
} 


void Dictionary::preOrderCopy(Node* R, Node* N)
{
     if (R != N)
     {
          BST_insert(R);
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



// RBT Helper Functions                            -----------------------------------------
void Dictionary::LeftRotate(Node* N)
{
     Node* x = N;
     
     Node* y = x->right;
     x->right = y->left; // turns y's left subtree into x's right subtree
     
     if (y->left != nil) 
     {
          y->left->parent = x;
     }
    
     y->parent = x->parent;
    
     if (x->parent == nil) 
     {
          root = y;
     } 
    
     else if (x == x->parent->left) 
     {
          x->parent->left = y;
     } 
    
     else 
     {
          x->parent->right = y;
     }
    
     y->left = x;
     x->parent = y;
}

void Dictionary::RightRotate(Node* N)
{
     Node* x = N;
     
     Node* y = x->left;
     x->left = y->right; // turns y's right subtree into x's left subtree
     
     if (y->right != nil) 
     {
          y->right->parent = x;
     }
    
     y->parent = x->parent;
    
     if (x->parent == nil) 
     {
          root = y;
     } 
    
     else if (x == x->parent->right) 
     {
          x->parent->right = y;
     } 
    
     else 
     {
          x->parent->left = y;
     }
    
     y->right = x;
     x->parent = y;
}


void Dictionary::RB_InsertFixUp(Node* N)
{
     Node* z = N;
     
     while (z->parent->color == RED) 
     {
          if (z->parent == z->parent->parent->left) 
          {
               Node* y = z->parent->parent->right;
            
               if (y->color == RED) 
               {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
               }  
            
               else 
               {
                    if (z == z->parent->right) 
                    {
                         z = z->parent;
                         LeftRotate(z);
                    }
                    
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    RightRotate(z->parent->parent);
               }    
          }     
        
          else 
          {
               Node* y = z->parent->parent->left;
               
               if (y->color == RED) 
               {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
               } 
            
               else 
               {
                    if (z == z->parent->left) 
                    {
                         z = z->parent;
                         RightRotate(z);
                    }
                    
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    LeftRotate(z->parent->parent);
               }             
          }     
     }            
     
     root->color = BLACK;
}   

void Dictionary::RB_Transplant(Node* u, Node* v)
{
     if (u->parent == nil) 
     {
          root = v;
     } 
    
     else if (u == u->parent->left) 
     {
          u->parent->left = v;
     } 
     
     else 
     {
          u->parent->right = v;
     }

     v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N)
{
     Node* x = N;
     
     while (x != root && x->color == BLACK)
     {
        if (x == x->parent->left) 
        {
            Node* w = x->parent->right;
            if (w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            
            if (w->left->color == BLACK && w->right->color == BLACK) 
            {
                w->color = RED;
                x = x->parent;
            } 
            
            else 
            {
                if (w->right->color == BLACK) 
                {
                     w->left->color = BLACK;
                     w->color = RED;
                     RightRotate(w);
                     w = x->parent->right;
                }
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        } 
        
        else 
        {
            Node* w = x->parent->left;
            
            if (w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) 
            {
                w->color = RED;
                x = x->parent;
            } 
            
            else 
            {
                if (w->left->color == BLACK) 
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    
    x->color = BLACK;
}

void Dictionary::RB_Delete(Node* N)
{
    Node* z = N;
    Node* y = z;
    Node* x;
    
    int y_originalColor = y->color;
    if (z->left == nil) 
    {
        x = z->right;
        RB_Transplant(z, z->right);
    } 
    
    else if (z->right == nil) 
    {
        x = z->left;
        RB_Transplant(z, z->left);
    } 
    
    else 
    {
        y = findMin(z->right);
        y_originalColor = y->color;
        x = y->right;
        
        if (y->parent == z) 
        {
             x->parent = y;
        } 
        
        else 
        {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        
    }
    
    if (y_originalColor == BLACK) 
    {
        RB_DeleteFixUp(x);
    }
}


// Class Constructors & Destructors  ----------------------------------------
Dictionary::Dictionary()
{
     nil = new Node("", -1);
     nil->color = BLACK;
     root = nil;
     current = nil;
     num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D)
{
     nil = new Node("", -1);
     nil->color = BLACK;
     root = nil;
     current = nil;
     num_pairs = D.num_pairs;
     preOrderCopy(D.root, D.nil);
}


Dictionary::~Dictionary()
{
     clear();
     delete nil;
}


 // Access functions  -------------------------------------------------------
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
     
     
     // create a new node to insert into RBT
     Node* new_Node = new Node(k,v);
     new_Node->left = nil;
     new_Node->right = nil;
     new_Node->color = RED;
     new_Node->parent = p;
     
     
     // if there is no root, then create a new node for the tree's root
     if (p == nil)
     {
          root = new_Node;
     }
     
     // if given key is smaller than parent key,then add it to left side
     else if (k < p->key)
     {
          p->left = new_Node;
     }
     
     // if given key is larger than parent key,then add it to right side     
     else
     {
          p->right = new_Node;
     }
     
     num_pairs += 1;
     
     RB_InsertFixUp(new_Node);
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
     
     // remove, but for RBT's
     RB_Delete(N); 
     
     N->left = nil;
     N->right = nil;
     N->parent = nil;
     
     delete N;
     num_pairs -= 1;
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



// Other Functions  ---------------------------------------------------------
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
          Dictionary temp(D);

          //Swap the copied dictionary fields with this dictionary fields
          std::swap(nil, temp.nil);
          std::swap(root, temp.root);
          std::swap(current, temp.current);
          std::swap(num_pairs, temp.num_pairs);     
     }
     
     return *this;
}


