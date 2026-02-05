#include "apc.h"

/* add magnitudes and store into headR/tailR */
static int add_magnitude(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;

    int carry = 0;

    while (t1 != NULL || t2 != NULL || carry != 0)
    {
        int x = (t1 ? t1->data : 0);
        int y = (t2 ? t2->data : 0);
        
        int sum = x + y + carry;

        int digit = sum % 10;
        carry = sum / 10;

        insert_at_first(headR, tailR, digit);

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    return SUCCESS;
}

/* Main addition with sign handling */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int s1 = (*head1 ? (*head1)->sign : 1);
    int s2 = (*head2 ? (*head2)->sign : 1);

    /* CASE 1: Same sign → Normal addition */
    if (s1 == s2)
    {
        add_magnitude(head1, tail1, head2, tail2, headR, tailR);
        if (*headR) (*headR)->sign = s1;

        /* print result */
        printf("Final Result: ");
        if (*headR && (*headR)->sign == -1) printf("-");
        print_list(*headR);
        printf("\n");

        return SUCCESS;
    }

    /* CASE 2: Signs differ → perform subtraction of magnitudes */
    int cmp = compair_numbers(*head1, *head2);

    /* CASE equal magnitude → result is zero */
    if (cmp == 0)
    {
        insert_at_first(headR, tailR, 0);
        if (*headR) (*headR)->sign = 1;     // avoid -0

        printf("Final Result: ");
        print_list(*headR);
        printf("\n");

        return SUCCESS;
    }

    /* CASE A: |head1| > |head2| → result sign = s1 */
    if (cmp == 1)
    {
        Dlist *t1 = *tail1;
        Dlist *t2 = *tail2;
        int borrow = 0;

        while (t1)
        {
            int x = t1->data - borrow;
            int y = (t2 ? t2->data : 0);

            borrow = 0;

            if (x < y)
            {
                x += 10;
                borrow = 1;
            }

            insert_at_first(headR, tailR, x - y);

            t1 = t1->prev;
            if (t2) t2 = t2->prev;
        }

        /* remove leading zeros safely */
        while (*headR && (*headR)->data == 0 && (*headR)->next)
        {
            Dlist *temp = *headR;
            *headR = (*headR)->next;
            (*headR)->prev = NULL;
            free(temp);
        }

        if (*headR) (*headR)->sign = s1;

        printf("Final Result: ");
        if (*headR && (*headR)->sign == -1) printf("-");
        print_list(*headR);
        printf("\n");

        return SUCCESS;
    }

    /* CASE B: |head2| > |head1| → result sign = s2 */
    else
    {
        Dlist *t1 = *tail2;
        Dlist *t2 = *tail1;
        int borrow = 0;

        while (t1)
        {
            int x = t1->data - borrow;
            int y = (t2 ? t2->data : 0);

            borrow = 0;

            if (x < y)
            {
                x += 10;
                borrow = 1;
            }

            insert_at_first(headR, tailR, x - y);

            t1 = t1->prev;
            if (t2) t2 = t2->prev;
        }

        /* remove leading zeros safely */
        while (*headR && (*headR)->data == 0 && (*headR)->next)
        {
            Dlist *temp = *headR;
            *headR = (*headR)->next;
            (*headR)->prev = NULL;
            free(temp);
        }

        if (*headR) (*headR)->sign = s2;

        printf("Final Result: ");
        if (*headR && (*headR)->sign == -1) printf("-");
        print_list(*headR);
        printf("\n");

        return SUCCESS;
    }
}
