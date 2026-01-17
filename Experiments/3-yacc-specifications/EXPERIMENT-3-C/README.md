<div align="justify">

[*← Back to Experiments Index*](/Experiments/README.md)


# Experiment 03(C): Syntax Analysis - Recognizing Control Structures

In this experiment, we level up our parser to recognize the "Big Decisions" in code. We are moving beyond simple lines of math and into the realm of [Control Flow](https://en.wikipedia.org/wiki/Control_flow). This is where the compiler identifies the loops and branches that make a program dynamic.

### The Backbone of Programming

In the mid-1960s, the **Böhm–Jacopini theorem** showed that any algorithm can be expressed using just three control structures: sequence, selection (`if/else`), and iteration (`while or for`). This result laid the foundation for structured programming. By teaching our parser to recognize these [Control Structures](https://en.wikipedia.org/wiki/Control_flow), we enable it to understand the core syntactic building blocks from which most program logic is constructed, even though additional features and semantics are handled at later stages.

---

##  What are we actually doing?

The goal is to build a parser that can read a block of code and identify the logical "containers" used. We want the computer to see `if (x > 0)` and not just see words, but realize, *`"Aha! This is a conditional branch."`*

###  The Logic Gates we are Identifying:

Our tool is designed to spot the `" if " "else" "for" "while" "do-while" "switch"` of the C language:

1.  **Selection:** `if` and `else` (The fork in the road).

2.  **Iteration:** `for`, `while`, and `do-while` (The loops).

3.  **Multi-way Branching:** `switch` (The complex decision maker).



---

##  The Logic: How LEX & YACC See Structure

This experiment works by breaking the code down into a hierarchy:

1.  **The LEX Layer (`control_lex.l`):** LEX acts as the "Keyword Spotter." It scans the text specifically looking for the reserved words defined in the C standard. When it sees `while`, it doesn't just call it a word; it sends a unique token called `WHILE` to the parser.

2.  **The YACC Layer (`control_parser.y`):** This is the "Architect." It doesn't care about the variables inside the parentheses yet; it cares about the structure. It looks for the pattern: `IF` + `(` + `CONDITION` + `)` + `{` + `BODY` + `}`. If it finds that pattern, it confirms it as a valid Control Structure.



---

##  Folder Contents & Logic

* **`control_lex.l`**: The Lexer. It is programmed to ignore variable names and numbers, focusing purely on identifying keywords like `if`, `else`, and `switch`.

* **`control_parser.y`**: The Parser. This defines the grammar for how these keywords should be placed (e.g., an `else` must always follow an `if`).

* **`input.txt`**: A test file containing nested structures (like a `while` loop inside an `if` statement) to test the parser's depth.

---

##  Execution Procedure

Run the generation and compilation pipeline to build your Control Structure Detector:

```bash
# 1. Generate the Parser (The Architect) files
win_bison -d -v control_parser.y

# 2. Generate the Lexer (The Spotter) files
win_flex control_lex.l

# 3. Compile the structural engine
gcc lex.yy.c control_parser.tab.c -o control.exe

# 4. Feed the complex input file into the program
./control.exe < input.txt
```
---

## The Result

The program will scan your code and announce every structure it discovers. For example, if it reads your `input.txt`, it will output:

* `Recognized: IF statement`

* `Recognized: WHILE loop`

* `Recognized: DO-WHILE loop`

This confirms that the compiler's "eyes" are now working at a structural level rather than just looking at individual words!

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)

[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>
