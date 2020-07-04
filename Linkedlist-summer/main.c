#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int data;
    struct Node*next;
}Node;


typedef struct{
    Node*Head;
    Node*Tail;
}LinkedList;

//It initializes Linked List so that there are no elements inserted.
void initLinkedList(LinkedList *list){

    list->Head=NULL;
    list->Tail=NULL;

}

//It returns 1 if linked list is empty or 0 otherwise.
int isEmpty(LinkedList *list){
    if(list->Head==NULL)
         return 1;
    else
         return 0;
}

//It allocates memory for new node with the given value
Node* newNode(int val){
    Node* node=malloc(sizeof(Node));
    node->data=val;
    node->next=NULL;
        return node;
}

//It adds new node to the beginning of the linked list
void addHead(LinkedList *list,int value){
    Node*node=newNode(value);
    node->next=list->Head;
    list->Head=node;

    if(list->Tail==NULL)
       list->Tail=node;
}

// adds new node to the end of the linked list
void addTail(LinkedList *list,int value){
    Node* node=newNode(value);

    if (list->Head==NULL){
        list->Head=list->Tail=node;

        }

    else{
       list->Tail->next=node;
       list->Tail=node;
        }

}

//It removes the first node from the linked list
void deleteHead(LinkedList *list){
    Node*First=list->Head;

    if (First!=NULL){
      list->Head=First->next;
      free(First);
      if (list->Head==NULL)
        list->Tail=NULL;
        }
}

//It removes the last node from the linked list
void deleteTail(LinkedList *list){

    Node*n=list->Head;

   // if list has only one element
    if(n==NULL){
        free(n);
        list->Head=list->Tail=NULL;
        }


   //finding the item before the tail
    while (n&&n->next!=list->Tail){
        n=n->next;
        }

    free(list->Tail);
    list->Tail=n;

    if (list->Tail!=NULL)// make sure list is not empty
        list->Tail->next=NULL;
}


void showLinkedList(LinkedList *list){
    Node*first=list->Head;

    while( first!=NULL){
       printf("%d  ",first->data);
       first=first->next;
        }
printf("\n");

}


int main()
{
    LinkedList *list;
    initLinkedList(&list);
    addHead(&list,4);
    addHead(&list,3);
    addHead(&list,2);
    addHead(&list,1);
    addTail(&list,5);
    printf("list:");
    showLinkedList(&list);
    printf("\nThe list after deleting from head: ");
    deleteHead(&list);
    showLinkedList(&list);
    printf("\nThe list after deleting from tail: ");
    deleteTail(&list);
    showLinkedList(&list);
    printf("\nThe list after deleting from head: ");
    deleteHead(&list);
    showLinkedList(&list);
    printf("\nThe list after deleting from tail: ");
    deleteTail(&list);
    showLinkedList(&list);



    return 0;
}
