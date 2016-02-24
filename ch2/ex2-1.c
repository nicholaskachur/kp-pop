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
    for (i = 0; i < n; ++i)
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

    for (i = 0; i < num_attempts; ++i)
    {
        // Generate two arrays of the same elements
        int i_array[num_elements], r_array[num_elements];
        for (j = 0; j < num_elements; ++j)
        {
            i_array[i] = r_array[i] = rand() % num_elements;
        }

        /* Run the test on i_qsort */
        /*
        start = clock();
        i_qsort(i_array, num_elements);
        end = clock();
        i_tota_time = ((double)end - (double)begin) / CLOCKS_PER_SEC;
        */

        /* Run the test on r_qsort */
        begin = clock();
        r_qsort(r_array, num_elements);
        end = clock();
        r_total_time += ((double)end - (double)begin) / CLOCKS_PER_SEC;
    }

    i_avg_time = i_total_time / num_attempts;
    r_avg_time = r_total_time / num_attempts;
    
    printf("Finished testing.\n");
    printf("Recursive quicksort stats:\n\tTotal time: %f seconds\n\tAverage time: %f seconds\n",
            r_total_time, r_avg_time);

    return 0;
}
