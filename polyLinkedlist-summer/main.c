#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef struct
{
  int coefficient;
  int exponent;
  struct polyNode *next;
} polyNode;

typedef struct
{
  polyNode *head ;
  polyNode *tail ;
} polyLinkedList;


 //Example:-
 //3x2 + 5x + 7
void initpolyLinkedList(polyLinkedList *list){
  list->head=NULL;
  list->tail=NULL;
}


polyNode* newNode(int coef, int exp){
  polyNode* node = malloc(sizeof(polyNode));
  node->coefficient=coef;
  node->exponent=exp;
  node->next=NULL;
  return node;
}


void addHead(polyLinkedList *list,int coef,int exp){
   polyNode*node=newNode(coef,exp);
   node->next=list->head;
   list->head=node;
   if(list->tail==NULL)
     list->tail=node;
}


void addTail(polyLinkedList*list,int coef,int exp){
  polyNode* node=newNode(coef,exp);
  if (list->head==NULL)
    list->head=list->tail=node;
  else{
    list->tail->next=node;
    list->tail=node;
  }
}


//it displays polynomial in the form 3*x^2 + 5*x^1 + 7
void display_poly (polyLinkedList *x){
  polyNode* first = x->head;

  while(first!=NULL)
  {
     if (first->exponent!=0){
       printf(" %dx^%d", first->coefficient, first->exponent);
     }
     else {
       printf(" %d", first->coefficient);
     }

     if(first->next != NULL)
       printf(" +");

     first=first->next;
  }

  printf("\n");
}


float get_valu (polyLinkedList *q, float x) {
  polyNode*polynode=q->head;
  float result=0.0;

  while (polynode!=NULL){

    result+=(polynode->coefficient * (pow(x,polynode->exponent)));
    polynode=polynode->next;

  }

  return result;
}


//For example if Polynomial is 3*x^2 + 5 * x^1 + 7 and x = 1 it will return 15


 polyLinkedList * poly_add(polyLinkedList *x, polyLinkedList *y)
 {
   polyNode*poly1=x->head;
   polyNode*poly2=y->head;
   polyLinkedList* polylist = malloc(sizeof(polyLinkedList));
   initpolyLinkedList(polylist);

   while(poly1 && poly2)
   {
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is
        // and move its pointer
      if(poly1->exponent > poly2->exponent)
        {

            addTail(polylist,poly1->coefficient,poly1->exponent);
            poly1 = poly1->next;
        }

        // If power of 2nd polynomial is greater then 1st, then store 2nd as it is
        // and move its pointer
        else if(poly1->exponent < poly2->exponent)
        {

          addTail(polylist,poly2->coefficient,poly2->exponent);
           poly2 = poly2->next;
        }

        // If power of both polynomial numbers is same then add their coefficients
        else
        {
            addTail(polylist,poly1->coefficient+poly2->coefficient,poly1->exponent);
              poly1 = poly1->next;
              poly2 = poly2->next;
        }

    }
while(poly1 || poly2)
    {
        if(poly1)
        {
             addTail(polylist,poly1->coefficient,poly1->exponent);
             poly1 = poly1->next;
        }
        if(poly2)
        {

            addTail(polylist,poly2->coefficient,poly2->exponent);
            poly2 = poly2->next;

        }

    }
    return polylist;
}



//Add two polynomial X to Y and return new polynomial for X+Y


int main (){


   int x,y,Num_Terms;

   printf("Enter Number Of Terms:");
   scanf("%d",&Num_Terms);
   printf("\n");
   polyLinkedList polylist1 ;
   initpolyLinkedList(&polylist1);

    while(Num_Terms!=0){
    printf("Enter coefficient:");
    scanf("%d",&x);
    printf("Enter exponent:");
    scanf("%d",&y);
    addTail(&polylist1,x,y);
    Num_Terms--;
          }

  //first polynomial:3*x^2 + 5 * x^1 + 7
  //addHead(&polylist1,7,0);
 // addHead(&polylist1,5,1);
  //addHead(&polylist1,3,2);

    printf("\nfirstpolyniomal:");
    display_poly (&polylist1);
    printf("Get value of polyniomal when x =");
    int X;
    scanf("%d",&X);
    printf("result of poly1:%2.f\n\n\n", get_valu(&polylist1, X));

   polyLinkedList polylist2;
   initpolyLinkedList(&polylist2);

  //second polynomial:6x^3+3x^2+10x^1
  //addHead(&polylist2,11,1);
  //addHead(&polylist2,2,2);
  //addHead(&polylist2,6,3);
  //addHead(&polylist2,8,4);

   printf("Enter Number Of Terms:");
   scanf("%d",&Num_Terms);
   printf("\n");

  while(Num_Terms!=0){
     printf("Enter coefficient:");
     scanf("%d",&x);
     printf("Enter exponent:");
     scanf("%d",&y);
     addTail(&polylist2,x,y);
     Num_Terms--;
       }


   printf("\nsecondpolyniomal:");
   display_poly (&polylist2);
   printf("Get value of polyniomal when x =");
   scanf("%d",&X);
   printf("result of poly2:%2.f\n\n\n", get_valu(&polylist2, X));

   polyLinkedList* addpoly;
   addpoly = poly_add(&polylist1, &polylist2);

  printf("\naddition of two polyniomals:");
  display_poly (addpoly);

  return 0;
}
