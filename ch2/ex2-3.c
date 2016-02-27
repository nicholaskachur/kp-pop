/***********************************************************************
 * Tests the C Standard Library implementation of quicksort (`qsort`)
 * on different sets of integer input to determine which has the worst
 * performance.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NUM_ARGS 2 /* <number_of_elements_to_sort>, <number_of_times_to_sort> */
#define TEST_LEN 10 /* Length of sanity test arrays */

/* icmp: compares two void pointers as integers, returns -1 for p1 < p2,
 * 1 for p1 > p2, 0 for p1 == p2
 */
int icmp(const void *p1, const void *p2)
{
    int i1 = *((int*)p1);
    int i2 = *((int*)p2);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

/* usage: prints out usage information */
void usage(char *prog_name)
{
    printf("Usage:\n\t%s <number_of_elements_to_sort> <number_of_attempts_to_sort>\n",
            prog_name);
}

/* print_array: a utility function to print out arrays of ints */
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
    int random_test_array[TEST_LEN], sorted_test_array[TEST_LEN],
        reverse_test_array[TEST_LEN], homogeneous_test_array[TEST_LEN];
    int random_array[num_elements], sorted_array[num_elements],
        reverse_array[num_elements], homogeneous_array[num_elements];
    double random_total_time, sorted_total_time, reverse_total_time,
           homogeneous_total_time;
    double random_avg_time, sorted_avg_time, reverse_avg_time,
           homogeneous_avg_time;

    printf("Beginning sanity test:\n");

    srand(clock());
    for (i = 0; i < TEST_LEN; ++i)
    {
        random_test_array[i] = rand() % TEST_LEN;
        sorted_test_array[i] = i;
        reverse_test_array[i] = TEST_LEN - i;
        homogeneous_test_array[i] = 1;
    }

    printf("\tRandom array:      ");
    print_array(random_test_array, TEST_LEN);
    qsort(random_test_array, TEST_LEN, sizeof(int), icmp);
    printf("\tSorted:            ");
    print_array(random_test_array, TEST_LEN);

    printf("\tSorted array:      ");
    print_array(sorted_test_array, TEST_LEN);
    qsort(sorted_test_array, TEST_LEN, sizeof(int), icmp);
    printf("\tSorted:            ");
    print_array(sorted_test_array, TEST_LEN);

    printf("\tReverse array:     ");
    print_array(reverse_test_array, TEST_LEN);
    qsort(reverse_test_array, TEST_LEN, sizeof(int), icmp);
    printf("\tSorted:            ");
    print_array(reverse_test_array, TEST_LEN);

    printf("\tHomogeneous array: ");
    print_array(homogeneous_test_array, TEST_LEN);
    qsort(homogeneous_test_array, TEST_LEN, sizeof(int), icmp);
    printf("\tSorted:            ");
    print_array(homogeneous_test_array, TEST_LEN);

    printf("Beginning performance test (%d runs on %d element arrays)...\n",
            num_attempts, num_elements);

    for (i = 0; i < num_attempts; ++i)
    {
        srand(clock());
        for (j = 0; j < num_elements; ++j)
        {
            random_array[j] = rand() % num_elements;
            sorted_array[j] = j;
            reverse_array[j] = num_elements - j;
            homogeneous_array[j] = 1;
        }

        begin = clock();
        qsort(random_array, num_elements, sizeof(int), icmp);
        end = clock();
        random_total_time += ((double)end - (double)begin) / CLOCKS_PER_SEC;

        begin = clock();
        qsort(sorted_array, num_elements, sizeof(int), icmp);
        end = clock();
        sorted_total_time += ((double)end - (double)begin) / CLOCKS_PER_SEC;

        begin = clock();
        qsort(reverse_array, num_elements, sizeof(int), icmp);
        end = clock();
        reverse_total_time += ((double)end - (double)begin) / CLOCKS_PER_SEC;

        begin = clock();
        qsort(homogeneous_array, num_elements, sizeof(int), icmp);
        end = clock();
        homogeneous_total_time += ((double)end - (double)begin) / CLOCKS_PER_SEC;

    }

    random_avg_time = random_total_time / num_attempts;
    sorted_avg_time = sorted_total_time / num_attempts;
    reverse_avg_time = reverse_total_time / num_attempts;
    homogeneous_avg_time = homogeneous_total_time / num_attempts;

    printf("Testing finished, statistics (in seconds):\n");
    printf("\tRandom input total time:        %f\n", random_total_time);
    printf("\tRandom input average time:      %f\n", random_avg_time);
    printf("\tSorted input total time:        %f\n", sorted_total_time);
    printf("\tSorted input average time:      %f\n", sorted_avg_time);
    printf("\tReverse input total time:       %f\n", reverse_total_time);
    printf("\tReverse input average time:     %f\n", reverse_avg_time);
    printf("\tHomogeneous input total time:   %f\n", homogeneous_total_time);
    printf("\tHomogeneous input average time: %f\n", homogeneous_avg_time);

    return 0;
}
