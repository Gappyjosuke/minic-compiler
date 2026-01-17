@echo off
echo Building Expression Optimizer...

echo Step 1: Running Bison...
win_bison -d optimizer_opt.y
if errorlevel 1 (
    echo Error: Bison failed!
    pause
    exit /b 1
)

echo Step 2: Running Flex...
win_flex optimizer_opt.l
if errorlevel 1 (
    echo Error: Flex failed!
    pause
    exit /b 1
)

echo Step 3: Compiling with GCC...
gcc lex.yy.c optimizer_opt.tab.c -o optimizer_opt.exe
if errorlevel 1 (
    echo Error: Compilation failed!
    pause
    exit /b 1
)

echo Build successful! Run optimizer_opt.exe
echo.
echo Example inputs:
echo   x = 2 + 3 * 4;
echo   y = (5 + 3) * 2;
echo   z = 10 + 0 * 5;
echo.
pause