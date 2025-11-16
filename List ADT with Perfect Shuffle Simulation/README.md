# List ADT with Perfect Shuffle Simulation (C++ Project)

This project implements a fully custom **List Abstract Data Type (ADT)** in C++ using a doubly linked structure with a movable cursor. The List ADT supports insertion, deletion, traversal, searching, cleanup, concatenation, and full operator overloading. The main program, `Shuffle.cpp`, uses this List ADT to simulate **perfect shuffles** on a sequence of integers and determine how many shuffles are required to restore the list to its original order.

The repository demonstrates class design, linked data structures, cursor-based navigation, operator overloading, modular C++ programming, and algorithmic simulation.

---

## 📁 Files Included

### **List.h**
Header file defining the List ADT interface.  
Includes:
- Private `Node` struct  
- Cursor-based navigation system  
- All public member functions  
- Operator overloads (`<<`, `==`, `=`)  
:contentReference[oaicite:0]{index=0}

---

### **List.cpp**
Implementation of the List ADT.  
Defines:
- Node creation  
- insertBefore / insertAfter  
- moveFront / moveBack / moveNext / movePrev  
- eraseBefore / eraseAfter  
- findNext / findPrev  
- cleanup (duplicate removal)  
- concat  
- copy constructor, destructor, and assignment operator  
:contentReference[oaicite:1]{index=1}

---

### **ListTest.cpp**
Standalone test client used to validate all List operations, including:
- Cursor movement  
- Insert/delete correctness  
- Equality checking  
- Exception handling  
- Cleanup and concatenation behavior  
:contentReference[oaicite:2]{index=2}

---

### **Shuffle.cpp**
Main driver program implementing a **perfect shuffle** algorithm.  
It:
1. Builds a list of integers from `1` to `n`  
2. Saves an original copy  
3. Performs a perfect shuffle by splitting the list and weaving halves together  
4. Counts how many shuffles return the list to its original ordering  
5. Prints a formatted output table  

This program demonstrates practical use of the List ADT in a real algorithmic simulation.  
:contentReference[oaicite:3]{index=3}

---

### **Makefile**
Automates compilation of all `.cpp` files and builds:
- `Shuffle` (main client)
- `ListTest` (test client)

Ensures proper dependency handling and rebuild options.

---

## 🧠 Concepts Demonstrated
- Custom doubly linked list design  
- Cursor-based list manipulation  
- Operator overloading in C++  
- Deep copying and destructor logic  
- Perfect shuffle simulation  
- Modular multi-file project structure  
- Exception safety and edge-case handling  

---

## ▶️ Build Instructions
```bash
make
