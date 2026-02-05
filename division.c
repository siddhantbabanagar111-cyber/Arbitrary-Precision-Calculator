/* division.c */
#include "apc.h"

typedef struct count{
    int data;
    struct count *next;
} CountNode;

void increment_count(CountNode **head){
    CountNode *new = (CountNode*)malloc(sizeof(CountNode));
    new->data = 1;
    new->next = *head;
    *head = new;
}

int count_length(CountNode *head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

/* copy_number: copy digits (magnitude only). newHead/newTail set appropriately.
   Leaves sign on new head as +1 if it exists. */
void copy_number(Dlist *head, Dlist *tail, Dlist **newHead, Dlist **newTail) {
    Dlist *current = head;
    *newHead = *newTail = NULL;
    while (current) {
        insert_at_last(newHead, newTail, current->data);
        current = current->next;
    }
    if (*newHead) (*newHead)->sign = 1;
}

/* Helper: subtract magnitudes assuming headA >= headB (magnitudes), produce headR */
static int subtract_magnitude_local(Dlist **headA, Dlist **tailA, Dlist **headB, Dlist **tailB, Dlist **headR, Dlist **tailR)
{
    Dlist *t1 = *tailA;
    Dlist *t2 = *tailB;
    int borrow = 0;

    while (t1 != NULL)
    {
        int x = t1->data;
        int y = (t2 != NULL) ? t2->data : 0;

        x = x - borrow;
        borrow = 0;

        if (x < y)
        {
            x = x + 10;
            borrow = 1;
        }

        insert_at_first(headR, tailR, x - y);

        t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    /* REMOVE LEADING ZEROS (leave single zero if result is 0) */
    while ((*headR) && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        if (*headR) (*headR)->prev = NULL;
        free(temp);
    }
    return SUCCESS;
}

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /*int s1 = 1, s2 = 1;
    if (*head1) s1 = (*head1)->sign;
    if (*head2) s2 = (*head2)->sign;*/
    int s1=(*head1?(*head1)->sign:1);
    int s2=(*head2?(*head2)->sign:1);

    /* Division by zero check */
    if ((*head2) == NULL || ((!(*head2)->next) && (*head2)->data == 0)) {
        printf("Division by zero is not allowed\n");
        return FAILURE;
    }

    /* Initialize output */
    *headR = *tailR = NULL;

    /* If dividend < divisor → quotient = 0 */
    if (compair_numbers(*head1, *head2) == -1) {
        insert_at_last(headR, tailR, 0);
        if (*headR) (*headR)->sign = (s1 * s2);
        printf("Final Result: ");
        if (*headR && (*headR)->sign == -1) printf("-");
        print_list(*headR);
        printf("\n");
        return SUCCESS;
    }

    CountNode *count = NULL;

    /* Make working copies (magnitude only) */
    Dlist *t1 = NULL, *t1_tail = NULL;   /* dividend copy */
    Dlist *t2 = NULL, *t2_tail = NULL;   /* divisor copy (constant) */

    copy_number(*head1, *tail1, &t1, &t1_tail);
    copy_number(*head2, *tail2, &t2, &t2_tail);

    /* MAIN LOOP: repeatedly subtract divisor from dividend */
    while (t1 != NULL && compair_numbers(t1, t2) != -1)  /* while t1 >= t2 */
    {
        Dlist *ResH = NULL, *ResT = NULL;

        /* Use TEMP copies because subtraction modifies inputs */
        Dlist *tempH = NULL, *tempT = NULL;
        Dlist *tempDH = NULL, *tempDT = NULL;

        copy_number(t1, t1_tail, &tempH, &tempT);
        copy_number(t2, t2_tail, &tempDH, &tempDT);

        subtract_magnitude_local(&tempH, &tempT, &tempDH, &tempDT, &ResH, &ResT);

        /* Free old dividend copy */
        Dlist *old = t1;
        while (old) { 
            Dlist *x = old; 
            old = old->next; 
            free(x); 
        }

        /* Update dividend working copy */
        t1 = ResH;
        t1_tail = ResT;

        /* Increment quotient count */
        increment_count(&count);

        /* Stop if result is exactly 0 */
        if (t1 && !t1->next && t1->data == 0)
            break;
    }

    /* Convert count list → final quotient number */
    int q = count_length(count);

    if (q == 0) {
        insert_at_last(headR, tailR, 0);
    } else {
        int temp = q;
        while (temp > 0) {
            insert_at_first(headR, tailR, temp % 10);
            temp /= 10;
        }
    }

    /* Ensure sign is set and zero is positive */
    if (*headR) {
        (*headR)->sign = (q == 0) ? 1 : (s1 * s2);
    }

    /* free CountNode list */
    while (count) {
        CountNode *nx = count->next;
        free(count);
        count = nx;
    }

    /* free any leftover working copies (t1 might already be used as result list) */
    if (t1 && (t1 != *headR)) {
        Dlist *node = t1;
        while (node) {
            Dlist *nx = node->next;
            free(node);
            node = nx;
        }
    }
    if (t2) { /* free divisor working copy */
        Dlist *node = t2;
        while (node) {
            Dlist *nx = node->next;
            free(node);
            node = nx;
        }
    }

    printf("Final Result: ");
    if (*headR && (*headR)->sign == -1) printf("-");
    print_list(*headR);
    printf("\n");
    return SUCCESS;
}
