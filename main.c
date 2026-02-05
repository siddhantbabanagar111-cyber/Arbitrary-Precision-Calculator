#include "apc.h"

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    char operator;
    char option;

    do {
        if (argc != 4) {
            printf("Invalid Arguments\n");
            printf("Usage: %s <num1> <op> <num2>\n", argv[0]);
            return FAILURE;
        }
        char *num1 = argv[1];
        char *op = argv[2];
        char *num2 = argv[3];

        /* Function for extracting the operator */
        operator = op[0];

        /* create lists: make sure previous lists are NULL (they are initially) */
        if (create_list(&head1, &tail1, num1) == FAILURE) {
            return FAILURE;
        }
        printf("1st Number: ");
        if (head1 && head1->sign == -1) printf("-");
        print_list(head1);
        printf("\n");

        if (create_list(&head2, &tail2, num2) == FAILURE) {
            return FAILURE;
        }
        printf("2nd Number: ");
        if (head2 && head2->sign == -1) printf("-");
        print_list(head2);
        printf("\n");

        /* initialize result pointers before each operation */
        headR = tailR = NULL;

        switch (operator) {
            case '+':
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                break;

            case '-':
                subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                break;

            case '*':
                multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                break;

            case '/':
                division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                break;

            default:
                printf("Invalid Input:-( Try again...\n");
                return FAILURE;
        }

        printf("Want to continue? Press [yY | nN]: "); 
		scanf("\n%c", &option);
    } while (option == 'y' || option == 'Y');

    return SUCCESS;
}
