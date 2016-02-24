/***********************************************************************
 * Implements both an iterative and recursive quicksort and compares
 * their performance.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_ARGS 2 /* <number_of_elements_to_sort>, <number_of_times_to_sort> */
#define TEST_LEN 10 /* Length of sanity test arrays */

/* swap: interchange v[i] and v[j]
 * Adapted from Kernighan & Pik "Practice of Programming".
 */
void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* r_qsort: sort v[0]..v[n-1] into increasing order recursively
 * Adapted from Kernighan & Pike "Practice of Programming".
 */
void r_qsort(int v[], int n)
{
    int i, last;

    if (n <= 1) /* nothing to do */
        return;

    swap(v, 0, rand() % n);
    last = 0;
    for (i = 1; i < n; ++i)
    {
        if (v[i] < v[0]) {
            swap(v, ++last, i);
        }
    }
    swap(v, 0, last);
    r_qsort(v, last);
    r_qsort(v+last+1, n-last-1);
}

/* i_qsort: sort v[0]..v[n-1] into increasing order iteratively */
void i_qsort(int v[], int n)
{
    if (n <= 1)
        return; /* nothing to sort */

    int i, last, top, start, end;
    int stack[n];

    top = -1;
    stack[++top] = 0;
    stack[++top] = n;
    while (top > 0)
    {
        end = stack[top--];
        start = stack[top--];

        if ((end - start) <= 1) {
            continue; /* nothing to sort in this iteration */
        }

        /* move a random element in this subarray to the front to be the pivot */
        swap(v, start, start + (rand() % (end-start)));
        last = start;
        for (i = start+1; i < end; ++i)
        {
            if (v[i] < v[start]) {
                swap(v, ++last, i);
            }
        }
        swap(v, start, last);

        /* Push the two new subarrays onto the stack */
        if (last-1 > start) {
            stack[++top] = start;
            stack[++top] = last-1;
        }
        if (last+1 < end) {
            stack[++top] = last+1;
            stack[++top] = end;
        }
    }
}

void print_array(int arr[], int n)
{
    int i;
    printf("%d", arr[0]);
    for (i = 1; i < n; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
}

void usage(char *prog_name)
{
    printf("Usage:\n\t%s <number_of_elements_to_sort> <number_of_attempts_to_sort>\n",
            prog_name);
}

int main(int argc, char **argv)
{
    if (argc < NUM_ARGS+1) {
        usage(argv[0]);
        return 1;
    }

    int num_elements = atoi(argv[1]);
    int num_attempts = atoi(argv[2]);
    int i, j;
    clock_t begin, end;
    double i_total_time, r_total_time;
    double i_avg_time, r_avg_time;

    printf("Preparing to start testing.\n");
    printf("Number of tests will be %d with %d elements per array.\n",
            num_attempts, num_elements);

    /* Create a test run */
    int i_array[TEST_LEN], r_array[TEST_LEN];
    for (i = 0; i < TEST_LEN; ++i)
    {
        i_array[i] = r_array[i] = rand() % TEST_LEN;
    }
    printf("Doing test sort...\n\tTest Array is:  ");
    print_array(i_array, TEST_LEN);
    i_qsort(i_array, TEST_LEN);
    printf("\tIterative Sort: ");
    print_array(i_array, TEST_LEN);
    r_qsort(r_array, TEST_LEN);
    printf("\tRecursive Sort: ");
    print_array(r_array, TEST_LEN);

    for (i = 0; i < num_attempts; ++i)
    {
        // Generate two arrays of the same elements
        int i_array[num_elements], r_array[num_elements];
        for (j = 0; j < num_elements; ++j)
        {
            i_array[i] = r_array[i] = rand() % num_elements;
        }

        /* Run the test on i_qsort */
        begin = clock();
        i_qsort(i_array, num_elements);
        end = clock();
        i_total_time = ((double)end - (double)begin) / CLOCKS_PER_SEC;

        /* Run the test on r_qsort */
        begin = clock();
        r_qsort(r_array, num_elements);
        end = clock();
        r_total_time += ((double)end - (double)begin) / CLOCKS_PER_SEC;
    }

    i_avg_time = i_total_time / num_attempts;
    r_avg_time = r_total_time / num_attempts;
    
    printf("Finished testing.\n");
    printf("Iterative quicksort stats:\n\tTotal time:   %f seconds\n\tAverage time: %f seconds\n",
            i_total_time, i_avg_time);
    printf("Recursive quicksort stats:\n\tTotal time:   %f seconds\n\tAverage time: %f seconds\n",
            r_total_time, r_avg_time);

    return 0;
}
