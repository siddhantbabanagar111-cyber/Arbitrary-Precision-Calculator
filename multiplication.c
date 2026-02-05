/* multiplication.c */
#include "apc.h"

static int add_magnitude_local(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;

    int carry = 0;

    while (t1 != NULL || t2 != NULL || carry != 0)
    {
        int x = (t1 ? t1->data : 0);
        int y = (t2 ? t2->data : 0);

        int sum = x + y + carry;

        insert_at_first(headR, tailR, sum % 10);
        carry = sum / 10;

        if (t1) t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }
    return SUCCESS;
}

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int s1 = (*head1 ? (*head1)->sign : 1);
    int s2 = (*head2 ? (*head2)->sign : 1);

    /* If either number is zero */
    if (!*head1 || (!((*head1)->next) && (*head1)->data == 0) || !*head2 || (!((*head2)->next) && (*head2)->data == 0))
    {
        insert_at_first(headR, tailR, 0);
        if (*headR) (*headR)->sign = 1;
        printf("Final Result: 0\n");
        return SUCCESS;
    }

    Dlist *p2 = *tail2;
    Dlist *sumH = NULL, *sumT = NULL;
    int pos = 0;

    while (p2 != NULL)
    {
        Dlist *tempH = NULL, *tempT = NULL;
        int carry = 0;

        /* Add zeros for shifting (at tail -> least significant side we append zeros at end using insert_at_last) */
        for (int i = 0; i < pos; i++)
            insert_at_last(&tempH, &tempT, 0);

        Dlist *p1 = *tail1;

        while (p1 != NULL)
        {
            int mul = p1->data * p2->data + carry;
            insert_at_first(&tempH, &tempT, mul % 10);
            carry = mul / 10;
            p1 = p1->prev;
        }

        if (carry)
            insert_at_first(&tempH, &tempT, carry);

        /* Add temp result to the final sum */
        Dlist *newSumH = NULL, *newSumT = NULL;

        add_magnitude_local(&sumH, &sumT, &tempH, &tempT, &newSumH, &newSumT);

        /* free previous sum lists (old sumH) */
        if (sumH) {
            Dlist *n = sumH;
            while (n) {
                Dlist *nx = n->next;
                free(n);
                n = nx;
            }
        }

        sumH = newSumH;
        sumT = newSumT;

        pos++;
        p2 = p2->prev;
    }

    *headR = sumH;
    *tailR = sumT;

    /* Apply final sign */
    if (*headR)
        (*headR)->sign = (s1 * s2);

    printf("Final Result: ");
    if (*headR && (*headR)->sign == -1) printf("-");
    print_list(*headR);
    printf("\n");

    return SUCCESS;
}
