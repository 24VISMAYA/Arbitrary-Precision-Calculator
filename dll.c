#include "apc.h"


int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *nnode=malloc(sizeof(Dlist));
    if(nnode==NULL)return -1;

    nnode->data=data;
    nnode->prev=NULL;
    nnode->next=NULL;

    if(!*head && !*tail)
    {
        *head=*tail=nnode;
        return 0;
    }
    nnode->prev=*tail;
   (*tail)->next=nnode;
   *tail = nnode;
	return 0;

}

int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *nnode=malloc(sizeof(Dlist));
    if(!nnode)return -1;

    nnode->data=data;
        nnode->prev=NULL;
        if(*head==NULL)
        {
            nnode->next=NULL;
            *head=nnode;
            *tail=nnode;
            return SUCCESS;
            
        }
        nnode->next=*head;
        (*head)->prev=nnode;
        *head=nnode;
        return 0;

}

void print_list(Dlist *head)
{
    if(head==NULL)
    {
        printf("0\n");
        return ;
    }
    Dlist *temp=head;
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->next;
    }
    printf("\n");

}

void free_list(Dlist *head) 
{
    Dlist *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int compare_list(Dlist *head1, Dlist *head2)
{
    int count1 = 0, count2 = 0;
    Dlist *h1 = head1;
    Dlist *h2 = head2;

    while (h1 != NULL)
    {
        count1++;
        h1 = h1->next;
    }
    while (h2 != NULL)
    {
        count2++;
        h2 = h2->next;
    }

    if (count1 > count2) return 1;
    if (count1 < count2) return -1;

    h1 = head1; 
    h2 = head2;
    while (h1 != NULL)
    {
        if (h1->data > h2->data) return 1;
        if (h1->data < h2->data) return -1;
        h1 = h1->next;
        h2 = h2->next;
    }
    return 0;
}
 
void remove_zeros(Dlist **head, Dlist **tail)
{
    while ((*head) != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
    if (*head == NULL)
    {
        *tail = NULL;
    }
}

