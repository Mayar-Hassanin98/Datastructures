#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef union
{
    float fData;
    char* cpData;
} Item;
/*
 *
 */


typedef struct Node
{
    Item data;
    struct Node* next;
} Node;




typedef struct
{

    Node*top;/* TODO: ADD YOUR CODE HERE */
} Stack;
/*
 *
 */
Node* newnode(Item x)
{
    Node*n=malloc(sizeof(Node));
    n->data=x;
    n->next=NULL;
    return n;
}


void init(Stack *s)
{
    s->top=NULL;/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
int isEmpty(Stack *s)
{
    if(s->top==NULL)
        return 1;
    else
        return  0;
}
/*
 *
 */
Item top(Stack *s)
{
    return s->top->data;
}
/* TODO: ADD YOUR CODE HERE */

/*
 *
 */
Item pop(Stack *s)
{
    Item x;
    Node*n=s->top;
    s->top=s->top->next;
    x=n->data;
    free(n);
    return x;

    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void push(Stack *s, Item val)
{
    Node*n=newnode(val);
    n->next=s->top;
    s->top=n;
    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void destroy(Stack *s)
{
    Node*n=s->top;
    while( s->top!=NULL)
    {
        s->top=s->top->next;
        free(n);
        n=s->top;
    }
    s->top=NULL; 	/* TODO: ADD YOUR CODE HERE */
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)*4 --> 23+4*
 */

int piority (char op)
{

    if(op=='*'||op=='/')
        return 2;
    if (op=='+'||op=='-')
        return 1;

    return 3;

}

void infixToPostfix(char* infix, char* postfix)
{
    Stack s;
    init(&s);
    int j=0;
    Item x;
    postfix[0]='\0';
    char* ptr=strtok(infix," ");
    while(ptr!=NULL)

    {

        if(isdigit(ptr[0])||(strlen(ptr)>0&&ptr[0]=='-'&&isdigit(ptr[1])))
        {
            strcat(postfix,ptr);
            strcat(postfix," ");


        }
        else if (isEmpty(&s)|| strcmp (top(&s).cpData,"(")==0)
        {
            x.cpData=malloc(strlen(ptr)+1);
            strcpy(x.cpData,ptr);
            push(&s,x);
        }
        else if ( strcmp (ptr,")")==0)
        {
            while(strcmp (top(&s).cpData,"(")!=0)
            {
                strcat(postfix,pop(&s).cpData);
                strcat(postfix," ");

            }
            pop(&s);
        }
        else
        {
            while(!isEmpty(&s)&&piority(*(top(&s).cpData))>=piority(*ptr)&&strcmp (x.cpData,"(")!=0)
            {
                strcat(postfix,pop(&s).cpData);
                strcat(postfix," ");

            }
            x.cpData=malloc(strlen(ptr)+1);
            strcpy(x.cpData,ptr);
            push(&s,x);
        }
        ptr=strtok(NULL," ");
    }
    while(!isEmpty(&s))
    {
        strcat(postfix,pop(&s).cpData);
        strcat(postfix," ");

    }
    strcat(postfix,"\0");

}
/* for (int i=0; i<strlen(infix); i++)

 {        x.cpData=(infix[i]);

     if(isdigit(infix[i]))
     {
         postfix[j++]=infix[i];
          postfix[j++]=' ';
     }
    else if (isEmpty(&s)||top(&s).cpData=='(')
     {
         push(&s,x);
     }
     else if (x.cpData==')')
     {
         while(top(&s).cpData!='(')
         {
             postfix[j++]=pop(&s).cpData;
              postfix[j++]="  ";
         }
         pop(&s);
     }
     else
     {
         while(!isEmpty(&s)&&piority(top(&s).cpData)>=piority(x.cpData))
         {
             postfix[j++]=pop(&s).cpData;
            postfix[j++]=' ';
         }
         push(&s,x);
     }
 }
 while(!isEmpty(&s))
 {
     postfix[j++]=pop(&s).cpData;
      postfix[j++]=' ';
 }
 postfix[j]='\0';
*/




/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */


float calculate(char postifix,float op1,float op2)
{

    if(postifix=='+')
        return (op1+op2);
    if (postifix=='-')
        return (op1-op2);
    if(postifix=='*')
        return (op1*op2);
    if (postifix=='/')
        return (op1/op2);
    if(postifix=='^')
    return ( pow (op1,op2));

}


float evaluatePostfix(char* postfix)
{
    Stack s;
    init(&s);
    float op1,op2;
    Item val;
    char *t;

    t=strtok(postfix," ");
    while( t!=NULL)
    {

        if (isdigit(t[0])||(t[0]=='-'&&isdigit(t[1])))
        {

            Item x;
            x.fData=atof(t);
            push(&s,x);

        }

        else
        {
            op2=pop(&s).fData;
            op1=pop(&s).fData;
            val.fData=calculate(t[0],op1,op2);
            push(&s,val);

        }
        t=strtok(NULL," ");

    }
    val.fData=pop(&s).fData;
    return val.fData;
}
/*
 *
 */
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}

