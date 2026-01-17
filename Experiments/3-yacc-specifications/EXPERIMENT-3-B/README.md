<div align="justify">

[*← Back to Experiments Index*](/Experiments/README.md)


# Experiment 03(B): Syntax Analysis - The Naming Authority

In this experiment, we are building a specialized validator. While it might seem simple to name a variable, every programming language has a strict set of rules— a [Naming Convention](https://en.wikipedia.org/wiki/Naming_convention_(programming)) —that determines what the computer can and cannot understand. We are using the LEX and YACC tag-team to enforce these rules.

### Why do we have Naming Rules?

Early programming languages adopted simple identifier rules influenced by mathematical notation, punch-card input, and compiler simplicity—not strict memory limits. As languages evolved (`such as C in the 1970s`), identifiers needed to be flexible yet unambiguous.

Allowing identifiers to start with digits (like `1var`) would break lexical analysis, because the compiler must clearly distinguish numbers from names without guesswork or backtracking. Naming rules ensure that tokens can be recognized cleanly during compilation, preventing errors long before the program reaches execution.

---

## What are we actually doing?

The goal is to create a program that acts as a "Gatekeeper." It takes a string as input and checks if it follows the C-standard for [Identifiers](https://en.wikipedia.org/wiki/Identifier_(computer_programming)).

### The Criteria for Success
To be considered a **"Valid Variable"** in our program, the name must pass three specific tests:
1.  **The Starting Character :** It must begin with an alphabet (`a-z`, `A-Z`) or an underscore (`_`).

2.  **The Body :** After the first character, it can contain any combination of letters, digits, or underscores.

3.  **The Forbidden Zone :** Symbols like `@`, `$`, `#`, or empty spaces are strictly prohibited.


---

## The Logic: Regex meets Grammar

This experiment uses two layers of defense to validate the input:

1.  **The LEX Layer (`var_lex.l`):** Uses [Regular Expressions](https://en.wikipedia.org/wiki/Regular_expression) to match the pattern `[a-zA-Z_][a-zA-Z0-9_]*`. If the input matches this pattern, it tells the parser, *`"I found a potential name!"`*

2.  **The YACC Layer (`var_parser.y`):** This is the final judge. It receives the token from LEX and confirms it fits the grammar rules. If the user types something like `_user123`, YACC prints **"Valid Variable."** If they type `123user`, the system triggers an error.



---

## Folder Contents & Logic

* **`var_lex.l`**: The Lexer. It contains the regex pattern that defines the "look" of a valid variable name.

* **`var_parser.y`**: The Parser. It handles the user interface, receiving tokens and deciding the final verdict of "Valid" or "Invalid."

* **`input.txt`**: Use this file to list various names you want to test in bulk.

---

## Execution Procedure

Open your terminal in this directory and run the generation and compilation pipeline:

```bash
# 1. Generate the Parser (The Judge) files
win_bison -d -v var_parser.y

# 2. Generate the Lexer (The Scout) files
win_flex var_lex.l

# 3. Link them together into a single validator executable
gcc lex.yy.c var_parser.tab.c -o variable.exe

# 4. Run the program
./variable.exe
```
---

## The Result

Once the program is running, try typing these into your terminal to see the validator in action:

* `_myname` ➔ **Result :** Valid

* `my_variable_1` ➔ **Result :** Valid

* `67_venn` ➔ **Result :** Invalid (Cannot start with a number)

* `hello@world` ➔ **Result :** Invalid (Special characters are not allowed)

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)

[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>
