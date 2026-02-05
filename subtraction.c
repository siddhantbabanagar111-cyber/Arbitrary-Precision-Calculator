#include "apc.h"

static int subtract_magnitude(Dlist **headA, Dlist **tailA, Dlist **headB, Dlist **tailB, Dlist **headR, Dlist **tailR)
{
    /* Compare magnitudes */
    int cmp = compair_numbers(*headA, *headB);

    /* If equal → result = 0 */
    if (cmp == 0)
    {
        insert_at_first(headR, tailR, 0);
        return SUCCESS;
    }

    int negative = 0;

    /* If A < B → swap → result becomes negative */
    if (cmp == -1)
    {
        Dlist *tmpH = *headA, *tmpT = *tailA;
        *headA = *headB;  *tailA = *tailB;
        *headB = tmpH;    *tailB = tmpT;
        negative = 1;
    }

    /* Work from least significant digits */
    Dlist *t1 = *tailA;
    Dlist *t2 = *tailB;

    int borrow = 0;

    /* NORMAL SUBTRACTION */
    while (t1 != NULL)
    {
        int x = t1->data;
        int y = (t2 ? t2->data : 0);

        /* Apply previous borrow */
        x -= borrow;
        borrow = 0;

        /* If minuend digit < subtrahend digit → borrow from next digit */
        if (x < y)
        {
            x += 10;
            borrow = 1;
        }

        insert_at_first(headR, tailR, x - y);

        t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    /* REMOVE LEADING ZEROS */
    while ((*headR) && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}

/* SUBTRACTION HANDLER (A - B) with sign logic */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    int s1 = (*head1) ? (*head1)->sign : 1;
    int s2 = (*head2) ? (*head2)->sign : 1;

    /* CASE 1: Different signs → A - (-B) = A + B   OR   (-A) - B = -(A + B) */
    if (s1 != s2)
    {
        Dlist *t1 = *tail1;
        Dlist *t2 = *tail2;
        int carry = 0;

        /* magnitude addition */
        while (t1 || t2 || carry)
        {
            int x = (t1) ? t1->data : 0;
            int y = (t2) ? t2->data : 0;

            int sum = x + y + carry;
            carry = sum / 10;

            insert_at_first(headR, tailR, sum % 10);

            if (t1) t1 = t1->prev;
            if (t2) t2 = t2->prev;
        }

        if (*headR) (*headR)->sign = s1;   // Sign of A

        printf("Final Result: ");
        if (*headR && (*headR)->sign == -1) printf("-");
        print_list(*headR);
        printf("\n");

        return SUCCESS;
    }

    /* CASE 2: Both signs equal */
    int cmp = compair_numbers(*head1, *head2);

    if (s1 == 1)
    {
        /* A (+) - B (+) */
        if (cmp == 0)
        {
            insert_at_first(headR, tailR, 0);
            printf("Final Result: 0\n");
            return SUCCESS;
        }
        else if (cmp == 1)
        {
            subtract_magnitude(head1, tail1, head2, tail2, headR, tailR);
            if (*headR) (*headR)->sign = 1;
        }
        else
        {
            subtract_magnitude(head2, tail2, head1, tail1, headR, tailR);
            if (*headR) (*headR)->sign = -1;
        }
    }
    else
    {
        /* (-A) - (-B) = B - A */
        if (cmp == 0)
        {
            insert_at_first(headR, tailR, 0);
            printf("Final Result: 0\n");
            return SUCCESS;
        }
        else if (cmp == 1)
        {
            subtract_magnitude(head1, tail1, head2, tail2, headR, tailR);
            if (*headR) (*headR)->sign = -1;  // negative result
        }
        else
        {
            subtract_magnitude(head2, tail2, head1, tail1, headR, tailR);
            if (*headR) (*headR)->sign = 1;   // positive result
        }
    }

    printf("Final Result: ");
    if (*headR && (*headR)->sign == -1) printf("-");
    print_list(*headR);
    printf("\n");

    return SUCCESS;
}
