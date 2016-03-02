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
    if (newp == NULL)
        return newp; /* well, _you're_ screwed */
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
    return listp;
}

/* rreverse: recursively reverse a list in place, returns the new head pointer */
Nameval *rreverse(Nameval *listp)
{
    if (listp == NULL)
        return listp;
    
    return listp;
}

int main(int argc, char **argv)
{
    Nameval *n1, *n2, *n3, *n4, *n5;
    char *name1, *name2, *name3, *name4, *name5;

    name1 = "Nicholas";
    name2 = "Harlan";
    name3 = "Rob";
    name4 = "Dario";
    name5 = "Brian";

    n1 = newitem(name1, 0);
    n2 = newitem(name2, 1);
    n3 = newitem(name3, 2);
    n4 = newitem(name4, 3);
    n5 = newitem(name5, 4);

    Nameval *nvlist;
    nvlist = addfront(nvlist, n1);
    nvlist = addfront(nvlist, n2);
    nvlist = addfront(nvlist, n3);
    nvlist = addfront(nvlist, n4);
    nvlist = addfront(nvlist, n5);

    printf("n1 is (%s, %d)\n", n1->name, n1->value);
    printf("nvlist initial state:\n\t");
    //print_list(nvlist);
    printf("\n");

    nvlist = ireverse(nvlist);
    printf("nvlist after iterative reverse:\n\t");
    //print_list(nvlist);
    printf("\n");

    nvlist = rreverse(nvlist);
    printf("nvlist after recursive reverse:\n\t");
    //print_list(nvlist);
    printf("\n");

    freeall(nvlist);

    return 0;
}
