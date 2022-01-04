//Abdellah Ghassel, Akshay Thakore - Lab04 - L4_QUICKSORT2.c

#include <stdio.h>
#include <time.h>

//initialize swap counter variables
int qswaps = 0;
int q2swaps = 0;

//Swap values at locations a and b - two pointers to integers
void qswap(int *a, int *b) {
    //create temp variable to hold first element (a)
    int temp = *a;
    //set first element to second element
    *a = *b;
    //set second element to the original first element
    *b = temp;
    //increase swap counter
    qswaps++;
}//qswap()

//Swap values at locations a and b - two pointers to integers
void q2swap(int *a, int *b) {
    //create temp variable to hold first element (a)
    int temp = *a;
    //set first element to second element
    *a = *b;
    //set second element to the original first element
    *b = temp;
    //increase swap counter
    q2swaps++;
}//q2swap()

//partition pivot, so elements to its left are less than the pivot and elements to its right are larger than the pivot
int partition(int arr[], int first, int last) {
    //initialize pivot as last element in array
    int pivot = arr[last];
    //initialize i to index before first element
    int i = (first - 1);
    //loop through array using index j starting from first element to last element
    for (int j = first; j < last; j++) {
        if (arr[j] <= pivot) {
            //if element j is than smaller than or equal to pivot, then increase index i
            //then swap elements at index i and index j
            i++;
            qswap(&arr[i], &arr[j]);
        }
    }
    //final step is to swap the pivot with the element to the right of index i
    qswap(&arr[i + 1], &arr[last]);
    //return pivot's index
    return (i + 1);
}//partition()

//partition pivot, so elements to its left are less than the pivot and elements to its right are larger than the pivot
int partition2(int arr[], int first, int last) {
    //initialize pivot as last element in array
    int pivot = arr[last];
    //initialize i to index before first element
    int i = (first - 1);
    //loop through array using index j starting from first element to last element
    for (int j = first; j < last; j++) {
        if (arr[j] <= pivot) {
            //if element j is than smaller than or equal to pivot, then increase index i
            //then swap elements at index i and index j
            i++;
            q2swap(&arr[i], &arr[j]);
        }
    }
    //final step is to swap the pivot with the element to the right of index i
    q2swap(&arr[i + 1], &arr[last]);
    //return pivot's index
    return (i + 1);
}//partition2()

void quickSort(int arr[], int first, int last) {
    //check that first index is less than right index
    if (first < last) {
        //initialize local variable pivotvar as pivot
        int pivotvar = partition(arr, first, last);
        //recursively sort element to the left of the pivot
        quickSort(arr, first, pivotvar - 1);
        //recursively sort elements to the right of the pivot
        quickSort(arr, pivotvar + 1, last);
    }
}//quickSort()

void insertionSort(int arr[], int first, int arrSize) {
    //sort through array starting from the second element (assuming first is sorted) until last element in array
    for (int i = first + 1; i <= arrSize; i++) {
        int v = arr[i]; //current element we are sorting
        int j = i;
        //while loop iterates if that j index is greater than the first index AND v is less than element to its left
        while ((j > first) && (arr[j - 1] > v)) {
            //set element at index j to element to its left
            arr[j] = arr[j - 1];
            //decrease j
            --j;
        }
        //set element at new index j to v
        arr[j] = v;
    }
}//insertionSort()

void quickSort2(int arr[], int first, int last) {
    while (first < last) {
        //check that first index is less than right index
        //if partitions are less than 32 data items in size, switch to insertionSort and stop recursive process
        if (last - first + 1 < 32) {
            insertionSort(arr, first, last);
            break;
        } else {
            int pivot = partition2(arr, first, last);
            //recursively sort elements to the left of the pivot
            quickSort2(arr, first, pivot - 1);
            //adjust first to the right of pivot
            first = pivot + 1;
            //recursively sort elements to the right of the pivot
            quickSort2(arr, pivot + 1, last);
            //adjust last to left of pivot
            last = pivot - 1;
        }
    }
}//quickSort2()

int main() {
    //create needed variables
    int num, ctr = -1, i = 0;
    FILE *fp, *rdm;

    //open random file and read it with rdm pointer
    rdm = fopen("RANDOM.txt", "r");
    //open file and write to it with fp pointer
    fp = fopen("LAB4_PART3.txt", "w");

    //determine how many numbers there are in the random file
    while (fscanf(rdm, "%d", &num) > 0) {
        ctr++;
    }
    //create an array big enough to hold all the data values
    int data[ctr];

    //point rdm to the beginning of the random file
    rewind(rdm);

    //take all the data from the random file and store it in data
    while (fscanf(rdm, "%d", &num) > 0) {
        //if file has reached -1, stop adding numbers to data
        if (num == -1) {
            break;
        }
            //add numbers to data
        else {
            data[i] = num;
            i++;
        }
    }

    //creating arrays to hold data
    int rqsort[ctr], rq2sort[ctr];

    //coping data to arrays
    for (int i = 0; i < ctr; i++) {
        rqsort[i] = data[i];
        rq2sort[i] = data[i];
    }

    //sorting rqsort with the quicksort method and timing it
    clock_t start = clock();
    quickSort(rqsort, 0, ctr - 1);
    clock_t rqtime = clock() - start;

    //sorting rq2sort with the modified quicksort method and timing it
    start = clock();
    quickSort2(rq2sort, 0, ctr - 1);
    clock_t rq2time = clock() - start;

    //printing all the data to the output file, LAB4_PART3.txt
    fprintf(fp, "Ghassel, Abdellah\tThakore, Akshay\t\tSize of Dataset: %d\n", ctr);
    fprintf(fp, "\t\t\tELAPSED TIME\t\tNumber of Swaps\n");
    fprintf(fp, "Original Quicksort\t%ld\t\t\t%d\n", rqtime, qswaps);
    fprintf(fp, "Modified Quicksort\t%ld\t\t\t%d\n", rq2time, q2swaps);

    //closing files
    fclose(fp);
    fclose(rdm);
}
