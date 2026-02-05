#ifndef APC_H
#define APC_H

#define SUCCESS 0
#define FAILURE -1

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef int data_t;

typedef struct node
{
    struct node *prev;
    data_t data;
    struct node *next;
    int sign;      // sign field added: 1 for positive, -1 for negative (valid on head node)
} Dlist;

/* linked list function */
int insert_at_first(Dlist **head, Dlist **tail, data_t data);
int insert_at_last(Dlist **head, Dlist **tail, int data);
int create_list(Dlist **head, Dlist **tail, char *num_str);
void print_list(Dlist *head);
int compair_numbers(Dlist *head1, Dlist *head2);
int list_length(Dlist *head);

/* Arthimatic operations */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

#endif
