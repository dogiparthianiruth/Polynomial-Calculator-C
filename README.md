# Polynomial Calculator in C

A menu-driven Polynomial Calculator implemented in C using a Singly Linked List. The application supports various polynomial operations such as addition, subtraction, multiplication, division, differentiation, and evaluation while maintaining terms in descending order of exponents.

---

## Features

- Polynomial Addition
- Polynomial Subtraction
- Polynomial Multiplication
- Polynomial Division (Quotient and Remainder)
- Polynomial Differentiation
- Polynomial Evaluation
- Display Polynomials
- Dynamic Memory Management
- Automatic Merging of Like Terms
- Sorted Polynomial Representation

---

## Data Structure Used

- Singly Linked List

Each node stores:
- Coefficient
- Exponent
- Pointer to the Next Node

---

## Operations Supported

| Operation | Description |
|-----------|-------------|
| Enter Polynomial | Create a polynomial by entering terms |
| Display | Display stored polynomials in standard mathematical form |
| Addition | Add two polynomials |
| Subtraction | Subtract one polynomial from another |
| Multiplication | Multiply two polynomials |
| Division | Perform polynomial long division |
| Derivative | Compute the derivative of a polynomial |
| Evaluation | Evaluate a polynomial for a given value of x |

---

## Menu

```text
--- Polynomial Calculator ---

1. Enter P1
2. Enter P2
3. Display
4. Add
5. Subtract
6. Multiply
7. Divide
8. Derivative of P1
9. Evaluate P1
0. Exit
```

---

## Technologies Used

- C Programming
- Singly Linked Lists
- Dynamic Memory Allocation
- Standard C Library
- Mathematical Functions (`math.h`)

---

## Compilation

```bash
gcc polynomial_calculator.c -o polynomial_calculator -lm
```

---

## Execution

```bash
./polynomial_calculator
```

On Windows (MinGW):

```bash
polynomial_calculator.exe
```

---

## Sample Input

```text
Enter number of terms: 3

Term 1: 5 4
Term 2: 2 2
Term 3: 3 0
```

## Sample Output

```text
Polynomial:
5.00x^4 + 2.00x^2 + 3.00
```

---

## Concepts Demonstrated

- Linked Lists
- Dynamic Memory Allocation
- Pointer Manipulation
- Polynomial Arithmetic
- Mathematical Algorithms
- Memory Management

---

## Future Enhancements

- Polynomial Integration
- Save and Load Polynomials from Files
- Graphical Visualization
- Polynomial Comparison
- Support for Multiple Stored Polynomials
- Improved User Interface

---

## Developer

**Dogiparthi Aniruth**

CMR College of Engineering & Technology (CMRCET)

---

## License

This project is licensed under the MIT License.