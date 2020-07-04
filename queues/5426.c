#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct {
	char *name;
	int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node {
	Item data;
	struct Node* next;
} Node;
/*
 *
 */
typedef struct {
	struct Node *front, *rear;
} Queue;

 Node* newnode(Item x){
  Node *n = malloc(sizeof(Node));
  n->data=x;
  n->next=NULL;
 return n;
 }
/*
 *
 */
void init(Queue *q)
{
    q->front = q->rear = NULL;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if (q->front == NULL)
        return 1;
    else
        return 0;
}
/*
 *
 */
Item dequeue(Queue *q)
{
    int ptr;

    if(q->front == NULL)
        return 0;
    else {
        ptr = q->front->data;
        q->front = q->front->next;

        return ptr;
    }
}
/*
 *
 */
void enqueue(Queue *q, Item val)//correct
{
    Node *n = newnode(val);

    if(q->front==NULL){
        q->front=q->rear=n;
    }
    else {
        q->rear->next=n;
        q->rear=n;
    }
}

/*
 *
 */
void destroy(Queue *q)
{
   Node*n=q->front;
while(q->front!=NULL){
    q->front=q->front->next;
    free(n);
    n=q->front;
}
q->front=q->rear=NULL;
}

int ReadData(FILE *f, Queue *q, int current_time)
{
    char p_name[10]; // used only for file reading
    int starting_time; // used only for file reading
    int duration; // used only for file reading

    while(1) // Reading data from file loop
    {
        long line_number = ftell(f);
        int could_read = fscanf(f, "%s %d %d\n", p_name, &starting_time, &duration);

        if(isEmpty(q) == 1 && could_read == EOF)
        {
            return 1;//Terminate the main while loop
        }

        if(could_read != EOF)
        {
            if(starting_time > current_time)
            {
                fseek(f, line_number, SEEK_SET);//Move backward one line
                break;
            }
            else{// starting time == current time
                Item item = malloc(sizeof(Process));
                item->name = (char*) malloc(sizeof(char) * strlen(p_name));
                strcpy(item->name, p_name);
                item->remaining_time = duration;
                enqueue(q, item);
            }
        }
        else{ // End of file but queue still has data
            break;
        }
    }

    return 0;
}

/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    int current_time = 0; //related to right now

    Queue q;
    init(&q);

    FILE* f = fopen(filename, "r");

    while(1)
    {
        if(ReadData(f, &q, current_time))
        {
            printf("EOF\n");
            break;
        }

        if(isEmpty(&q))
        {
            printf("idle (%d-->%d)\n", current_time, current_time + 1);
        }
        else{
            Item front_item = dequeue(&q);

            front_item->remaining_time--;

            if(front_item->remaining_time == 0)
            {
                //we finished with this process
                printf("%s (%d-->%d) %s halts\n", front_item->name, current_time, current_time + 1, front_item->name);

                free(front_item->name);
                free(front_item);
            }
            else{
                // still we need this process
                printf("%s (%d-->%d)\n", front_item->name, current_time, current_time + 1);

                ReadData(f, &q, current_time + 1);

                enqueue(&q, front_item);
            }
        }


        current_time++;
    }
}

/*
 *
 */
int main(int argc, char**argv) {

	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	RoundRobin(argv[1]);

	return 0;
}
