[*← Back to Home Index*](/README.md)

# Laboratory Experiments Index

This folder contains the standalone source code and sample inputs for all 7 experiments in the Anna University Compiler Design syllabus.

---
## Prerequisites & Environment Setup

Before starting the experiments, you must configure your development environment. These tools are the industry standard for language engineering.


#### **1. Required Toolchain**
<div align="center">
    
| Tool | Purpose | Why we use it |
| :---: | :---: | :--- |
| **[GCC](https://thelinuxcode.com/install-gcc-windows/)** | C Compiler | The GNU Compiler Collection is built by some of the **brightest minds** in computing. It is the gold standard for turning your C code into machine binary executables (`.exe`). |
| **[WinFlexBison](https://github.com/lexxmark/winflexbison?tab=readme-ov-file)** | Lexical & Parser Generator | Used to generate the `lex.yy.c` file from a LEX specification (`.l`). It automates the creation of Finite Automata for token recognition. Parser GeneratorUsed to generate the C code for a Syntax Analyzer from a YACC specification (`.y`). It handles complex context-free grammars.

</div>    

>[!Caution]
>CRITICAL : Path Environment Variables
>Simply downloading these tools is not enough. You **must** add the `/bin` folder of each tool to your System Path. Without this, your terminal will not recognize commands like `gcc`, `flex`, or `bison`.

* **How to set up Paths:** [Official Guide: Adding to Windows Path](https://www.computerhope.com/issues/ch000549.htm)
* **Verify Installation:** Open your terminal and type `gcc --version` and `flex --version`.

> [!NOTE]
> **Automated Setup:** I am currently developing a custom script to automate the installation and path configuration. Until then, please perform the setup manually.

---

## Experiment Navigation

<div align="center">

| Exp No. | Experiment Name | Key Technologies | Quick Link |
| :---: | :--- | :--- | :---: |
| **01** | Lexical Analyzer Implementation | C Language | [Go to Task](./1-lexical-analyzer/README.md) |
| **02** | Lexical Analysis using LEX Tool | LEX / FLEX | [Go to Task](./2-lex-tool-implementation/README.md) |
| **03-A** | Recognize A Valid Arithmetic Expression | YACC / BISON | [Go to Task](/Experiments/3-yacc-specifications/EXPERIMENT-3-A/README.d) |
| **03-B** | Recognize A Valid Varibale Name | YACC / BISON | [Go to Task](/Experiments/3-yacc-specifications/EXPERIMENT-3-B/README.md) |
| **03-C** | Recognize Control Structure | YACC / BISON | [Go to Task](/Experiments/3-yacc-specifications/EXPERIMENT-3-C/README.md) |
| **03-D** | Calculator Using Lex ToolC  | YACC / BISON | [Go to Task](/Experiments/3-yacc-specifications/EXPERIMENT-3-D/README.md) |
| **04** | Three Address Code Generation | Intermediate Code | [Go to Task](./4-three-address-code/README.md) |
| **05** | Type Checking Implementation | Semantic Analysis | [Go to Task](./5-type-checking/README.md) |
| **06** | Code Optimization (Constant Folding) | Optimization | [Go to Task](./6-code-optimization/README.md) |
| **07** | Backend Generation (8086 Assembly) | Code Generation | [Go to Task](./7-backend-8086/README.md) |

</div>

---

>[!Tip]
>If you are looking for the theoretical background, algorithms, for these codes, please refer to the **[Complete Lab Manual PDF](/Docs/)**.
