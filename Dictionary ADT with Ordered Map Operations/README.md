# Dictionary ADT with Ordered Map Operations (C++ BST Implementation)

This project implements a full **Dictionary Abstract Data Type (ADT)** in C++ using a Binary Search Tree (BST) with an internal iterator for in-order and reverse-order traversal. The Dictionary supports key–value insertion, deletion, search, iterators, deep copying, and multiple string representations (in-order and pre-order). The main client (`Order.cpp`) reads strings from an input file, stores them with associated line numbers, and outputs two ordered representations of the dictionary.

This project demonstrates data structure engineering, recursion, tree-based algorithms, and clean modular C++ programming.

---

## 📁 Files Included

### **Dictionary.h**
Defines the Dictionary ADT interface, including:
- `keyType` and `valType` typedefs  
- The private `Node` struct (key, value, parent, left, right)  
- Helper functions for search, traversal, and tree manipulation  
- Public access, modification, iterator, and string-generation functions  
- Overloaded operators (`<<`, `==`, `=`)  
:contentReference[oaicite:0]{index=0}

---

### **Dictionary.cpp**
Implements the full Dictionary ADT using a Binary Search Tree.  
Includes:
- Node creation and pointer wiring  
- `setValue()`, `remove()`, and `clear()`  
- `search`, `findMin`, `findMax`, `findNext`, `findPrev`  
- Recursive in-order and pre-order string generation  
- Iterator support (`begin`, `end`, `next`, `prev`)  
- Copy constructor, destructor, and assignment operator  
:contentReference[oaicite:1]{index=1}

---

### **DictionaryTest.cpp**
Comprehensive test client for the Dictionary ADT.  
Tests:
- Deep copying  
- Equality operator  
- Value modification  
- Removal cases  
- Forward and reverse iteration  
- Exception handling  
:contentReference[oaicite:2]{index=2}

---

### **Order.cpp**
Main program that uses the Dictionary ADT to:
1. Read each line from an input file  
2. Insert the line as a key with its line number as the value  
3. Print the dictionary in **sorted (in-order)** form  
4. Print the dictionary in **pre-order traversal** form  
:contentReference[oaicite:3]{index=3}

This program demonstrates ordered map behavior and dictionary traversal output formats.

---

### **Makefile**
Build script that compiles:
- `Order` (main client)
- `DictionaryTest` (test suite)

Supports automatic rebuilding and dependency handling.

---

## 🧠 Concepts Demonstrated
- Binary Search Tree implementation  
- Ordered map/dictionary operations  
- Recursive search, traversal, and deletion  
- In-order / pre-order tree string generation  
- Iterators for forward and backward iteration  
- Operator overloading in C++ (`==`, `<<`, `=`)  
- Exception handling and robust error checks  
- Modular OOP design

---

## ▶️ Build Instructions
```bash
make
