# MiniC Compiler

Lightweight compiler for a subset of the C language, written in C.  
Focused on clarity, structure, and educational value.

## Project Overview

- **Type**: Educational / Experimental Compiler
- **Language**: C
- **Architecture**: Single-pass, modular (Lexer → Parser → AST → Interpreter)
- **Goal**: Understand compiler fundamentals by building a simplified C-like interpreter from scratc

## Current Phase


- [x] Lexer: Tokenizes input using keywords, operators, symbols  
- [x] Parser: Parses expressions and statements, builds AST  
- [x] AST: Structured representation for evaluation  
- [x] Evaluator: Interprets AST and executes MiniC code  
- [ ] Error Handling: Add user-friendly syntax/runtime diagnostics  
- [ ] Type System (optional): Add support for `int`, `string`, and type checks  
- [ ] Codegen (optional): Generate assembly or bytecode for executio

## Features

### Implemented

- **Lexer / Tokenizer**
  - Supports keywords: `int`, `let`, `print`
  - Identifiers, numeric literals
  - Operators: `+`, `-`, `*`, `/`, `=`
  - Delimiters: `(`, `)`, `;`
  - Enhanced whitespace skipping and file-reading
  - Classifies `let` as `TOKEN_LET

- **Parser**
  - Recursive descent parsing
  - Supports:
    - Variable declarations using `let`
    - Arithmetic expressions with proper precedence
    - Assignment and `print(...)` statements
  - Constructs AST for each parsed input

- **AST Generation & Printer**
  - Builds AST nodes for:
    - Node types: `VarDecl`, `Print`, `BinaryOp`, `UnaryOp`, `Literal`, `Variable`
    - Visual debug output via `print_ast()`    
  - Prints structured AST for debugging/visual verification:

- **Evaluator / Interpreter**-
- Walks the AST and executes statements
- Supports:
  - Arithmetic evaluation
  - Variable declaration, assignment, and usage
  - Print statement execution
- Detects runtime issues:
  - Use of undefined variables
  - Division by zero

- **Input Support**
   - Source: `.minic` files
   - Output: Token stream with lexemes and token types

## Planned

- [ ] **Error Reporting**
  - Improve syntax/runtime messages with line and column context
  - Display source location in case of parse or runtime errors

- [ ] **Type System (optional)**  
  Add support for basic types like `int`, `string`, and possibly type checking

- [ ] **Code Generation (optional)**  
  Generate pseudo-assembly or VM bytecode for portability or optimization

## Output Temp
```text
 Raw input starts with: let x = 2 + 3 * (4 - 1);
 print(x);
 Token: let          Lexeme: let        Value: 0
 Token: identifier   Lexeme: x          Value: 0
 Token: =            Lexeme: =          Value: 0
 Token: number       Lexeme: 2          Value: 2
 Token: +            Lexeme: +          Value: 0
 Token: number       Lexeme: 3          Value: 3
 Token: *            Lexeme: *          Value: 0
 Token: (            Lexeme: (          Value: 0
 Token: number       Lexeme: 4          Value: 4
 Token: -            Lexeme: -          Value: 0
 Token: number       Lexeme: 1          Value: 1
 Token: )            Lexeme: )          Value: 0
 Token: ;            Lexeme: ;          Value: 0
 Token: print        Lexeme: print      Value: 0
 Token: (            Lexeme: (          Value: 0
 Token: identifier   Lexeme: x          Value: 0
 Token: )            Lexeme: )          Value: 0
 Token: ;            Lexeme: ;          Value: 0
 Token: EOF          Lexeme: EOF        Value: 0
 [DEBUG] Created binary op node, type = 3, op = 5
 [DEBUG] Created binary op node, type = 3, op = 6
 [DEBUG] Created binary op node, type = 3, op = 4
 
 AST:
 AST: VarDecl x = ...
 BinaryOp(+)
  Left: AST: Literal 2
  Right: BinaryOp(*)
  Left: AST: Literal 3
  Right: BinaryOp(-)
  Left: AST: Literal 4
  Right: AST: Literal 1
  AST: Print AST: Variable x

 Output:
 11
```

## Installation

```bash
git clone https://github.com/Gappyjosuke/minic-compiler.git
cd minic-compiler
make
./minic test/example.minic
