@echo off
echo Building TAC to 8086 Assembly Compiler...

echo Step 1: Running Bison...
win_bison -d tac_to_8086.y
if errorlevel 1 (
    echo Error: Bison failed!
    pause
    exit /b 1
)

echo Step 2: Running Flex...
win_flex tac_to_8086.l
if errorlevel 1 (
    echo Error: Flex failed!
    pause
    exit /b 1
)

echo Step 3: Compiling with GCC...
gcc lex.yy.c tac_to_8086.tab.c -o tac_to_8086.exe
if errorlevel 1 (
    echo Error: Compilation failed!
    pause
    exit /b 1
)

echo Build successful! Run tac_to_8086.exe
echo.
echo Example TAC inputs:
echo   a = 5
echo   b = 10
echo   t1 = a + b
echo   result = t1 * 2
echo   if a < b
echo   END
echo.
pause