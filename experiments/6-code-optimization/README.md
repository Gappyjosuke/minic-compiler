<div align="justify">

[*← Back to Expeiments Index*](/Experiments/README.md)


#  Experiment 06: Code Optimization - Making it Lean and Mean

We have reached the stage where our compiler is no longer just a translator; it is now an **Optimizer**. In the previous labs, we generated code that worked, but "working" isn't always good enough. In the real world, code needs to run at lightning speed. This experiment implements techniques that clean up redundant logic and replace heavy math with lighter alternatives.

###  The Art of "Teaching Computers to Be Clever"

In the 1970s and 1980s, computer memory and CPU time were scarce and expensive, motivating deep research into code optimization. Engineers such as [Frances Allen](https://en.wikipedia.org/wiki/Frances_Allen) pioneered compiler optimization techniques that analyze and transform programs to run more efficiently on limited hardware. These foundational ideas still influence modern compilers today, helping software adapt across a wide range of systems—from large servers to resource-constrained devices—when combined with advances in hardware and runtime systems.

---

##  What are we actually doing?

The goal is to take a raw arithmetic expression and "rewrite" it into a version that produces the exact same result but takes less effort for the CPU to execute.

###  Our Three Techniques:

1.  **[Constant Folding](https://en.wikipedia.org/wiki/Constant_folding):** Why make the CPU calculate `2 + 3` every time the program runs? We do the math once during compilation and just put `5` in the code.

2.  **[Strength Reduction](https://en.wikipedia.org/wiki/Strength_reduction):** Some math operations are "expensive" for hardware. Multiplying by 2 is slow; shifting bits to the left (`x << 1`) is instant. We replace the heavy lifting with cheaper equivalents.

3.  **[Algebraic Transformation](https://en.wikipedia.org/wiki/Simplification):** We use the laws of math to delete useless code. If a programmer writes `x + 0`, we simply turn it into `x`. If they write `x * 0`, the whole thing becomes `0`.



---

##  The Architecture: The Expression Tree

To optimize code, the compiler needs to see the "shape" of the math. We use a **Node System** (`node.h`) to build an **Expression Tree**.


1.  **The Scout (`optimizer_opt.l`):** Breaks the input into numbers and operators.

2.  **The Builder (`optimizer_opt.y`):** Connects the tokens into a tree structure in memory. 

3.  **The Optimizer:** The parser traverses this tree. If it sees a node where both "children" are numbers, it "collapses" them into a single value. If it sees a multiplication by 0 or 1, it prunes the tree branches accordingly.

---

##  Folder Contents & Logic

* **`optimizer_opt.l`**: The Lexer. It captures the raw numeric and variable data.

* **`optimizer_opt.y`**: The Parser. This is the "Brain" where the optimization rules (folding and reduction) are applied.

* **`node.h`**: The header file defining the tree structure used to store expressions.

---

##  Execution Procedure

Ready to see your code shrink and speed up? Run the following:

```bash
# 1. Generate the Optimizer Parser
win_bison -d -v optimizer_opt.y

# 2. Generate the Lexer
win_flex optimizer_opt.l

# 3. Compile the optimization engine
gcc optimizer_opt.tab.c lex.yy.c -o optimizer.exe

# 4. Run the program
./optimizer.exe
```

## The Result

Testing your program. When prompted, try entering these expressions to see the results:

* `a = 2 + 3 * 5`  ➔ **Optimized:** `a = 17`

* `x = y * 2`  ➔ **Optimized:**  `x = y << 1`

* `z = b * 1 + 0`  ➔ **Optimized:**  `z = b`

---

[*Download Full Manual PDF*](/Docs/CompilerDesign-Lab-Manual.pdf)
[*Download Full Manual DOCX*](/Docs/CompilerDesign-Lab-Manual.docx)

</div>