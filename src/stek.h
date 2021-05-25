#include <stdlib.h>
#ifndef STEK_H
#define STEK_H

typedef struct Stek {
    int operand;
    int command;
    int num;
    int step;
    struct Stek* next;
} Stek;

Stek* init(int num, int command, int operand, Stek* next)
{
    Stek* temp = malloc(sizeof(Stek));
    temp->num = num;
    temp->command = command;
    temp->operand = operand;
    temp->next = next;
    return temp;
}
void add(Stek* head, Stek* node)
{
    if (head) {
        Stek* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = node;
    }
}
void rem(Stek* head, Stek* node)
{
    if (head) {
        Stek* temp = head;
        while (temp->next != node && temp->next)
            temp = temp->next;
        temp->next = node->next;
    }
}
void pop(Stek** head)
{
    if (*head) {
        *head = (*head)->next;
    }
}
Stek* find(Stek* head, int value)
{
    if (head) {
        Stek* temp = head;
        while (temp->next) {
            if (temp->num == value) {
                return temp;
            }
            temp = temp->next;
        }
    }
    return NULL;
}
Stek* last(Stek* head)
{
    if (head) {
        Stek* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp;
    }
    return NULL;
}
#endif
