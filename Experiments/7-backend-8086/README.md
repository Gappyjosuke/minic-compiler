<div align="justify">

[*← Back to Expeiments Index*](/Experiments/README.md)


#  Experiment 07: Target Code Generation (TAC to 8086)

We have reached the finish line! In previous experiments, we parsed code, checked its types, and optimized its logic into Three Address Code (TAC). But a computer's CPU doesn't understand "t1 = a + b." It only understands specific electronic instructions. This experiment implements the **Compiler Back-End**, which translates our optimized TAC into **8086 Assembly Language**.

###  The Final Translation

In the late 1970s, the **Intel 8086** microprocessor helped shape modern computing by introducing the x86 instruction set architecture. This architecture exposed programmer-visible registers such as `AX `and `BX`, and many operations required careful movement of data between memory and registers. By building this back end, you are performing the same essential task as a real compiler: translating abstract program logic into concrete machine instructions that can be executed by a physical processor.


---

##  What are we actually doing?

The goal is to take the "linear" Three Address Code we generated in Experiment 04 and map it to the hardware-specific instructions of the 8086 architecture.

###  The Translation Logic:

To convert TAC to Assembly, the generator follows a strict mapping process:

1.  **Variable to Memory :** Every variable in our TAC (like `x` or `t1`) must be declared in the 8086 `DATA SEGMENT` using `DW` (Define Word).

2.  **The "MOV" Dance :** In assembly, you cannot perform math directly between two memory locations. You must "Move" a value into a CPU register first.
    * *TAC:* `x = y + z`
    * *8086:* `MOV AX, y` -> `ADD AX, z` -> `MOV x, AX`

3.  **Jumps and Labels :** Conditional statements like `if x < 10 goto L1` are translated into `CMP` (Compare) and `JL` (Jump if Less) instructions, which manipulate the Instruction Pointer (IP).



---

##  The Architecture: The Assembly Factory

1.  **The Scout (`tac_to_8086.l`) :** Scans the TAC input file. It looks for assignments (`=`), operators (`+`, `-`, `*`), and control flow keywords.

2.  **The Translator (`tac_to_8086.y`) :** This is the core. For every TAC line it finds, it prints out the equivalent 3 or 4 lines of Assembly code. It also automatically generates the `.DATA` and `.CODE` segment boilerplate required for a valid program.

3.  **The Output :** The result is a complete 8086 assembly script that can be executed on an emulator or a compatible processor.

---

##  Folder Contents & Logic

* **`tac_to_8086.l`**: The Lexer specifically tuned to recognize intermediate code syntax.

* **`tac_to_8086.y`**: The Parser that handles the mapping of TAC operations to 8086 hardware opcodes.

* **`INPUT.TAC`**: Your source file. This is the intermediate representation of your program containing arithmetic and logic jumps.

---

##  Execution Procedure

Follow these commands to generate your hardware-ready assembly code:

```bash
# 1. Generate the Code Generator Parser
win_bison -d tac_to_8086.y

# 2. Generate the Lexer
win_flex tac_to_8086.l

# 3. Compile the Back-End Engine
gcc lex.yy.c tac_to_8086.tab.c -o tac_to_8086.exe

# 4. Run the generator against your TAC input
./tac_to_8086.exe < INPUT.TAC
```

## The Result

Your program will output a full 8086 Assembly file. You will see your abstract variables defined in memory and your math converted into `ADD`, `SUB`, and `MUL `instructions. You have successfully completed the journey from high-level source code down to low-level machine-ready instructions!

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)
[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>