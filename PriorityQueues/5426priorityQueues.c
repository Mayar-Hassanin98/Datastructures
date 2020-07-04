#include <stdio.h>
#include <stdlib.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
    char* cName;
    double balance;
    int order;
} Item;

int left(int index)
{
    return 2*index;
}
int right(int index)
{
    return 2*index+1;
}



/*
 * Heapify index i in array of Items with size n
 */
void max_heapify(Item *arr, int n, int i)
{
    int L,R;
    int largest;
    L=left(i);
    R=right(i);
    if(L<=n&&arr[L].balance>arr[i].balance)
        largest=L;
    else
     largest=i;
    if ( L<=n&&arr[L].balance==arr[i].balance)
    {
        if( arr[L].order<arr[i].order)
            largest=L;
    }
    if(R<=n&&arr[R].balance>arr[largest].balance)
        largest=R;
     if(R<=n&&arr[R].balance==arr[largest].balance)
    {
        if (arr[R].order<arr[largest].order)
            largest=R;
    }
    if (largest!=i)
    {
        Item temp;
        temp=arr[largest];
        arr[largest]=arr[i];
        arr[i]=temp;
        max_heapify(arr,n+1,largest);
    }


    /* TODO: ADD YOUR CODE HERE */
}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{
    for(int i=n/2; i>=1; i--)
        max_heapify(arr, n+1, i);
}
/*
 * delete the item with max priority and then return it.
 */

Item extract_maximum(Item*arr,int n)
{
    Item maxarray;
        maxarray=arr[1];
        arr[1]=arr[n--];
        max_heapify(arr,n+1,1);



    return maxarray;

}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
    int i=1;
    int count=0;
    FILE* f = fopen(fname, "r");
    while (!feof(f) )
    {
        arr[i].cName=malloc(100);
        fscanf(f, "%s",arr[i].cName);
          fscanf(f, " %lf",&arr[i].balance);
      //printf("%s",arr[i].cName);
       // printf("%  lf\n",arr[i].balance);
        arr[i].order=i;
        i++;
        count ++;
    }
    return count;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{ Item popped;
    for (int i=n; i>0; i--) {
            popped=extract_maximum(arr, n+1);
           // printf("%d-customer'sName:%s\nbalance:%lf\n\n",popped.order,popped.cName,popped.balance);
              printf("%d-%s    %.2lf\n\n",popped.order,popped.cName,popped.balance);


          }


}
/*
 *,popped.order
 */
int main(int argc, char**argv)
{

    if(argc!=2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
