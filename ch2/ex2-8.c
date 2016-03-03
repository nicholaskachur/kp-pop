/***********************************************************************
 * Implements a simple list type and both iterative and recursive
 * reverse functions which it demonstrates in the main function.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
    Nameval *next; /* in list */
};

/* newitem: create new item from name and value
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
Nameval *newitem(char *name, int value)
{
    Nameval *newp;

    newp = (Nameval *) malloc(sizeof(Nameval));
    if (newp == NULL) {
        printf("Failed to allocate newitem (%s, %d)\n", name, value);
        exit(EXIT_FAILURE);
    }
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}

/* addfront: add newp to the front of listp
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
Nameval *addfront(Nameval *listp, Nameval *newp)
{
    newp->next = listp;
    return newp;
}

/* freeall: free all elements of listp
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
void freeall(Nameval *listp)
{
    Nameval *next;

    for ( ; listp != NULL; listp = next)
    {
        next = listp->next;
        /* assumes name is freed elsewhere */
        free(listp);
    }
}

/* print_list: pretty print out listp */
void print_list(Nameval *listp)
{
    if (listp == NULL)
        return;

    printf("(%s, %d)", listp->name, listp->value);
    for (listp = listp->next; listp != NULL; listp = listp->next)
    {
        printf(", (%s, %d)", listp->name, listp->value);
    }
}

/* ireverse: iteratively reverse a list in place, returns the new head pointer */
Nameval *ireverse(Nameval *listp)
{
    Nameval *nextp;
    Nameval *prevp = NULL;

    for ( ; listp != NULL; listp = nextp)
    {
        nextp = listp->next;
        listp->next = prevp;
        prevp = listp;

    }
    return prevp;
}

/* rreverse: recursively reverse a list in place, returns the new head pointer
 * Adapted from: http://stackoverflow.com/a/354937
 */
Nameval *rreverse(Nameval *listp)
{
    if (listp == NULL) /* trivial case, list is empty */
        return listp;
    if (listp->next == NULL) { /* base case, we've reached the end of the list */
        return listp;
    }
    
    Nameval *nextp = listp->next;
    listp->next = NULL;
    Nameval *remainderp = rreverse(nextp);
    nextp->next = listp;

    return remainderp;
}

int main(int argc, char **argv)
{
    Nameval *nvlist, *n1, *n2, *n3, *n4, *n5;

    char name1[] = "Nicholas";
    char name2[] = "Harlan";
    char name3[] = "Rob";
    char name4[] = "Dario";
    char name5[] = "Brian";

    n1 = newitem(name1, 0);
    n2 = newitem(name2, 1);
    n3 = newitem(name3, 2);
    n4 = newitem(name4, 3);
    n5 = newitem(name5, 4);

    nvlist = addfront(nvlist, n1);
    nvlist = addfront(nvlist, n2);
    nvlist = addfront(nvlist, n3);
    nvlist = addfront(nvlist, n4);
    nvlist = addfront(nvlist, n5);

    printf("nvlist initial state:\n\t");
    print_list(nvlist);
    printf("\n");

    nvlist = ireverse(nvlist);
    printf("nvlist after iterative reverse:\n\t");
    print_list(nvlist);
    printf("\n");

    nvlist = rreverse(nvlist);
    printf("nvlist after recursive reverse:\n\t");
    print_list(nvlist);
    printf("\n");

    freeall(nvlist);

    return 0;
}
