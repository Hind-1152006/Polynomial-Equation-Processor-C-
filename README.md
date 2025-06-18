# Polynomial Equation Processor (C++)

This project reads pairs of polynomial equations from a file, validates them, displays each polynomial in human-readable form, and calculates their **sum** and **difference**.

## 📂 File Structure
- `main.cpp` → C++ source file
- `input.txt` → Input file containing polynomial data

## 🧮 What It Does
For each pair of polynomials, the program:
1. Reads the degree and right-hand side value
2. Reads coefficients for each polynomial
3. Displays each polynomial nicely (e.g., `3x^2 + 2x + 5 = 10`)
4. Computes:
   - Their **sum** (coefficient-wise + RHS)
   - Their **difference** (coefficient-wise - RHS)
5. Handles input errors gracefully

