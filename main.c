#include<stdio.h>
#include<stdlib.h>
#include "apc.h"



int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;

    if (argc < 4)
    {
        printf("Use: ./a.out <operand1> <operator> <operand2>\n");
        return -1;
    }
    
    int operand1=validate_operand(argv[1]);
    int operand2=validate_operand(argv[3]);
      char op = argv[2][0];
    if(operand1!=0 && operand2!=0)
    {
        printf("Both operand1 and 2 contains letters or invalid character.\n");
        printf("Invalid operand.\n");
        return FAILURE;
    }
    else if(operand1!= 0)
    {
        printf("Error: First operand contains letters or invalid characters.\n");
        printf("Invalid operand.\n");
        return FAILURE;
    }
    else if (operand2!= 0)
    {
        printf("Error: Second operand contains letters or invalid characters.\n");
        printf("Invalid operand.\n");
        return FAILURE;
    }
    else if (op != '+' && op != '-' && op != 'x' && op != '/')
    {
        printf("Error: '%c' is not a valid mathematical operator. Use +, -, x, or /.\n", op);
        printf("Invalid operation.\n");
        return FAILURE;
    }

    Dlist *res_head = NULL;
    Dlist *res_tail = NULL;

    int sign1 = 1, sign2 = 1;
    int result_sign = 1;
    char operation;

    if (argv[1][0] == '-')
    {
        sign1 = -1;
    }

    if (argv[3][0] == '-')
    {
        sign2 = -1;
    }

    switch (argv[2][0])
    {
        case '+':
            if (sign1 == sign2) 
            {
                result_sign = sign1;
                operation = '+';
            } 
            else 
            {
                result_sign = sign1;
                operation = '-';
            }
            break;

        case '-':
            if (sign1 != sign2) 
            {
                result_sign = sign1;
                operation = '+';
            } 
            else 
            {
                result_sign = sign1;
                operation = '-';
            }
            break;

        case 'x':
            result_sign = sign1 * sign2;
            operation = 'x';
            break;

        case '/':
            result_sign = sign1 * sign2;
            operation = '/';
            break;

        default:
            printf("Invalid operator\n");
            return 1;
    }

    int i = 0;
    if (argv[1][0] == '+' || argv[1][0] == '-')
    {
        i++;
    }
    while (argv[1][i] != '\0')
    {
        dl_insert_last(&head1, &tail1, argv[1][i] - '0');
        i++;
    }

    i = 0;
    if (argv[3][0] == '+' || argv[3][0] == '-')
    {
        i++;
    }
    while (argv[3][i] != '\0')
    {
        dl_insert_last(&head2, &tail2, argv[3][i] - '0');
        i++;
    }

    switch (operation)
    {
        case '+':
            addition(tail1, tail2, &res_head, &res_tail);
            break;

        case '-':
            subtraction(head1, head2, tail1, tail2, &res_head, &res_tail, &result_sign);
            break;

        case 'x':
            multiplication(head1, head2, tail1, tail2, &res_head, &res_tail);
            break;

        case '/':
            division(head1, head2, tail1, tail2, &res_head, &res_tail);
            break;
    }

    remove_zeros(&res_head, &res_tail);

    if (res_head != NULL && res_head->data == 0 && res_head->next == NULL)
    {
        result_sign = 1;
    }

    if (result_sign == -1)
    {
        printf("-");
    }

    print_list(res_head);


    return 0;
}
