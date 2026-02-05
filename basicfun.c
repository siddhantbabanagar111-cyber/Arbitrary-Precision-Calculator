#include "apc.h"

int insert_at_first(Dlist **head, Dlist **tail, data_t data){
    Dlist *new = (Dlist *)malloc(sizeof(Dlist));
    if (new == NULL) {
        printf("Failed to allocate the memory\n");
        return FAILURE;
    }
    new->prev = NULL;
    new->data = data;
    new->next = NULL;
    new->sign = 1; /* default sign for each node */
    if (*head == NULL) {
        *head = *tail = new;
    }
    else {
        (*head)->prev = new;
        new->next = *head;
        *head = new;
    }
    return SUCCESS;
}

int insert_at_last(Dlist **head, Dlist **tail, data_t data){
    Dlist *new = (Dlist *)malloc(sizeof(Dlist));
    if (new == NULL) {
        printf("Failed to allocate the memory\n");
        return FAILURE;
    }
    new->prev = NULL;
    new->data = data;
    new->next = NULL;
    new->sign = 1; /* default sign */
    if (*head == NULL && *tail == NULL) {
        *head = *tail = new;
        return SUCCESS;
    }
    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;
    return SUCCESS;
}

void print_list(Dlist *head)
{
    if (head == NULL)
    {
        printf("0");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
}

int create_list(Dlist **head, Dlist **tail, char *num_str)
{
    int i = 0;
    int sign = 1;
    /* reset head/tail just in case */
    *head = *tail = NULL;

    if (num_str[0] == '-') 
    { 
        i = 1; 
        sign = -1; 
    }
    for (; num_str[i] != '\0'; i++)
    {
        if (num_str[i] < '0' || num_str[i] > '9') {
            printf("Invalid character %c in list\n", num_str[i]);
            return FAILURE;
        }
        insert_at_last(head, tail, num_str[i] - '0');
    }
    /* if list is created, set sign at head node */
    if (*head != NULL)
        (*head)->sign = sign;
    return SUCCESS;
}

int list_length(Dlist *head){
    Dlist *temp = head;
    int len = 0;
    while (temp) {
        len++;
        temp = temp->next;
    }
    return len;
}

int compair_numbers(Dlist *head1, Dlist *head2){
    Dlist *t1 = head1;
    Dlist *t2 = head2;
    int len1 = list_length(head1), len2 = list_length(head2);

    if (len1 > len2) return 1;
    if (len1 < len2) return -1;

    t1 = head1;
    t2 = head2;
    while (t1 && t2) {
        if (t1->data > t2->data) return 1;
        if (t1->data < t2->data) return -1;

        t1 = t1->next;
        t2 = t2->next;
    }
    return 0; /* equal */
}
