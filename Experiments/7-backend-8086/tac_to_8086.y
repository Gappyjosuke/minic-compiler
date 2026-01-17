%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAC 100
#define SYMBOL_TABLE_SIZE 50

// Structure for Three Address Code
typedef struct {
    char result[20];
    char arg1[20];
    char arg2[20];
    char op[10];
} TAC;

// Structure for Symbol Table
typedef struct {
    char name[20];
    int offset;
} Symbol;

TAC tac_codes[MAX_TAC];
Symbol symbol_table[SYMBOL_TABLE_SIZE];
int tac_count = 0;
int symbol_count = 0;
int current_offset = 0;

void add_symbol(char* name);
int find_symbol(char* name);
void generate_8086_code();
void process_assignment(int index);
void process_arithmetic(int index);
void process_conditional(int index);

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char strval[50];
}

%token <strval> ID NUMBER OPERATOR ASSIGNOP RELOP
%token NEWLINE

%%

program:
    lines
;

lines:
    lines line
    | line
;

line:
    assignment NEWLINE
    | arithmetic NEWLINE  
    | conditional NEWLINE
    | NEWLINE
;

assignment:
    ID ASSIGNOP ID {
        strcpy(tac_codes[tac_count].result, $1);
        strcpy(tac_codes[tac_count].arg1, $3);
        strcpy(tac_codes[tac_count].op, "=");
        tac_count++;
        
        add_symbol($1);
        add_symbol($3);
    }
    | ID ASSIGNOP NUMBER {
        strcpy(tac_codes[tac_count].result, $1);
        strcpy(tac_codes[tac_count].arg1, $3);
        strcpy(tac_codes[tac_count].op, "=");
        tac_count++;
        
        add_symbol($1);
    }
;

arithmetic:
    ID ASSIGNOP ID OPERATOR ID {
        strcpy(tac_codes[tac_count].result, $1);
        strcpy(tac_codes[tac_count].arg1, $3);
        strcpy(tac_codes[tac_count].arg2, $5);
        strcpy(tac_codes[tac_count].op, $4);
        tac_count++;
        
        add_symbol($1);
        add_symbol($3);
        add_symbol($5);
    }
    | ID ASSIGNOP ID OPERATOR NUMBER {
        strcpy(tac_codes[tac_count].result, $1);
        strcpy(tac_codes[tac_count].arg1, $3);
        strcpy(tac_codes[tac_count].arg2, $5);
        strcpy(tac_codes[tac_count].op, $4);
        tac_count++;
        
        add_symbol($1);
        add_symbol($3);
    }
    | ID ASSIGNOP NUMBER OPERATOR ID {
        strcpy(tac_codes[tac_count].result, $1);
        strcpy(tac_codes[tac_count].arg1, $3);
        strcpy(tac_codes[tac_count].arg2, $5);
        strcpy(tac_codes[tac_count].op, $4);
        tac_count++;
        
        add_symbol($1);
        add_symbol($5);
    }
;

conditional:
    ID RELOP ID {
        strcpy(tac_codes[tac_count].result, "IF");
        strcpy(tac_codes[tac_count].arg1, $1);
        strcpy(tac_codes[tac_count].arg2, $3);
        strcpy(tac_codes[tac_count].op, $2);
        tac_count++;
        
        add_symbol($1);
        add_symbol($3);
    }
;

%%

// Add symbol to symbol table if not exists
void add_symbol(char* name) {
    // Skip numbers and temporary variables starting with 't'
    if (name[0] >= '0' && name[0] <= '9') return;
    
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return;
        }
    }
    
    if (symbol_count < SYMBOL_TABLE_SIZE) {
        strcpy(symbol_table[symbol_count].name, name);
        symbol_table[symbol_count].offset = current_offset;
        current_offset += 2; // Each variable takes 2 bytes in 8086
        symbol_count++;
    }
}

// Find symbol in symbol table
int find_symbol(char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].offset;
        }
    }
    return -1;
}

// Generate 8086 Assembly Code
void generate_8086_code() {
    printf("\n=== GENERATED 8086 ASSEMBLY CODE ===\n\n");
    
    // Data Segment
    printf("DATA SEGMENT\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("    %s DW ?\n", symbol_table[i].name);
    }
    printf("DATA ENDS\n\n");
    
    // Code Segment
    printf("CODE SEGMENT\n");
    printf("    ASSUME CS:CODE, DS:DATA\n");
    printf("START:\n");
    printf("    MOV AX, DATA\n");
    printf("    MOV DS, AX\n\n");
    
    // Process each TAC instruction
    for (int i = 0; i < tac_count; i++) {
        printf("; TAC: %s = %s %s %s\n", 
               tac_codes[i].result, tac_codes[i].arg1, 
               tac_codes[i].op, tac_codes[i].arg2);
        
        if (strcmp(tac_codes[i].op, "=") == 0) {
            process_assignment(i);
        }
        else if (strcmp(tac_codes[i].result, "IF") == 0) {
            process_conditional(i);
        }
        else {
            process_arithmetic(i);
        }
        printf("\n");
    }
    
    // Program end
    printf("    MOV AH, 4CH\n");
    printf("    INT 21H\n");
    printf("CODE ENDS\n");
    printf("END START\n");
}

void process_assignment(int index) {
    char* result = tac_codes[index].result;
    char* arg1 = tac_codes[index].arg1;
    
    // Check if arg1 is a number
    if (arg1[0] >= '0' && arg1[0] <= '9') {
        printf("    MOV %s, %s\n", result, arg1);
    } else {
        printf("    MOV AX, %s\n", arg1);
        printf("    MOV %s, AX\n", result);
    }
}

void process_arithmetic(int index) {
    char* result = tac_codes[index].result;
    char* arg1 = tac_codes[index].arg1;
    char* arg2 = tac_codes[index].arg2;
    char* op = tac_codes[index].op;
    
    // Load first operand
    if (arg1[0] >= '0' && arg1[0] <= '9') {
        printf("    MOV AX, %s\n", arg1);
    } else {
        printf("    MOV AX, %s\n", arg1);
    }
    
    // Perform operation
    if (strcmp(op, "+") == 0) {
        if (arg2[0] >= '0' && arg2[0] <= '9') {
            printf("    ADD AX, %s\n", arg2);
        } else {
            printf("    ADD AX, %s\n", arg2);
        }
    }
    else if (strcmp(op, "-") == 0) {
        if (arg2[0] >= '0' && arg2[0] <= '9') {
            printf("    SUB AX, %s\n", arg2);
        } else {
            printf("    SUB AX, %s\n", arg2);
        }
    }
    else if (strcmp(op, "*") == 0) {
        if (arg2[0] >= '0' && arg2[0] <= '9') {
            printf("    MOV BX, %s\n", arg2);
        } else {
            printf("    MOV BX, %s\n", arg2);
        }
        printf("    MUL BX\n");
    }
    else if (strcmp(op, "/") == 0) {
        if (arg2[0] >= '0' && arg2[0] <= '9') {
            printf("    MOV BX, %s\n", arg2);
        } else {
            printf("    MOV BX, %s\n", arg2);
        }
        printf("    XOR DX, DX\n");
        printf("    DIV BX\n");
    }
    
    // Store result
    printf("    MOV %s, AX\n", result);
}

void process_conditional(int index) {
    char* arg1 = tac_codes[index].arg1;
    char* arg2 = tac_codes[index].arg2;
    char* op = tac_codes[index].op;
    
    static int label_count = 0;
    label_count++;
    
    printf("    MOV AX, %s\n", arg1);
    printf("    CMP AX, %s\n", arg2);
    
    if (strcmp(op, "==") == 0) {
        printf("    JNE LABEL_%d\n", label_count);
    }
    else if (strcmp(op, "!=") == 0) {
        printf("    JE LABEL_%d\n", label_count);
    }
    else if (strcmp(op, "<") == 0) {
        printf("    JGE LABEL_%d\n", label_count);
    }
    else if (strcmp(op, ">") == 0) {
        printf("    JLE LABEL_%d\n", label_count);
    }
    else if (strcmp(op, "<=") == 0) {
        printf("    JG LABEL_%d\n", label_count);
    }
    else if (strcmp(op, ">=") == 0) {
        printf("    JL LABEL_%d\n", label_count);
    }
    
    printf("    ; True branch code here\n");
    printf("LABEL_%d:\n", label_count);
    printf("    ; False branch code here\n");
}

void print_tac() {
    printf("\n=== THREE ADDRESS CODE ===\n");
    for (int i = 0; i < tac_count; i++) {
        if (strcmp(tac_codes[i].result, "IF") == 0) {
            printf("%d: IF %s %s %s GOTO L\n", 
                   i, tac_codes[i].arg1, tac_codes[i].op, tac_codes[i].arg2);
        } else {
            printf("%d: %s = %s %s %s\n", 
                   i, tac_codes[i].result, tac_codes[i].arg1, 
                   tac_codes[i].op, tac_codes[i].arg2);
        }
    }
}

int main() {
    printf("=== Three Address Code to 8086 Assembly Compiler ===\n");
    printf("Enter TAC statements (one per line):\n");
    printf("Format: result = arg1 op arg2\n");
    printf("        or if a relop b\n");
    printf("Operators: +, -, *, /, =, ==, !=, <, >, <=, >=\n");
    printf("Example: t1 = a + b\n");
    printf("         if a < b\n");
    printf("Type 'END' to finish input\n\n");
    
    yyparse();
    
    print_tac();
    generate_8086_code();
    
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}