#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1
#define LIST_EMPTY -2
#define DATA_NOT_FOUND -3

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;

int dl_insert_last(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
int validate_operand(char *str);
int addition(Dlist *tail1,Dlist *tail2,Dlist **res_head,Dlist **res_tail);
int subtraction(Dlist *head1,Dlist *head2,Dlist *tail1,Dlist *tail2,Dlist **res_head,Dlist **res_tail,int *result_sign);
int multiplication(Dlist *head1,Dlist *head2,Dlist *tail1,Dlist *tail2,Dlist **res_head,Dlist **res_tail);
int division(Dlist *head1, Dlist *head2, Dlist *tail1, Dlist *tail2, Dlist **res_head, Dlist **res_tail);
int dl_insert_first(Dlist **head, Dlist **tail, int data);
void free_list(Dlist *head) ;
int compare_list(Dlist *head1, Dlist *head2);
void remove_zeros(Dlist **head, Dlist **tail);



#endif