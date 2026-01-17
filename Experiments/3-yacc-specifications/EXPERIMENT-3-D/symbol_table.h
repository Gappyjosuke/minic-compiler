#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Var {
    char *name;
    float value;
    struct Var *next;
} Var;

Var *symbol_table = NULL;
// Lookup a variable
Var* lookup_var(const char *name) {
    Var *current = symbol_table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) return current;
        current = current->next;
    }
    return NULL;
}
void set_var(const char *name, float value) {
    Var *v = lookup_var(name);
    if (v) {
        v->value = value;
    } else {
        v = (Var*)malloc(sizeof(Var));
        v->name = strdup(name);
        v->value = value;
        v->next = symbol_table;
        symbol_table = v;
    }
}


float get_var_value(const char *name) {
    Var *v = lookup_var(name);
    if (v) return v->value;
    printf("Warning: variable %s not initialized. Using 0.\n", name);
    return 0.0;
}

#endif
