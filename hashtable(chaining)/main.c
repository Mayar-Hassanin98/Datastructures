#include <stdio.h>
#include <stdlib.h>
#define size 13
struct node
{
               int data;
               struct node *next;
};
struct node *head[size]={NULL},*c;
void add()
{
    int i,key;
    printf("\nenter a value to insert into hash table\n");
    scanf("%d",&key);
    i=key%size;
    struct node * newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data=key;
    newnode->next = NULL;
    if(head[i] == NULL)
        head[i] = newnode;
    else
    {
        c=head[i];
        while(c->next != NULL)
        {
           c=c->next;
        }
        c->next=newnode;
    }
}
void lookUp()
{
    int key,index;
    printf("\nenter the value you want to lookup for:\n");
    scanf("%d",&key);
    index=key%size;
    if(head[index] == NULL)
        printf("\n element not found\n");
    else
    {
        for(c=head[index];c!=NULL;c=c->next)
        {
            if(c->data == key)
                {
                    printf(" element found at index (%d)\n",index);
                    break;
                }
        }
        if(c==NULL)
            printf("\n  element not found\n");

    }
}
void print()
{
    int i;
    for(i=0;i<size;i++)
          {
           printf("\nentries at index %d\n",i);
               if(head[i] == NULL)
               {
               printf("NULL\n");

               }
               else
               {
                              for(c=head[i];c!=NULL;c=c->next){
                              printf("%d->",c->data);
                               }
                               printf("NULL");
               }

          }



}
void main()
{
    int choice,i;
    while(1)
      {
        printf("\nchoose: 1.add\n        2.print\n        3.LookUp\n        4.Exit\n\n");
        printf("you choose:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                add();
                break;
            case 2:
                print();
                break;
            case 3:
                lookUp();
                break;
            case 4:exit(0);
        }
     }
}
