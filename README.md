# C++ at 42 Berlin

## Introduction

C++ is a powerful, low-level programming language that builds on C by introducing object-oriented programming (OOP), stronger type safety, and abstraction mechanisms.  
At **42 Berlin**, the C++ curriculum is designed to progressively teach students modern C++ concepts while enforcing strict discipline in memory management, design, and compilation rules.

The C++ modules (CPP 00 → CPP 09) focus on understanding **how C++ works under the hood**, rather than relying on high-level conveniences.

---

## Structure of the C++ Modules

The C++ curriculum at 42 consists of **10 modules**, each building upon the previous one.

### CPP Module 00 — Basics of C++
- Classes and member functions
- Input/output streams (`std::cout`, `std::cin`)
- Initialization lists
- Orthodox Canonical Form (OCF)
- Basic Makefiles

---

### CPP Module 01 — Memory Allocation
- Stack vs heap memory
- `new` and `delete`
- References vs pointers
- Object lifetime
- Zombie objects
- Preventing memory leaks

---

### CPP Module 02 — Ad-hoc Polymorphism
- Operator overloading
- Copy constructor and assignment operator
- Const correctness
- Fixed-point number implementation

---

### CPP Module 03 — Inheritance
- Base and derived classes
- Access specifiers (`public`, `protected`, `private`)
- Method overriding
- Class hierarchies

---

### CPP Module 04 — Subtype Polymorphism
- Virtual functions
- Virtual destructors
- Abstract classes and interfaces
- Runtime polymorphism using base class pointers

---

### CPP Module 05 — Exceptions
- `try`, `catch`, and `throw`
- Custom exception classes
- Exception safety
- `std::exception`

---

### CPP Module 06 — Casting
- `static_cast`
- `dynamic_cast`
- `const_cast`
- `reinterpret_cast`
- Type conversion rules and pitfalls

---

### CPP Module 07 — Templates
- Function templates
- Class templates
- Generic programming
- Template instantiation

---

### CPP Module 08 — STL Containers
- Standard containers (`vector`, `list`, `map`, `stack`, etc.)
- Iterators
- Algorithms
- When and how to use STL correctly

---

### CPP Module 09 — STL in Practice
- Applying STL to real problems 
- Performance considerations
- Combining containers and algorithms
- Advanced exercises using STL

CPP09 focuses on applying STL containers and algorithmic reasoning to solve a real-world problem.  
By implementing the Ford–Johnson (merge-insertion) sorting algorithm, students learn how to optimize comparisons, manage different containers, and measure performance accurately. This module reinforces careful design, efficiency, and a deeper understanding of how algorithms behave in practice.

---

## Key Rules and Constraints

- **C++ standard:**  
  ```bash
  c++ -Wall -Wextra -Werror -std=c++98
  ```

## Author

Developed by **Huayun Ai**  
Student at **42 Berlin**

## License

This project is part of the **42 curriculum** and was developed for educational purposes
Reuse, modification, and distribution may be subject to **42 school policies**.  

