#include "apc.h"

int addition(Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    int carry = 0, data;
    Dlist *temp1 = tail1;
    Dlist *temp2 = tail2;

    while (temp1 != NULL || temp2 != NULL)
    {
        int dat1 = (temp1 != NULL) ? temp1->data : 0;
        int dat2 = (temp2 != NULL) ? temp2->data : 0;

        int sum = dat1 + dat2 + carry;
        data = sum % 10;

        if (sum >= 10)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        dl_insert_first(res_head, res_tail, data);

        if (temp1 != NULL) temp1 = temp1->prev;
        if (temp2 != NULL) temp2 = temp2->prev;
    }

    if (carry)
    {
        dl_insert_first(res_head, res_tail, carry);
    }

    return 1;
}



  int subtraction(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail, int *result_sign) 
{
    int cmp = compare_list(head1, head2);

    if (cmp == 0) 
    {
        dl_insert_first(res_head, res_tail, 0);
        *result_sign = 1; 
        return SUCCESS;
    }

    if (cmp == -1) 
    {
        Dlist *temp_h = head1; 
        head1 = head2;
         head2 = temp_h;
        Dlist *temp_t = tail1; 
        tail1 = tail2; 
        tail2 = temp_t;
        *result_sign = -(*result_sign); 
    }

    int borrow = 0;
    Dlist *temp1 = tail1;
    Dlist *temp2 = tail2;

    while(temp1 != NULL || temp2 != NULL) 
    {
        int dat1 = temp1->data;
        int dat2 = (temp2 != NULL) ? temp2->data : 0;
        int sub = dat1 - dat2 - borrow;

        if (sub < 0) 
        {
            sub = sub + 10;
            borrow = 1;
        } 
        else 
        {
            borrow = 0;
        }

        dl_insert_first(res_head, res_tail, sub);

        temp1 = temp1->prev;
        if (temp2 != NULL) {
            temp2 = temp2->prev;
        }
    }

    return SUCCESS;
}

int multiplication(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    Dlist *list2 = tail2;
    Dlist *res1_h = NULL, *res1_t = NULL;
    Dlist *res2_h = NULL, *res2_t = NULL;
    int shift = 0;

    while (list2 != NULL)
    {
        for (int i = 0; i < shift; i++)
        {
            dl_insert_first(&res2_h, &res2_t, 0);
        }

        int carry = 0;
        Dlist *list1 = tail1;

        while (list1 != NULL)
        {
            int prod = (list1->data * list2->data) + carry;
            int digit = prod % 10;
            carry = prod / 10;

            dl_insert_first(&res2_h, &res2_t, digit);
            list1 = list1->prev;
        }

        if (carry > 0)
        {
            dl_insert_first(&res2_h, &res2_t, carry);
        }

        if (res1_h == NULL)
        {
            res1_h = res2_h;
            res1_t = res2_t;
        }
        else
        {
            *res_head = NULL;
            *res_tail = NULL;

            addition(res1_t,res2_t,res_head,res_tail);

            free_list(res1_h);
            free_list(res2_h);

            res1_h = *res_head;
            res1_t = *res_tail;
        }

        res2_h = NULL;
        res2_t = NULL;
        shift++;
        list2 = list2->prev;
    }

    *res_head = res1_h;
    *res_tail = res1_t;

    return SUCCESS;
}

int division(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail)
{
    if (head2 != NULL && head2->data == 0 && head2->next == NULL)
    {
        printf("Cannot divide by zero.\n");
        return FAILURE;
    }

    *res_head = NULL;
    *res_tail = NULL;

    Dlist *dividend_ptr = head1;
    Dlist *list3_head = NULL;
    Dlist *list3_tail = NULL;

    while (dividend_ptr != NULL)
    {
        dl_insert_last(&list3_head, &list3_tail, dividend_ptr->data);

        while (list3_head != NULL && list3_head->data == 0 && list3_head->next != NULL)
        {
            Dlist *temp = list3_head;
            list3_head = list3_head->next;
            if (list3_head) list3_head->prev = NULL;
            free(temp);
        }
        if (list3_head == NULL) list3_tail = NULL;

        int count=0;
        
        while (1)
        {
          
            int cmp = compare_list(list3_head, head2);
            
            if (cmp == -1) 
            {
                break;
            }

            Dlist *sub_head = NULL;
            Dlist *sub_tail = NULL;
            int sign = 1;

            subtraction(list3_head, head2, list3_tail, tail2, &sub_head, &sub_tail, &sign);

            free_list(list3_head);

            list3_head = sub_head;
            list3_tail = sub_tail;

            while (list3_head != NULL && list3_head->data == 0 && list3_head->next != NULL)
            {
                Dlist *temp = list3_head;
                list3_head = list3_head->next;
                if (list3_head) list3_head->prev = NULL;
                free(temp);
            }
            if (list3_head == NULL) list3_tail = NULL;

            count++;
        }

        dl_insert_last(res_head, res_tail, count);

        dividend_ptr = dividend_ptr->next;
    }

    while ((*res_head) != NULL && (*res_head)->data == 0 && (*res_head)->next != NULL)
    {
        Dlist *temp = *res_head;
        *res_head = (*res_head)->next;
        if (*res_head) (*res_head)->prev = NULL;
        free(temp);
    }

    free_list(list3_head);

    return SUCCESS;
}
