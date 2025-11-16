# Dictionary ADT with Red-Black Tree & Text Processing Clients

This project implements a fully functional **Dictionary Abstract Data Type (ADT)** backed by a **Red-Black Tree (RBT)** to support efficient insertion, deletion, lookup, and ordered traversal.  
Two client programs—**Order** and **WordFrequency**—demonstrate real applications of the Dictionary ADT, including sorting input lines and computing word frequencies from text files.

---

## 📁 Submitted Files

### **1. Dictionary.h**
Header file defining the public interface of the Dictionary ADT.  
Includes:
- `keyType` and `valType` type definitions  
- Node structure definition  
- Public methods for insertion, deletion, lookup, iteration, and printing  
- Iterator support for forward and reverse traversal  

> Only the helper function section may be modified; the rest is provided and should remain unchanged.

---

### **2. Dictionary.cpp**
Main implementation of the Dictionary ADT using a **Red-Black Tree**.  
Implements:
- Balanced insertions and deletions  
- Tree rotations and RBT fix-up operations  
- Search, lookup, ordered iteration  
- `to_string()` and `pre_string()` output formats  
- Overloaded operators (`<<`, `==`, `=`)

This file contains the core logic and constitutes the majority of the project's work.

---

### **3. DictionaryTest.cpp**
A comprehensive test client for validating the Dictionary ADT.  
It checks:
- Insertion and deletion  
- Copy constructor, assignment operator, equality operator  
- Forward and reverse iteration  
- Error handling and exception correctness  

Ensures the ADT behaves correctly under various scenarios.

---

### **4. Order.cpp**
A client program that:
- Reads lines from an input file  
- Stores each line in the Dictionary with its line number  
- Outputs:
  - The Dictionary in sorted (in-order) order  
  - A pre-order traversal showing the RBT structure  

Useful for verifying ordering and tree structure.
:contentReference[oaicite:0]{index=0}

---

### **5. WordFrequency.cpp**
A text-processing client that:
- Reads text from an input file  
- Tokenizes words while ignoring punctuation and digits  
- Converts all words to lowercase  
- Counts occurrences using the Dictionary  
- Outputs word frequencies in alphabetical order

Demonstrates a real-world application of the Dictionary ADT for text analysis.  
:contentReference[oaicite:1]{index=1}

---

### **6. Makefile**
Automates the compilation of the entire project.  
Targets include:
- Building each executable  
- Cleaning compiled artifacts  

Ensure dependency lists match all required `.cpp` files.

---

## 🧠 Project Concepts

- **Balanced Search Trees (Red-Black Trees)**  
- **Ordered Maps & Dictionaries**  
- **File Parsing and Tokenization**  
- **Iterator Design (forward & reverse)**  
- **Operator overloading in C++**  
- **Efficient text-processing utilities**

---

## 🚀 How to Build and Run

```bash
make
./Order input.txt output.txt
./WordFrequency input.txt output.txt
