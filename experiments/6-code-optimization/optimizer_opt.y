%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations
typedef struct Node Node;
Node* makeNode(char op, Node* left, Node* right);
Node* makeLeaf(int value);
Node* makeVariable(char* id);
void optimize(Node* node);
void printOptimized(Node* node);
void freeTree(Node* node);
int isPowerOfTwo(int n);

int yylex(void);
void yyerror(const char *s);
extern int yyparse();
%}

%union {
    int num;
    char id[32];
    struct Node* node;
}

%token <num> NUMBER
%token <id> ID
%token ASSIGN PLUS MINUS MUL DIV SEMI
%type <node> expr

%left PLUS MINUS
%left MUL DIV

%%

program:
    statement
;

statement:
    ID ASSIGN expr SEMI
    {
        printf("\n=== Optimization Results ===\n");
        printf("Original Code:   %s = ", $1);
        printOptimized($3);
        printf(";\n");

        optimize($3);
        
        printf("Optimized Code:  %s = ", $1);
        printOptimized($3);
        printf(";\n");
        
        freeTree($3);
    }
;

expr:
      expr PLUS expr   { $$ = makeNode('+', $1, $3); }
    | expr MINUS expr  { $$ = makeNode('-', $1, $3); }
    | expr MUL expr    { $$ = makeNode('*', $1, $3); }
    | expr DIV expr    { $$ = makeNode('/', $1, $3); }
    | NUMBER           { $$ = makeLeaf($1); }
    | ID               { $$ = makeVariable($1); }  // ADDED: Variable support
;

%%

// ---------- Node structure definition ----------
struct Node {
    char op;
    int value;
    char id[32];
    int is_var;  // ADDED: Flag to indicate if this is a variable
    struct Node *left, *right;
};

// ---------- Utility Functions ----------
int isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int logBaseTwo(int n) {
    int log = 0;
    while (n > 1) {
        n >>= 1;
        log++;
    }
    return log;
}

// ---------- Node creation ----------
Node* makeNode(char op, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->op = op;
    node->left = left;
    node->right = right;
    node->id[0] = '\0';
    node->value = 0;
    node->is_var = 0;
    return node;
}

Node* makeLeaf(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->op = '\0';
    node->left = node->right = NULL;
    node->value = value;
    node->id[0] = '\0';
    node->is_var = 0;
    return node;
}

// ADDED: Function to create variable nodes
Node* makeVariable(char* id) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->op = '\0';
    node->left = node->right = NULL;
    node->value = 0;
    strcpy(node->id, id);
    node->is_var = 1;  // Mark as variable
    return node;
}

// ---------- Optimization ----------
void optimize(Node* node) {
    if (!node) return;
    
    // Optimize children first (post-order traversal)
    if (node->left) optimize(node->left);
    if (node->right) optimize(node->right);

    // Skip if already a leaf node (constant or variable)
    if (node->op == '\0') return;

    // TECHNIQUE 1: CONSTANT FOLDING
    if (node->left && node->left->op == '\0' && !node->left->is_var && 
        node->right && node->right->op == '\0' && !node->right->is_var) {
        
        int left_val = node->left->value;
        int right_val = node->right->value;
        int result = 0;
        int valid = 1;

        switch (node->op) {
            case '+': 
                result = left_val + right_val; 
                printf("// Constant folding: %d + %d = %d\n", left_val, right_val, result);
                break;
            case '-': 
                result = left_val - right_val; 
                printf("// Constant folding: %d - %d = %d\n", left_val, right_val, result);
                break;
            case '*': 
                result = left_val * right_val; 
                printf("// Constant folding: %d * %d = %d\n", left_val, right_val, result);
                break;
            case '/': 
                if (right_val != 0) {
                    result = left_val / right_val;
                    printf("// Constant folding: %d / %d = %d\n", left_val, right_val, result);
                } else {
                    printf("// Warning: Division by zero! Using 0 as result.\n");
                    result = 0;
                }
                break;
            default:
                valid = 0;
        }

        if (valid) {
            // Convert this node to a leaf
            node->op = '\0';
            node->value = result;
            node->is_var = 0;
            free(node->left);
            free(node->right);
            node->left = node->right = NULL;
            return;
        }
    }

    // TECHNIQUE 2: STRENGTH REDUCTION
    if (node->op == '*') {
        // Multiplication by powers of 2 (right side)
        if (node->right && node->right->op == '\0' && !node->right->is_var && 
            isPowerOfTwo(node->right->value)) {
            int power = node->right->value;
            int shift = logBaseTwo(power);
            printf("// Strength reduction: *%d -> <<%d\n", power, shift);
        }
        // Multiplication by powers of 2 (left side)
        else if (node->left && node->left->op == '\0' && !node->left->is_var && 
                 isPowerOfTwo(node->left->value)) {
            int power = node->left->value;
            int shift = logBaseTwo(power);
            printf("// Strength reduction: %d* -> <<%d\n", power, shift);
        }
        
        // Multiplication by 2 (with variable on left)
        if (node->left && node->left->is_var && 
            node->right && node->right->op == '\0' && !node->right->is_var && 
            node->right->value == 2) {
            printf("// Strength reduction: %s * 2 -> %s + %s\n", 
                   node->left->id, node->left->id, node->left->id);
        }
        // Multiplication by 2 (with variable on right)
        else if (node->right && node->right->is_var && 
                 node->left && node->left->op == '\0' && !node->left->is_var && 
                 node->left->value == 2) {
            printf("// Strength reduction: 2 * %s -> %s + %s\n", 
                   node->right->id, node->right->id, node->right->id);
        }
    }
    else if (node->op == '/') {
        // Division by powers of 2
        if (node->right && node->right->op == '\0' && !node->right->is_var && 
            isPowerOfTwo(node->right->value)) {
            int power = node->right->value;
            int shift = logBaseTwo(power);
            printf("// Strength reduction: /%d -> >>%d\n", power, shift);
        }
    }

    // TECHNIQUE 3: ALGEBRAIC TRANSFORMATIONS
    if (node->op == '+') {
        // x + 0 = x (0 on right)
        if (node->right && node->right->op == '\0' && !node->right->is_var && 
            node->right->value == 0) {
            printf("// Algebraic simplification: x + 0 -> x\n");
            Node* temp = node->left;
            *node = *temp;
            free(temp);
            return;
        }
        // 0 + x = x (0 on left)
        else if (node->left && node->left->op == '\0' && !node->left->is_var && 
                 node->left->value == 0) {
            printf("// Algebraic simplification: 0 + x -> x\n");
            Node* temp = node->right;
            *node = *temp;
            free(temp);
            return;
        }
    }
    else if (node->op == '-') {
        // x - 0 = x
        if (node->right && node->right->op == '\0' && !node->right->is_var && 
            node->right->value == 0) {
            printf("// Algebraic simplification: x - 0 -> x\n");
            Node* temp = node->left;
            *node = *temp;
            free(temp);
            return;
        }
        // x - x = 0 (same variable on both sides)
        else if (node->left && node->left->is_var && 
                 node->right && node->right->is_var && 
                 strcmp(node->left->id, node->right->id) == 0) {
            printf("// Algebraic simplification: %s - %s -> 0\n", 
                   node->left->id, node->right->id);
            node->op = '\0';
            node->value = 0;
            node->is_var = 0;
            free(node->left);
            free(node->right);
            node->left = node->right = NULL;
            return;
        }
    }
    else if (node->op == '*') {
        // x * 0 = 0 (0 on left)
        if (node->left && node->left->op == '\0' && !node->left->is_var && 
            node->left->value == 0) {
            printf("// Algebraic simplification: 0 * x -> 0\n");
            node->op = '\0';
            node->value = 0;
            node->is_var = 0;
            free(node->left);
            free(node->right);
            node->left = node->right = NULL;
            return;
        }
        // x * 0 = 0 (0 on right)
        else if (node->right && node->right->op == '\0' && !node->right->is_var && 
                 node->right->value == 0) {
            printf("// Algebraic simplification: x * 0 -> 0\n");
            node->op = '\0';
            node->value = 0;
            node->is_var = 0;
            free(node->left);
            free(node->right);
            node->left = node->right = NULL;
            return;
        }
        // x * 1 = x (1 on right)
        else if (node->right && node->right->op == '\0' && !node->right->is_var && 
                 node->right->value == 1) {
            printf("// Algebraic simplification: x * 1 -> x\n");
            Node* temp = node->left;
            *node = *temp;
            free(temp);
            return;
        }
        // 1 * x = x (1 on left)
        else if (node->left && node->left->op == '\0' && !node->left->is_var && 
                 node->left->value == 1) {
            printf("// Algebraic simplification: 1 * x -> x\n");
            Node* temp = node->right;
            *node = *temp;
            free(temp);
            return;
        }
    }
    else if (node->op == '/') {
        // 0 / x = 0 (x ≠ 0)
        if (node->left && node->left->op == '\0' && !node->left->is_var && 
            node->left->value == 0) {
            printf("// Algebraic simplification: 0 / x -> 0\n");
            node->op = '\0';
            node->value = 0;
            node->is_var = 0;
            free(node->left);
            free(node->right);
            node->left = node->right = NULL;
            return;
        }
        // x / 1 = x
        else if (node->right && node->right->op == '\0' && !node->right->is_var && 
                 node->right->value == 1) {
            printf("// Algebraic simplification: x / 1 -> x\n");
            Node* temp = node->left;
            *node = *temp;
            free(temp);
            return;
        }
        // x / x = 1 (same variable on both sides)
        else if (node->left && node->left->is_var && 
                 node->right && node->right->is_var && 
                 strcmp(node->left->id, node->right->id) == 0) {
            printf("// Algebraic simplification: %s / %s -> 1\n", 
                   node->left->id, node->right->id);
            node->op = '\0';
            node->value = 1;
            node->is_var = 0;
            free(node->left);
            free(node->right);
            node->left = node->right = NULL;
            return;
        }
    }
}

// ---------- Print ----------
void printOptimized(Node* node) {
    if (!node) return;
    if (node->op == '\0') {
        if (node->is_var) {
            printf("%s", node->id);
        } else {
            printf("%d", node->value);
        }
    } else {
        printf("(");
        printOptimized(node->left);
        printf(" %c ", node->op);
        printOptimized(node->right);
        printf(")");
    }
}

// ---------- Memory cleanup ----------
void freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    printf("=== Advanced Expression Optimizer ===\n");
    printf("Supports: Constant Folding, Strength Reduction, Algebraic Transformations\n");
    printf("Enter assignment statements (e.g., x = 2 + 3 * 4; or y = a * 8;)\n");
    printf("Press Ctrl+C to exit\n\n");
    
    while(1) {
        printf("> ");
        if (yyparse() != 0) {
            break; // Exit on parsing error
        }
    }
    
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}