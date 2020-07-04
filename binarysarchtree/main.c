#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    char *Name [50];
    int Number;
    struct Node *left,*right;

} Node;


Node *newNode(char name[],int number)
{
    Node *n=malloc(sizeof(Node));
    strcpy(n->Name,name);
    n->Number=number;
    n->left=NULL;
    n->right=NULL;
    return n;
}


 Node* insert(Node*node, char name[],int number)
{
      if(node==NULL)
         return newNode(name,number);


       else if  (strcasecmp(name,node->Name) == 0)
        printf("Name already exist");

        else if (number==node->Number)
        printf("Number already exist");

       else if( strcasecmp(name,node->Name) < 0)
         node->left=insert(node->left,name,number);

       else if (strcasecmp(name,node->Name) > 0)
        node->right=insert(node->right,name,number);

       return node;
}


Node * search(Node*t, char name[])
 {
      while(t!=NULL)
       {
         if (strcasecmp(name,t->Name)==0)
            return t;

         else if (strcasecmp(name,t->Name) < 0)
            t=t->left;

         else
            t=t->right;

         }

     return NULL;
 }


 Node* FindMin(Node*root)
{
  if(root==NULL)
     return NULL;
  else if(root->left!=NULL)
      return FindMin(root->left);
  else
      return root;
}




Node* Delete(Node *t,char name[])
{
      Node*temp;

        if(t==NULL)
          {
           return NULL;
          }

        else if(strcasecmp(name,t->Name)<0)
          {
           t->left = Delete(t->left, name);
          }

        else if(strcasecmp(name,t->Name)>0)
        {
           t->right = Delete(t->right, name);
         }

       else
      {
        if(t->right!=NULL && t->left!=NULL )
            {
              temp = FindMin(t->right);
              strcpy(t->Name,temp->Name);
              t->Number=temp->Number;
              t-> right = Delete(t->right,temp->Name);
             }
       else
             {
               temp = t;
               if(t->left == NULL)
                t = t->right;
             else if(t->right == NULL)
                 t= t->left;

                 free(temp);
                 printf("username has deleted ");
                   }
                 }

return t;
}


//root/left/right
 void preOrdertraverse(Node*t)
 {
     if(t!=NULL){
      printf("Name: %s - PhoneNumber: %dxxxxxx\n",t->Name,t->Number);
      preOrdertraverse(t->left);
      preOrdertraverse(t->right);
     }



 }


 //left/right/root
 void postOrdertraverse(Node*t)
 {
     if(t!=NULL){

      postOrdertraverse(t->left);
      postOrdertraverse(t->right);
      printf("Name: %s - PhoneNumber: %dxxxxxx\n",t->Name,t->Number);

     }


 }

 //left/root/right
void InOrdertraverse(Node*t)
 {
     if(t!=NULL){

       InOrdertraverse(t->left);
       printf("Name: %s - PhoneNumber: %dxxxxxx\n",t->Name,t->Number);
       InOrdertraverse(t->right);

     }


 }






int main()
{   Node*node=NULL;
    char Name[50];
    int Number;
    FILE* f = fopen("Dictionary.txt", "r");
    while (!feof(f))
       {
         fscanf(f, "%s", Name);
         fscanf(f, "%d",&Number);
         node = insert(node,Name,Number);
              }


 int users;
    printf("please enter number of users you want to insert:");
    scanf("%d",&users);
    char*t;
    Node*n=NULL;
     while(users!=0){
          printf("\nEnter a new Username:");
          scanf("%s",Name);
          printf("Enter a new UserNumber:");
          scanf("%d",&Number);
          node=insert(node,Name,Number);
          users--;
     }



    Node* N=NULL;
    char* g;
    char name[50];
    printf("\nsearch for a username:");
    scanf("%s",name);
    N=search(node,name);

    if(N!=NULL){

         printf("Name: %s - PhoneNumber: %dxxxxxx",N->Name,N->Number);
    }

    else  printf("not found\n");




      char y[50];
      printf("\nDelete a Username:");
      scanf("%s",y);
      Node* M=Delete(node,y);




    int selection;
           do
                {
                    printf("\nselect(1) if you want to print preOrdertraversal \n");
                    printf("select(2) if you want to change InOrdertraversal \n");
                    printf("select(3) if you want to change  postOrdertraversal \n");
                    printf("Enter your selection:");
                    scanf("%d",&selection);

                    if(selection==1)
                    {
                        preOrdertraverse(node);
                    }
                    else if(selection==2)
                    {
                        InOrdertraverse(node);
                    }

                    else if(selection==3)
                    {
                        postOrdertraverse(node);
                    }
                    else
                        break;

             }while(selection<4);


    return 0;
}
