<div align="justify">

[*← Back to Experiments Index*](/Experiments/README.md)


# Experiment 03(A): Syntax Analysis - The Math Decoder

In the previous labs, we built a Lexer to identify individual words (tokens). But a list of words like `3`, `+`, and `5` doesn't mean anything until we arrange them into a sentence. This experiment introduces **YACC (Yet Another Compiler-Compiler)** to help us determine if a mathematical expression is logically valid.

### The Power of the "Context-Free Grammar"

In the 1950s, [Noam Chomsky](https://en.wikipedia.org/wiki/Noam_Chomsky) introduced [Context-Free Grammars (CFG)](https://en.wikipedia.org/wiki/Context-free_grammar), revolutionizing linguistics and laying the groundwork for formal language theory. Computer scientists soon realized that CFGs were an excellent way to define the syntax of programming languages. By specifying a small set of grammatical "rules" such as how expressions can be combined—a parser can recognize and structure infinitely many valid programs. While CFGs precisely describe syntax, additional semantic checks are required to enforce meaning, types, and scope.

---

## What are we actually doing?

The goal here is to recognize and **evaluate** a valid arithmetic expression. We aren't just checking if `3 + 5` is written correctly; we are actually making the computer calculate the answer.

### The Tag Tools: LEX + YACC
This experiment is a collaboration between two powerful tools:

1.  **LEX (The Scout):** Scans the input and says, *` "Hey, I found a number (3), an operator (+), and another number (5)."`*

2.  **YACC (The Judge):** Takes those pieces and checks the "Rulebook" (the Grammar). It asks, *`"Is it legal to put a '+' between two numbers?"`* If the answer is yes, it performs the math.



---

## The Grammar: Teaching Math to a Machine

In our `arith_parser.y` file, we define the hierarchy of math. We tell the computer that an **Expression** can be:
* Two expressions joined by `+`, `-`, `*`, or `/`.
* An expression wrapped in parentheses `( )`.
* Or simply a raw **Number**.

By defining these rules [recursively](https://en.wikipedia.org/wiki/Recursion_(computer_science)), the compiler can solve complex problems like `3 + 5 * (2 - 1)` by breaking them down into smaller and smaller "trees."



---

##  Folder Contents & Logic

* **`arith_lex.l`**: The Lexer. It captures numbers and mathematical symbols and hands them over to the parser as tokens.

* **`arith_parser.y`**: The Parser. This contains the grammar rules and the actual logic to calculate the result (using the `$$ = $1 + $3` syntax).

* **`input.txt`**: A simple text file containing the math problem you want to solve (e.g., `3 + 5 * 2`).

---

## Execution Procedure

Because we are using two different tools, the compilation process has a few more steps. We use **Win_Bison** (the modern version of YACC) and **Win_Flex**:

```bash
# 1. Generate the Parser files (Header and C code)
win_bison -d -v arith_parser.y

# 2. Generate the Lexer C code
win_flex arith_lex.l

# 3. Compile both generated files together into one executable
gcc lex.yy.c arith_parser.tab.c -o arith.exe

# 4. Run the evaluator against your input
arith.exe < input.txt
```
---

## The Result

If your expression is valid (like `10 / 2 + 3`), the program will print the calculated result. If you give it something nonsensical (like` 10 + / 5`), the YACC judge will trigger a Syntax Error, telling you the expression is invalid.

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)

[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>
