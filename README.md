# Compiler for E++ Language

## Overview
This project implements a compiler for the E++ language, a simple language of arithmetic expressions. The compiler parses E++ code, generates an Abstract Syntax Tree (AST), and produces output in a target stack-based assembly language (Targ). This builds upon a prior expression evaluator, enhancing it with efficiency and additional features.

## Features
- **Expression Parsing**: Converts E++ expressions into an AST, supporting:
  - Arithmetic operations (e.g., addition, multiplication).
  - Variable assignments and two new statements:
    - **Delete**: Removes variables from memory.
    - **Return**: Stops execution and outputs the final result.
- **Optimized Symbol Table**:
  - Implemented using AVL Trees for efficient operations (O(log n)).
  - Dynamically allocates and deallocates memory for variables.
- **Code Generation**:
  - Produces Targ assembly code for a stack-based machine.
  - Supports operations like `PUSH`, `ADD`, `SUB`, `MUL`, `DIV`.
- **Memory Management**:
  - Implements a stack-like memory allocator for variable mapping.
  - Bonus: Supports a min-heap-based memory allocator for optimal memory usage.

## Directory Structure
- **`src`**: Contains the source code for the compiler.
- **`include`**: Header files defining key classes like `Parser`, `EPPCompiler`, and `SymbolTable`.
- **`samples`**: Sample E++ and Targ files for testing.
- **`tests`**: Basic test cases for validating compiler functionality.

## Getting Started

### Building the Compiler
Run the following command from the project root:
```bash
make
