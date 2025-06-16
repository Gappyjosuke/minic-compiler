# MiniC Compiler


[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A lightweight compiler for a C-like subset language, implemented in C. Designed for educational purposes with clean, modular architecture.


## Project Overview

- **Type**: Educational / Experimental Compiler
- **Language**: C
- **Architecture**: Single-pass, modular (Lexer → Parser → AST → Interpreter)
- **Goal**: Understand compiler internals by building a minimal C-like interpreter from scratch



## Current Phase

- [x] Lexer: Full tokenization with position tracking 
- [x] Parser: Recursive descent with operator precedence
- [x] AST: Visualizable tree structure
- [x] Interpreter: Complete runtime evaluation
- [x] Semantic Analysis: Variable declaration checks 
- [x] Error Handling: Improve syntax/runtime messages with line and column context Display source location in case of parse or runtime errors
- [ ] Type System (optional): Add support for `int`, `string`, and type checks  
- [ ] Codegen (optional): Generate assembly or bytecode for executio

🔧 **Recent Improvements**:
- Robust error handling system
- Relational operators (`<`, `<=`, `>`, `>=`, `==`, `!=`)
- Memory-safe string management
- Debug logging system

## Architecture

```mermaid
graph LR
    S[Source] --> L[Lexer]
    L --> P[Parser]
    P --> A[AST]
    A --> I[Interpreter]
    A --> C[Codegen *planned*]
    I --> O[Output]
```

## Features

### Lexer
  - Supports keywords: `int`, `let`, `print`
  - Identifiers, numeric literals
  - Operators: `+`, `-`, `*`, `/`, `=`,`==`, `!=`, `<`, `<=`, `>`,`>=`
  - Delimiters: `(`, `)`, `;`
  - Enhanced whitespace skipping and file-reading
  - Classifies `let` as `TOKEN_LET

---

### Syntax Analysis
```text
program     → statement*
statement   → decl | assign | print
decl        → 'let' ID '=' expr ';'
expr        → equality
equality    → comparison ( ('=='|'!=') comparison )*
comparison  → term ( ('<'|'<='|'>'|'>=') term )*
term        → factor ( ('+'|'-') factor )*
factor      → unary ( ('*'|'/') unary )*
unary       → ('-'|'+') unary | primary
primary     → NUM | ID | '(' expr ')'
```

---

### AST Generation + Debug Printer
  - Node Types:
    - `VarDecl`, `Assign`, `Print`
    - `BinaryOp`, `UnaryOp`, `Literal`, `Variable`
  -  UTF-8 visual tree printing with `print_ast()`

⚠️ To see tree-style AST properly, use a UTF-8 compatible terminal like:
- Windows Terminal
- VSCode integrated terminal
- Git Bash (mintty)
- Any Linux terminal (gnome-terminal, Konsole, etc.)

If your terminal shows `Γö£` or junk characters, it's a rendering issue, not a bug.

---

### Evaluator / Interpreter
- Evaluates AST in a simple runtime
- Tracks variable values with error checks
- Detects runtime issues:
  - undefined variables
  - Division by zero

---

### Semantic Analysis

- Verifies:
  - No use of undeclared variables
  - Valid assignments and usage
- Catches common runtime issues early

---

## Output
```text
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
Token: identifier   Lexeme: x          Value: 0
Token: =            Lexeme: =          Value: 0
Token: identifier   Lexeme: x          Value: 0
Token: +            Lexeme: +          Value: 0
Token: number       Lexeme: 5          Value: 5
Token: ;            Lexeme: ;          Value: 0
Token: print        Lexeme: print      Value: 0
Token: (            Lexeme: (          Value: 0
Token: identifier   Lexeme: x          Value: 0
Token: )            Lexeme: )          Value: 0
Token: ;            Lexeme: ;          Value: 0
Token: print        Lexeme: print      Value: 0
Token: (            Lexeme: (          Value: 0
Token: -            Lexeme: -          Value: 0
Token: identifier   Lexeme: x          Value: 0
Token: )            Lexeme: )          Value: 0
Token: ;            Lexeme: ;          Value: 0
Token: EOF          Lexeme: EOF        Value: 0
[DEBUG][PARSER] Created binary op node, op = 5
[DEBUG][PARSER] Created binary op node, op = 6
[DEBUG][PARSER] Created binary op node, op = 4
Created var decl node for x

AST:
AST:
├── VarDecl x
│   └── BinaryOp(+)
│       ├── Literal 2
│       └── BinaryOp(*)
│           ├── Literal 3
│           └── BinaryOp(-)
│               ├── Literal 4
│               └── Literal 1
├── Print
│   └── Variable x
├── Assign x
│   └── UnaryOp(+)
│       └── Literal 5
├── Print
│   └── Variable x
└── Print
    └── UnaryOp(-)
        └── Variable x

Output:
Starting interpretation...
Current node type: 0
Processing declaration of x
Evaluating expression type 3
Evaluating binary op: 4
Evaluating expression type 4
Evaluating expression type 3
Evaluating binary op: 6
Evaluating expression type 4
Evaluating expression type 3
Evaluating binary op: 5
Evaluating expression type 4
Evaluating expression type 4
Setting variable x to 11
Current node type: 2
Evaluating expression type 5
0
Current node type: 1
Evaluating expression type 6
Evaluating expression type 4
Setting variable x to 5
Current node type: 2
Evaluating expression type 5
5
Current node type: 2
Evaluating expression type 6
Evaluating expression type 5
-5
Interpretation completed successfully.
```

## Planned  Work

- [ ] **Type System (optional)**  
  - Add support for basic types like `string`, and possibly type checking

- [ ] **Code Generation (optional)**  
  - Generate pseudo-assembly or VM bytecode for portability or optimization

- [ ] **Control Flow**  
  - Support if, while, block {}

---

## Installation

```bash
git clone https://github.com/Gappyjosuke/minic-compiler.git
cd minic-compiler
make
./minic test/error.minic
```
# License
MIT License - See LICENSE for details.
