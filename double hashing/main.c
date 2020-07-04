#include <stdio.h>
#include<stdlib.h>
#define SIZE 13

int array[SIZE]={NULL};

int hash1(int value)
{
    return value%SIZE;
}

int hash2(int value)
{
    return 7-(value%7);
}
void insert(int value)
{
 int index;
 for(int i=0;i<SIZE;i++)
 {
    index=(hash1(value)+i*hash2(value))%SIZE;
    if(array[index] == NULL)
    {
        array[index]=value;
        break;
    }
 }
}
void search(int value)
{
 int index;
 for(int i=0;i<SIZE; i++)
 {
    index=(hash1(value)+i*hash2(value))%SIZE;
    if(array[index]==value)
    {
      printf("\n value is found --> array[%d]=%d",index,value);
      break;
    }
  }
}
void display()
{

  int i;
  for(i=0;i<SIZE; i++)
    printf("\narray[%d]= %d",i,array[i]);

}
int main()
{
    insert(18);
    insert(41);
    insert(22);
    insert(44);
    display();
    search(44);
   return 0;
}
