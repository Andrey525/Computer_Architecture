#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef RPN_H
#define RPN_H

typedef struct Rpn {
    char c;
    struct Rpn* next;
} Rpn;

Rpn* push(Rpn* head, char a)
{
    Rpn* temp = malloc(sizeof(Rpn));
    if (temp) {
        temp->c = a;
        temp->next = head;
        return temp;
    }
    return NULL;
}
char stack_pop(Rpn** head)
{
    if (*head) {
        Rpn* ptr = (*head)->next;
        char a = (*head)->c;
        free(*head);
        *head = ptr;
        return a;
    }
    return '\0';
}
int get_prior(char c)
{
    if (c == '*' || c == '/')
        return 3;
    if (c == '-' || c == '+')
        return 2;
    if (c == '(')
        return 1;
    return 0;
}
void translate_to_rpn(char* str, char* out)
{
    Rpn* opers = NULL;
    int len;
    for (int i = 0; i <= strlen(str); i += 1) {
        if (str[i] == ')') {
            while (opers->c != '(') {
                len = strlen(out);
                out[len] = stack_pop(&opers);
                len = strlen(out);
                out[len] = ',';
                out[len + 1] = '\0';
            }
            stack_pop(&opers);
        } else if (isalpha(str[i])) {
            len = strlen(out);
            out[len] = str[i];
            len = strlen(out);
            out[len] = ',';
            out[len + 1] = '\0';
        } else if (isdigit(str[i])) {
            while (isdigit(str[i])) {
                len = strlen(out);
                out[len] = str[i];
                len = strlen(out);
                out[len] = '\0';
                i++;
            }
            i--;
            len = strlen(out);
            out[len] = ',';
            out[len + 1] = '\0';
        } else if (str[i] == '(') {
            opers = push(opers, str[i]);
        } else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*') {
            if (opers == NULL) {
                opers = push(opers, str[i]);
            } else if (get_prior(opers->c) < get_prior(str[i])) {
                opers = push(opers, str[i]);
            } else {
                while ((opers != NULL) && (get_prior(opers->c) >= get_prior(str[i]))) {
                    len = strlen(out);
                    out[len] = stack_pop(&opers);
                    len = strlen(out);
                    out[len] = ',';
                    out[len + 1] = '\0';
                }
                opers = push(opers, str[i]);
            }
        }
    }
    while (opers != NULL) {
        len = strlen(out);
        out[len] = stack_pop(&opers);
        len = strlen(out);
        out[len] = '\0';
        if (opers) {
            len = strlen(out);
            out[len] = ',';
            out[len + 1] = '\0';
        }
    }
    len = strlen(out);
    out[len] = '.';
    out[len + 1] = '\0';
}
#endif