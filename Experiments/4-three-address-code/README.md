<div align="justify">

[*← Back to Expeiments Index*](/Experiments/README.md)


#  Experiment 04: Generating Three Address Code (TAC)

In our previous labs, we built a "Master Calculator" that could understand and execute code. But real compilers don't just "run" the code; they translate it into a simplified, universal language that the computer's hardware can eventually understand. This simplified language is called **Three Address Code (TAC)**.

###  The Bridge to Machine Code

From the 1960s onward, as programming languages and hardware architectures became more complex, compiler designers introduced [Intermediate Representations (IR)](https://en.wikipedia.org/wiki/Intermediate_representation). Instead of translating source code directly to machine code, compilers first convert it into a machine-independent intermediate form. This makes it easier to perform optimizations and to retarget the compiler to different processors. Simple forms like Three-Address Code (TAC) are classic examples used to represent program logic before it is finally lowered to machine instructions (0s and 1s).

---

##  What is Three Address Code?

In [Three Address Code](https://en.wikipedia.org/wiki/Three-address_code), every instruction has at most three "addresses" (two for operands and one for the result). For example, a complex line like `x = a + b * c` is too crowded for a CPU to handle in one go. The compiler breaks it down into small, bite-sized steps:

1.  `t1 = b * c` (Temporary variable 1)

2.  `t2 = a + t1` (Temporary variable 2)

3.  `x = t2` (Final assignment)



###  Handling Logic (Labels & Jumps)

When it comes to `if-else` statements, TAC uses **Labels** (like `L1`, `L2`) and **GOTO** statements. This mimics how a CPU jumps from one part of memory to another based on a condition, effectively flattening the high-level logic into a linear list of commands.



---

##  The System: The TAC Factory

This experiment uses LEX and YACC as an "Assembly Line" to manufacture these instructions.

1.  **The Scout (`tacgen.l`):** Identifies the raw materials—numbers, variables, and keywords like `if` and `else`.

2.  **The Architect (`tacgen.y`):** This is where the magic happens. Every time the parser recognizes a math operation, it automatically creates a new "Temporary Variable" (`t1`, `t2`, etc.) and prints out the instruction string.

3.  **The Counter:** We maintain internal counters so that every temp variable and every jump label has a unique name, ensuring the "jump" logic never gets confused.

---

##  Folder Contents & Logic

* **`tacgen.l`**: The Lexer. It tokenizes symbols, relational operators (`<`, `>`), and identifiers.

* **`tacgen.y`**: The Parser. It contains the **Syntax Directed Translation (SDT)** rules that print the TAC strings.

* **`input.txt`**: Your test script. Try a complex structure to see how it "unrolls":
  ```c
  x = a + b * c;
  if (x < 10) y = x + 1;
  else y = x - 1;

  ```
---

## Execution Procedure

Open your terminal and watch your high-level code get "disassembled" into intermediate code:

```bash
# 1. Generate the Parser (TAC Generator) files
win_bison -d -v tacgen.y

# 2. Generate the Lexer files
win_flex tacgen.l

# 3. Compile the TAC Engine
gcc lex.yy.c tacgen.tab.c -o tacgen.exe

# 4. Run the generator against your input file
./tacgen.exe < input.txt
```

## The Result

The program will output a list of simple, linearized instructions. This is the exact "blueprint" that a [Code Optimizer](https://en.wikipedia.org/wiki/Optimizing_compiler) would use in the next phase of the compiler to make your program run faster and consume less memory!

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)
[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>