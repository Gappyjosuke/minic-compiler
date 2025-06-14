# MiniC Compiler

Lightweight compiler for a subset of the C language, written in C.  
Focused on clarity, structure, and educational value.

## Project Overview

- Type: Educational Compiler Project
- Language: C
- Goal: Build a simplified C compiler from scratch
- Design: Single-pass, modular phases

## Current Phase

- [x] Lexical Analysis (Lexer)
- [x] Syntax Analysis (Parser)
- [ ] AST Generation
- [ ] Code Generation

## Features

### Implemented

- Tokenizer
  - Handles keywords, identifiers, numbers, operators, delimiters

- Recursive Descent Parser
  - Parses simple expressions and statements
  - Checks syntax correctness
  - Builds a base structure for upcoming AST generation

- Source: `.minic` files
- Output: Token stream with lexemes and token types

### Planned

- AST node builder
- Stack-based code generation

## Installation

```bash
git clone https://github.com/Gappyjosuke/minic-compiler.git
cd minic-compiler
make
./minic test/example.minic
