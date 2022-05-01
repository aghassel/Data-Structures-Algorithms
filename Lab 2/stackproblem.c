#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint, *puint;
typedef enum {
    false = 0, true
} bool, *pbool;

// Descriptor for stack.
struct _stack {
    uint magic;            // check destroy routine for reason
    int stack_size;        // Size of array holding stack
    char tos;            // Top of stack index [Size-1..0]
    char *stack_data;    // pointer to array holding stack data
};
typedef struct _stack Stack, *pStack;

#define    MAGIC    ((unsigned int) 0xDEADBEEF)

pStack new_stack(int size)
// Create instance of stack. Caller specifies stack capacity. Returns
// pointer to stack descriptor if successful; returns NULL if stack
// instance could not be created.
{
    pStack pstk = NULL;
    char *pint;

    // do a little parameter checking
    // first try to get enough memory for stack data
    pint = (char *) malloc(size * sizeof(char));
    // make sure we got some memory
    if (pint == NULL) return NULL;
    // second, get memory for stack descriptor
    pstk = (pStack) malloc(sizeof(struct _stack));
    if (pstk == NULL) {
        // didn't get that memory - give up the memory we did get
        free(pint);
        return NULL;
    }
    // Set up the descriptor
    pstk->stack_data = pint;        // point to where actual stack data goes
    pstk->stack_size = size;        // capacity of the stack
    pstk->tos = size;                // index 1 beyond end - see push()
    // for explanation
    pstk->magic = MAGIC;
    return pstk;
}//new_stack()


void destroy_stack(pStack *pstk)
// Get rid of a stack instance. Let tidy programmers clean up after
// themselves. Note that this routine takes a pointer to a stack
// descriptor pointer, so we can get rid of any reference to the stack.
{
    pStack ps;
    // see if caller is confused
    if (pstk == NULL || (ps = *pstk) == NULL) return;
    // make sure caller is passing us a valid descriptor
    if (ps->magic != MAGIC) return;
    if (ps->stack_data != NULL) free(ps->stack_data);
    free(ps);                // get rid of descriptor
    *pstk = (pStack) NULL;    // get rid of its address as well
}// destroy_stack()


bool is_empty(pStack pstk)
// Determine if stack is currently empty
{
    return pstk->tos == pstk->stack_size;
}//isempty()


bool is_full(pStack pstk)
// Determine if stack is full
{
    return pstk->tos == 0;
}//isfull()


bool push(pStack pstk, char value)
// push value onto stack indicated by pstk.
{
    // Check for errors - bad pointer, invalid pointer
    if (pstk == NULL || pstk->magic != MAGIC) return false;
    // Check if room on stack
    if (is_full(pstk)) return false;
    pstk->tos = pstk->tos - 1;
   // printf("Push %c onto stack at location %d\n", value, pstk->tos);
    pstk->stack_data[pstk->tos] = value;
    return true;
}//push()


bool pop(pStack pstk, char *pn)
// Pop value from stack, storing value in location pn.
{
    // Check for errors - bad pointer, invalid pointer
    if (pstk == NULL || pstk->magic != MAGIC) return false;
    // Check if anything to pop stack
    if (is_empty(pstk)) return false;
    *pn = pstk->stack_data[pstk->tos];
    pstk->tos++;
    return true;
}//pop


void reverse_print(pStack pstk)
// Routine - for debugging purposes - to print out contents of
// stack instance.
{
    // Check for errors - bad pointer, invalid pointer
    if (pstk == NULL || pstk->magic != MAGIC) return;
    // Check if anything to pop stack
    if (is_empty(pstk)) {
        printf("NO CHARACTERS INPUTTED\n");
    } else {
        int i, j;
        printf("Your characters in reverse order are:");
        for (i = pstk->tos, j = 0; i < pstk->stack_size; i++, j++) {
            printf("%c", pstk->stack_data[i]);
        }//endfor
        printf("\n");
    }
}//print_stack()

int main(void) {
    pStack ps1;
    char c = '\0';

    ps1 = new_stack(80);
    printf("Enter up to 80 characters, then click 'Enter' key:\n");
    while (c != '\n') { //checks that they haven't clicked enter
        scanf("%c", &c); //scans for each character
        push(ps1, c); //push characters onto stack called ps1
    }
    reverse_print(ps1); //stacks always print in reverse order

    return 0;
}//main()
