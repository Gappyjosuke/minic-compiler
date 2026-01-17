<div align="justify">

[*← Back to Expeiments Index*](/Experiments/README.md)


# Experiment 01: The Lexical Frontier (Using the LEX Tool)

Welcome to the first true step of building a compiler! In our previous era, we manually scanned for patterns. Now, we are stepping into the modern era of [Language 
Engineering](https://en.wikipedia.org/wiki/Language_engineering) by using **LEX (Lexical Analyzer Generator)**.

### A Quick Bit of History

Back in the mid-1970s, **Mike Lesk** and **Eric Schmidt** developed LEX at Bell Labs as part of the Unix research effort. Writing hand-coded character-by-character scanners using long `if-else` chains was tedious and error-prone, so they introduced a tool that allowed programmers to *describe* lexical patterns using regular expressions. LEX would then generate the corresponding C code automatically. This same idea lives on today in tools like **WinFlexBison** and its Windows ports, where we describe what tokens look like and let the tool handle the low-level scanning logic.

---
## What is the Purpose of this Experiment?

The goal is to move from manual character-checking to [Pattern Matching](https://en.wikipedia.org/wiki/Pattern_matching). We want to develop a tool that recognizes the "Pieces" of the C language—**Identifiers**, **Keywords**, and **Operators**—while simultaneously building a **Symbol Table**.

### Why the Symbol Table?

Imagine reading a book but forgetting the characters' names as soon as you turn the page. You wouldn't understand the story! A [Symbol Table](https://en.wikipedia.org/wiki/Symbol_table) is the compiler's memory. Every time our Lexer finds a new variable name (Identifier), it stores it in a table (like a 2D array). This ensures that in later stages, the compiler knows exactly which "entities" exist in your program.

---

## How it Works : The LEX Pipeline

When you write a file with a `.l` extension, you aren't writing pure C; you are writing a set of rules called [Regular Expressions](https://en.wikipedia.org/wiki/Regular_expression). 



* **The Pattern Matcher :**  We tell LEX that an **Identifier** is any string starting with a letter or underscore, followed by alphanumeric characters.

* **The Filter :**  We instruct the program to ignore "noise" like whitespaces so it only focuses on the meaningful parts of the code.

* **The Result :**  When LEX finds a match, it executes C functions like `insertSymbol()` to check if we’ve seen this variable before and add it to our "address book" if it's new.

---

## Folder Breakdown

**`lexer.l`**: This is your "Specification File." It contains the rules for recognizing `int`, `float`, and operators like `+` or `=`.

**`lex.yy.c`**: You don't write this file! **Win_Flex** generates this from your `.l` file. It is a massive, complex C program that implements a [DFA (Deterministic Finite Automaton)](https://en.wikipedia.org/wiki/Deterministic_finite_automaton) to scan your code at high speed.

**`input.c`**: Your test subject. It contains the C code patterns you want to recognize.

---

## Execution Procedure

Follow these steps to transform your logic into a working binary:

```bash
# 1. Generate the C source code from your LEX rules
win_flex lexer.l

# 2. Compile the generated C file using GCC
gcc lex.yy.c -o lexer.exe

# 3. Feed your sample code into the analyzer
lexer.exe < input.c
```
---

## What to expect?

After the scan, the terminal will print out every token it found. Finally, it will display the Symbol Table, listing every unique variable name (identifier) collected during the process.

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)
[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)


</div>