# BigInteger Arbitrary-Precision Arithmetic (C++ ADT Implementation)

This project implements a full arbitrary-precision integer arithmetic system in C++, built on top of a custom doubly-linked List ADT. It supports addition, subtraction, multiplication, comparison, sign handling, and string conversion for integers far larger than native C++ types allow. The project includes complete test suites for both List and BigInteger ADTs, along with a high-level client (`Arithmetic.cpp`) that performs large-number arithmetic using input/output files.

---

## 📁 Project Structure

### **List ADT**
- **List.h**  
  Defines the `List` class interface, node structure, cursor operations, and public method prototypes.  
- **List.cpp**  
  Implements all List operations including insertion, deletion, cursor movement, cleanup, concatenation, and equality checks.  
  *(Source reference: :contentReference[oaicite:0]{index=0})*

### **BigInteger ADT**
- **BigInteger.h**  
  Defines the `BigInteger` class, its data members (sign + digit list), and the full set of arithmetic and comparison operators.  
  *(Source reference: :contentReference[oaicite:1]{index=1})*

- **BigInteger.cpp**  
  Implements all BigInteger operations:  
  - Addition, subtraction, multiplication  
  - Sign normalization  
  - Conversion to/from strings  
  - Operator overloads (`+`, `-`, `*`, `==`, `<`, etc.)  
  Includes helper List-based vector arithmetic.  
  *(Source reference: :contentReference[oaicite:2]{index=2})*

### **Test Clients**
- **ListTest.cpp**  
  Unit tests verifying the correctness of the List ADT operations.

- **BigIntegerTest.cpp**  
  Tests arithmetic correctness using very large integers, comparison operators, and edge cases (invalid input, empty strings).  
  *(Source reference: :contentReference[oaicite:3]{index=3})*

### **Top-Level Client**
- **Arithmetic.cpp**  
  Reads two large integers from an input file, performs all required arithmetic operations, and outputs the results.  
  Demonstrates real-world usage of the BigInteger ADT.  
  *(Source reference: :contentReference[oaicite:4]{index=4})*

### **Makefile**
Automates compilation of all source files, producing executables for the ADT and test clients.

---

## 🚀 Features
- Handles integers of **arbitrary size** (beyond 64-bit limits)  
- Fully supports:  
  - Addition  
  - Subtraction  
  - Multiplication  
  - Comparison operators  
  - Sign handling  
  - Zero normalization  
- Uses a custom List-based vector arithmetic backend  
- Includes robust error checking and exception handling  
- Comprehensive test suites included  

---

## 🧪 How to Build & Run

```bash
make
./Arithmetic <input.txt> <output.txt>
./ListTest
./BigIntegerTest
