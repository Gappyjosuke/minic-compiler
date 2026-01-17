<div align="justify">

[*← Back to Experiments Index*](/Experiments/README.md)

#  Experiment 02: Building a Professional Lexical Analyzer

In our first experiment, we dipped a surface level. Now, it's time to dive deep. Experiment 02 is about moving from *`"recognizing a few patterns"`* to building a **Complete Lexical Analyzer** that can handle almost everything a real C compiler encounters—including complex strings, relational operators, and control flow keywords.

---

##  The Evolution of Scanning

In the early days of computing, programmers worked directly in machine code or assembly. As high-level languages emerged, compiler designers needed systematic ways to translate human-readable source code into forms machines could process. This led to the development of compiler front ends, beginning with lexical analysis. This experiment mirrors the first stage of the front end used by modern compilers such as[GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) or [Clang](https://en.wikipedia.org/wiki/Clang), building the initial bridge between raw source text and structured program representation.

---

##  Why are we doing this again? (We are making a full version)

You might wonder: *"Didn't we already do this in Exp 01?"* The answer is **Scale**. In this experiment, we aren't just looking for a few keywords. We are training our Lexer to understand the full vocabulary of C logic:

* **Logic Gates :** We now recognize [Relational Operators](https://en.wikipedia.org/wiki/Relational_operator) like `==`, `!=`, and `>=`. These are the "decision makers" in your code.

* **Strings & Literals :** We’ve added the ability to recognize text inside double quotes—essential for handling strings in programs.

* **Full Keyword Support :** We’ve expanded the vocabulary to include `while`, `for`, `do`, `switch`, and `case`. 

###  The Symbol Table 2.0

Our **Symbol Table** (the "Address Book") is much smarter now. The `insertSymbol()` function acts as a gatekeeper—it ensures that keywords (like `int` or `return`) don't accidentally get saved as variable names. This ensures that every entry in your table is a unique, user-defined [Identifier](https://en.wikipedia.org/wiki/Identifier_(computer_programming)).

---

## How it Works: The WinFlex Power

We are using **WinFlex**, the Windows port of [Flex](https://en.wikipedia.org/wiki/Flex_(lexical_analyser_generator)). 

1.  **Definitions :** We define what a "digit" and a "letter" look like using [Regular Expressions](https://en.wikipedia.org/wiki/Regular_expression).

2.  **Rules :** We create a list of rules. For example: *"If you see a word that starts with a letter, check if it's a keyword. If it's not, try to put it in the Symbol Table."*

3.  **The Engine :** WinFlex takes these rules and generates `lex.yy.c`, which is essentially a high-speed [Scanner](https://en.wikipedia.org/wiki/Lexical_analysis#Scanner) that can process thousands of lines of code in milliseconds.



---

## Folder Breakdown

* **`lexer.l`**: The "Master Specification." This is where you write your patterns, regular expressions, and C logic.

* **`lex.yy.c`**: The generated C file. It is a massive state machine created automatically by WinFlex.

* **`input.c`**: A complex test file. Try putting `while`, `if`, and `return` in here to see if your Lexer can handle the full syntax!

---

## Execution Procedure

Ready to run the professional-grade analyzer? Open your terminal and follow the pipeline:

```bash
# 1. Transform your .l rules into C code
win_flex lexer.l

# 2. Compile the generated engine into a binary
gcc lex.yy.c -o lexer.exe

# 3. Test it against your complex C input
lexer.exe < input.c
```
---

## The Result

Your terminal will act like a "Live Feed." As the program reads `input.c`, it will announce every token it sees:

* *Found Keyword :* `while`

* *Found Operator :* `>=`

* *Found Identifier :* `counter` (Added to Symbol Table)

---


[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)

[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>
