<div align="justify">

[*← Back to Expeiments Index*](/Experiments/README.md)


#  Experiment 05: Type Checking - The Logic of Compatibility

In the previous labs, we learned how to recognize code structures and translate them. However, a program can be syntactically perfect and still be a logical disaster. For example, `string x = 10 / "apple";` follows the rules of grammar, but it makes no sense to a computer. This experiment focuses on **Type Checking**, the process where the compiler ensures that data types are compatible.

###  The Guardian of Data Integrity

Type checking was strongly emphasized by languages such as **Pascal** and **ALGOL**, which helped popularize disciplined static typing as a way to catch programming errors early. By detecting type mismatches before execution, these systems prevent an entire class of mistakes that could otherwise lead to incorrect behavior or low-level failures. In modern development tools, [Static Type Checking](https://en.wikipedia.org/wiki/Type_system#Static_type_checking) is a key reason IDEs can flag errors with red highlights long before a program is ever run.

---

##  What is Type Checking?

Type checking is the compiler’s "Reality Check." It verifies that every operation performed on a variable is consistent with the type it was assigned during declaration.


###  The Rules of the Game:

1.  **Declaration Check:** Is the variable `x` even declared before it's being used?

2.  **Assignment Check:** Can you store a `float` (like `3.14`) inside an `int` variable? 

3.  **Expression Compatibility:** If you add an `int` to a `float`, what should the resulting type be? (Usually, the compiler performs [Type Promotion](https://en.wikipedia.org/wiki/Type_conversion), upgrading the result to a `float` to avoid losing precision).

---

##  The Architecture: Semantic Enforcement

This experiment uses our familiar LEX and YACC setup, but with a much smarter **Symbol Table**.

1.  **The Scout (`typecheck.l`) :** Identifies keywords like `int` and `float`, variables, and numbers.

2.  **The Memory :** Our symbol table doesn't just store names anymore; it stores the **Type** (INT, FLOAT, etc.) associated with every name.

3.  **The Judge (`typecheck.y`) :** This is where the semantic rules live. When it sees `a = b + c`, it doesn't just generate code. It first looks up `a`, `b`, and `c` in the table. If `a` is an `int` but the result of `b + c` is a `float`, it flags a warning or error.

---

##  Folder Contents & Logic

* **`typecheck.l`** : The Lexer. It captures type names and identifiers and sends them to the parser as typed tokens.

* **`typecheck.y`** : The Parser & Semantic Analyzer. It handles the logic of **Type Inference** and **Type Mismatch** detection.

* **`input.c`** : Your test subject. Use it to try both valid and invalid scenarios:
  ```c
  int a;
  float b;
  a = 10;      // Valid
  b = a + 1.5; // Valid (Type Promotion)
  a = b;       // Should trigger a Type Mismatch Warning
  c = 5;       // Should trigger an "Undeclared Variable" Error

  ```
---

## Execution Procedure

Ready to see if your code makes sense? Run the compilation pipeline:

```bash
# 1. Generate the Semantic Parser files
win_bison -d -v typecheck.y

# 2. Generate the Lexer files
win_flex typecheck.l

# 3. Compile the Type Checker engine
gcc lex.yy.c typecheck.tab.c -o typecheck.exe

# 4. Run the program and feed your test cases
./typecheck.exe < input.c
```

## The Result

The program will evaluate your code line by line. Instead of just printing tokens, it will output validation messages like:

* `Declaration successful: a as INT`

* `Type Match: Assignment valid`

* `Error: Variable 'c' used before declaration`

* `Warning: Possible precision loss (Assigning FLOAT to INT)`

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)
[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>