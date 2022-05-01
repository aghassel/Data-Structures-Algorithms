#include <stdio.h>
#include <stdlib.h>

#define bool        unsigned char
#define false       (unsigned char) 0
#define true        (unsigned char) 1
#define QUEUE_SIZE  400

// Queue is linked list of items.
struct item {
    struct item *next;
    int         value;
};

typedef struct item Item, *pItem;

// Queue implementation
struct queue {
    Item    *front;             //Pointer to front node
    Item    *end;               // Pointer to end node
    int     count;              // Number of items in queue
};//_queue

typedef struct queue Queue, *pQueue;

pItem new_node(int n) {
    // Create node to hold value being added to queue
    pItem pnew = (Item *) malloc(sizeof(struct item));
    if (pnew != NULL) {
        pnew->value = n;
        pnew->next = NULL;
        return pnew;
    } else return NULL;
}//new_node

//new queue implementation
pQueue new_queue(int size) {
    pQueue pQ = NULL;
    int *pint;

    pint = (int *) malloc(size * sizeof(int));

    if (pint == NULL) return NULL;
    pQ = (pQueue) malloc(sizeof(struct queue)); //get memory for queue pointer
    if (pQ == NULL) {
        // didn't get that memory - give up the memory we did get
        free(pint);
        return NULL;
    }
    pQ->front = pQ->end = NULL; //queue is empty, so front and end point to nothing
    pQ->count = 0; //set number of items in queue to zero

    return pQ;
}//new_queue

bool enqueue(pQueue pQ, int n)
// Add integer n to end of queue
{
    //int result;
    Item *pnew = new_node(n);
    // Create node to hold value being added to queue
    bool result = false;
    // Make current last node point to new node
    if (pnew != NULL) {
        if (pQ->end != NULL) {
            pQ->end->next = pnew;
        }
        // and update queue's end pointer
        pQ->end = pnew;
        // If queue was empty, new node is also new front node
        if (pQ->front == NULL) pQ->front = pnew;
        pQ->count++;
        result = true;
    }
    return result;
}//enqueue()

bool dequeue(pQueue pQ)
// Remove first value from front of queue
{
    int *n;
    bool result = false;
    // Check if there is anything to remove
    if (pQ->count > 0) {
        // There is data to remove
        Item *ptmp = pQ->front;             // pointer to first element
        *n = pQ->front->value;              // give value to caller
        pQ->front = pQ->front->next;        // move front pointer to next item
        pQ->count--;                        // reduce queue count
        free(ptmp);                        // give back memory
        // Did we just remove last item from queue?  If so, must adjust
        // end pointer
        if (pQ->front == NULL) pQ->end = NULL;
        result = true;
    }
    return result;
}//dequeue()

void qprint(pQueue pQ)
// Print all contents of array - primarily used for debugging purposes
{
    pItem pv;
    int k = 0;        //serve as a line counter
    //implementation
    pv = pQ->front; //start the node from the beginning of the queue
    while (pv != NULL) {
        printf("%5d ", pv->value);
        pv = pv->next;
        k++; //update line counter
        if ((k % 12) == 0) putchar('\n'); //after every 12 integers, start a new line
    }
    putchar('\n');
}//qprint()


int main(int argc, char *argv[]) {
    //make four queues
    pQueue QueueOne = new_queue(QUEUE_SIZE);
    pQueue QueueTwo = new_queue(QUEUE_SIZE);
    pQueue QueueThree = new_queue(QUEUE_SIZE);
    pQueue QueueFour = new_queue(QUEUE_SIZE);

    printf("Enter up to 400 integers seperated by spaces, then input a negative integer to end list:\n");

    int check = 0; //checks the sign of the integers
    int counter = 0; //counts number of integers

    do {
        scanf("%d", &check);
        //if input is negative, stop adding new numbers
        if (check < 0) {
            break;
        }

        if (check % 4 == 0) {
            enqueue(QueueOne, check);
        } else if (check % 4 == 1) {
            enqueue(QueueTwo, check);
        } else if (check % 4 == 2) {
            enqueue(QueueThree, check);
        } else {
            enqueue(QueueFour, check);
        }
    } while ((check > 0) && (counter < QUEUE_SIZE));

    putchar('\n');

    printf("Queue 1:\n");
    qprint(QueueOne);
    printf("Queue 2:\n");
    qprint(QueueTwo);
    printf("Queue 3:\n");
    qprint(QueueThree);
    printf("Queue 4:\n");
    qprint(QueueFour);

    return 0;
}//main()
