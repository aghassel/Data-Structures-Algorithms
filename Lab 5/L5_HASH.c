//LAB5_HASH.C - Lab 05 - Ghassel, Abdellah, Thakore, Akshay

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DLL.h"


// Definition of data structure for chained hashtable
typedef struct HashTable {
    pLinkedList *a;            // point to array of pointers to linked lists
    int size;        // size of the array (not the table)
    int population;    // actual number of strings in table
    int collisions;    // count collisions detected on insert
} HashTable, *pHashTable;


pHashTable initHashTable(int s) {
    pHashTable pht = (pHashTable) malloc(sizeof(HashTable));
    if (pht != NULL) {
        // Created space for hashtable descriptor
        int i;
        pht->size = s;        // size is the size of the linked-list array
        pht->collisions = 0;
        pht->population = 0;
        // Now set up the harray of linked list pointers for the chains
        pht->a = malloc(sizeof(LinkedList) * s);
        if (pht->a != NULL) {
            // Initialize memory for all the linked lists
            for (i = 0; i < s; i++) pht->a[i] = init();
        } else {
            // Didn't get needed memory - give up what we got
            free(pht);
            pht = NULL;
        }
    }
    return pht;
}//initHashTable()


unsigned long int hashcode(char *x)
// This function computes hash code for given string.  Note that hash code
// is unbounded - it needs to be reduced modulo size of hash table (array)
// used to store data. (You will see another function hash() below that
// completes the index calculation.)
{
    unsigned long int sum = 0;
    int i = 0;
    int l = strlen(x);
    while (x[i] != '\0') {
        sum += (x[i] * (long) pow(31, l - 1 - i));
        i++;
    }
    return sum;
}//hashcode()


int hash(char *x, int size)
// Index calculation. Function hashcode() computes general hash for string;
// this function turns hash into valid index, given size of array.
{
    return hashcode(x) % size;
}//hash()


void insert(HashTable *ht, char *x)
// Insert new string into hashtable
{
    int key = hash(x, ht->size);
    printf("    Word: %s hash index: %d\n", x, key);
    // Is the slot empty?
    if (!isEmptyList(ht->a[key])) ht->collisions++;
    addFront(ht->a[key], x);
    ht->population++;
}//insert()


int findInTable(HashTable *ht, char *x) {
    int key = hash(x, ht->size);
    return (find(ht->a[key], x));
}

//calculate loadFactor using population and size
float loadFactor(HashTable *ht) {
    return (float) ht->population / ht->size;
}


void printTable(HashTable *ht) {
    int i;
    printf("----------\n");
    for (i = 0; i < ht->size; i++) {
        printf("%d --> ", i);
        printList(ht->a[i]);
    }
    printf("# of Collisions=%d # entries=%d\n", ht->collisions, ht->population);
    printf("Load Factor %%=%.2f\n----------", loadFactor(ht));
}

#define    TABSIZ    42                // define size of table

float ACL(HashTable *ht) {

    float x;
    //assign variables to the size of the hashtable and sum to 0
    int nChains = ht->size;
    int sum = 0;

    for (int i = 0; i < (ht->size); i++) {
        //remove one from chain
        if (ht->a[i]->size == 0) nChains--;
        else sum += ht->a[i]->size;
    }
    return ((float) sum / nChains);
}

int main() {
    int i = 0;
    HashTable *h = initHashTable(TABSIZ + 1);

// Two versions of code to build data. The first generates random strings, the
// second (used in the lab) reads words from a file.
#if 0
    // Generate a set of random strings (given the way this works, everyone
    // gets the same set of random strings!) insert each into the hash table
    // and then print the table.
    for(i=0;i<TABSIZ;i++){
        int x = rand()%5+1;
        char *p = malloc(sizeof(char)*x);
        int j=0;
        for(j=0;j<x;j++)
            p[j] = rand()%26 + 97;
        p[j]='\0';
       insert(h,p);
    }
#else

    FILE *fp;
    char *p;
    char buff[132];
    fp = fopen("WORDLIST.TXT", "r");
    while (!feof(fp)) {
        fgets(buff, 128, fp);
        p = buff;
        while (*p) {
            if (*p <= ' ') {
                *p = '\0';
                break;
            }
            p++;
        }
        printf("Word inserted: %s\n", buff);
        insert(h, buff);
        printTable(h);
        printf("Press return key to add another number to table:");
        fflush(stdout);
        getchar();
    }
#endif
    printTable(h);
    printf("\nACL: %.2f\n", ACL(h));

    return 0;
}
