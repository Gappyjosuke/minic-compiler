# MiniC Compiler

Lightweight compiler for a subset of the C language, written in C.  
Focused on clarity, structure, and educational value.

## Project Overview

- Type: Educational Compiler Project
- Language: C
- Goal: Build a simplified C compiler from scratch
- Design: Single-pass, modular phases

## Current Phase


- [x] Lexer: Tokenize basic MiniC syntax
- [x] Parser: Parse declarations, expressions, print statements
- [x] AST: Build and debug-print AST
- [ ] Evaluator: Interpret the AST and execute code
- [ ] Error Handling: Clear syntax/runtime error reporting
- [ ] Type System (optional): Add basic types like `int`, `string`
- [ ] Codegen (optional): Generate assembly or bytecode

## Features

### Implemented

- **Lexer / Tokenizer**
  - Supports keywords: `int`, `let`, `print`
  - Identifiers, numeric literals
  - Operators: `+`, `-`, `*`, `/`, `=`
  - Delimiters: `(`, `)`, `;`
  - Enhanced whitespace skipping and file-reading
  - Classifies `let` as `TOKEN_LET

- **Recursive Descent Parser**
  - Parses simple expressions and statements
  - Checks syntax correctness
  - Builds a base structure for upcoming AST generation

- **AST Generation & Printer**
  - Builds AST nodes for:
    - Variable declarations (`VarDecl`)
    - Print statements
    - Binary and assignment expressions
  
  - Prints structured AST for debugging/visual verification:
    ```text
    AST:
    AST: VarDecl x = ...
    AST: VarDecl y = ...
    AST: VarDecl z = ...
    AST: Print (...)
    ```

- **Input Support**
   - Source: `.minic` files
   - Output: Token stream with lexemes and token types

### Planned

- [ ] **Evaluator**  
  Interpret the AST and execute the program directly (like a scripting language runtime)

- [ ] **Error Handling**  
  Clear syntax error messages and runtime error diagnostics

- [ ] **Type System (optional)**  
  Add support for basic types like `int`, `string`, and possibly type checking

- [ ] **Code Generation (optional)**  
  Generate pseudo-assembly or VM bytecode for portability or optimization


## Installation

```bash
git clone https://github.com/Gappyjosuke/minic-compiler.git
cd minic-compiler
make
./minic test/example.minic
