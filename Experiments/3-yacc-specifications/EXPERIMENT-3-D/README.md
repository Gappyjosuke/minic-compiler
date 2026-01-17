<div align="justify">

[*← Back to Expeiments Index*](/Experiments/README.md)


# Experiment 03(D): The Master Calculator (Advanced LEX & YACC)

In our previous labs, we built separate tools to recognize math, validate names, and identify control structures. Now, we are merging all those features into one powerful program: a **C-style Calculator**. This isn't just a simple math tool; it's a program that understands variables, remembers their values, and recognizes the logic of C code.

###  The Birth of the "Interpreter"

What we are building today is the foundation of an [Interpreter](https://en.wikipedia.org/wiki/Interpreter_(computing)). While a compiler translates code into machine language for later use, an interpreter like yours reads the code and executes it immediately. Think of it as a baby version of **Python** or **JavaScript**—languages that process and calculate as they go!

---

## What are we actually doing?

The goal is to create a tool that acts as a complete processing unit. It doesn't just look at the code; it interacts with it.

### The Integrated System:

This experiment brings together three massive components:
1.  **Expression Solver :** It calculates complex math like `(10 + 5) * 2`.

2.  **Memory Management :** Using a **Symbol Table**, it can handle assignments like `x = 10;`. Later, if you type `x + 5`, it remembers that `x` is `10` and gives you `15`.

3.  **Structure Recognition :** It identifies `if`, `while`, and `for` blocks, proving it understands the "skeleton" of a C program even before it executes the logic.


---

## The Architecture: How it fits together

This experiment uses a "Triple-Threat" file structure to manage complexity:

* **The Scout (`lexical3.l`) :** Scans the code and identifies keywords, numbers, and operators.

* **The Brain (`parser.y`) :** The grammar rules. It decides that `IDENTIFIER = EXPRESSION` is a valid assignment and tells the computer to update the memory.

* **The Memory (`symbol_table.h`) :** A custom header file. This is where we define the C structures used to store variable names and their current numerical values.



---

## Folder Contents & Logic

* **`lexical3.l`**: The advanced Lexer. It now handles relational operators (`==`, `!=`) and keywords simultaneously.

* **`parser.y`**: The sophisticated Parser. It contains the logic to "calculate" and "assign" values using the results from the lexer.

* **`symbol_table.h`**: The "Memory Bank." It contains C functions to `insert`, `update`, and `retrieve` data so the program has "state."

* **`input.c`**: Your test file. Try writing a small script:
  ```c
  x = 10;
  y = 20;
  z = x + y * 2;
  if (z > 40) { return z; }

  ```
---

## Execution Procedure

Since we are linking multiple C components and a custom header, the compilation process is specific:

```bash
# 1. Generate the Parser (Bison) files
win_bison -d -v parser.y

# 2. Generate the Lexer (Flex) files
win_flex lexical3.l

# 3. Compile the Lexer, Parser, and Symbol Table logic together
gcc lex.yy.c parser.tab.c -o calc.exe

# 4. Run the master calculator and pipe in your code
./calc.exe < input.c
```

## The Result

When you run this, the program will process your `input.c` line by line. It will calculate the values of your variables in real-time. At the end, the program will display the **Final Symbol Table**, showing you exactly what the "mind" of your compiler currently remembers.

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)
[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>