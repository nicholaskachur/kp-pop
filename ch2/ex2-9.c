/***********************************************************************
 * Implements a generic list type, implements some sample operations
 * and demonstrates them in the main function.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListElement ListElement;
struct ListElement {
    void *data;
    ListElement *next; /* in list */
};

/* newitem: create new item from void * to its data
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
ListElement *newitem(void *data)
{
    ListElement *newp;

    newp = (ListElement *) malloc(sizeof(ListElement));
    if (newp == NULL) {
        fprintf(stderr, "Failed to malloc\n");
        exit(EXIT_FAILURE);
    }
    newp->data = data;
    newp->next = NULL;
    return newp;
}

/* addfront: add newp to the front of listp
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
ListElement *addfront(ListElement *listp, ListElement *newp)
{
    newp->next = listp;
    return newp;
}

/* freeall: free all elements of listp
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
void freeall(ListElement *listp)
{
    ListElement *next;

    for ( ; listp != NULL; listp = next)
    {
        next = listp->next;
        /* assumes name is freed elsewhere */
        free(listp);
    }
}

/* reverse: reverse a list in place, returns the new head pointer
 * Adapted from: http://stackoverflow.com/a/354937
 */
ListElement *reverse(ListElement *listp)
{
    if (listp == NULL) /* trivial case, list is empty */
        return listp;
    if (listp->next == NULL) /* base case, we've reached the end of the list */
        return listp;
    
    ListElement *nextp = listp->next;
    listp->next = NULL;
    ListElement *remainderp = reverse(nextp);
    nextp->next = listp;

    return remainderp;
}

/* print_strlist: pretty print out listp which uses strings as data */
void print_strlist(ListElement *listp)
{
    if (listp == NULL)
        return;

    printf("(%s)", (char *)listp->data);
    for (listp = listp->next; listp != NULL; listp = listp->next)
    {
        printf(", (%s)", (char *)listp->data);
    }
}

/* print_intlist: pretty print out listp which uses ints as data */
void print_intlist(ListElement *listp)
{
    if (listp == NULL)
        return;

    printf("(%d)", *(int *)listp->data);
    for (listp = listp->next; listp != NULL; listp = listp->next)
    {
        printf(", (%d)", *(int *)listp->data);
    }
}
int main(int argc, char **argv)
{
    ListElement *strlist, *intlist, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8;

    char name1[] = "Nicholas";
    char name2[] = "Namoi";
    char name3[] = "Noah";
    char name4[] = "Lizzie";

    int i1 = 0;
    int i2 = 1;
    int i3 = 2;
    int i4 = 3;

    n1 = newitem(name1);
    n2 = newitem(name2);
    n3 = newitem(name3);
    n4 = newitem(name4);

    n5 = newitem(&i1);
    n6 = newitem(&i2);
    n7 = newitem(&i3);
    n8 = newitem(&i4);

    strlist = addfront(strlist, n1);
    strlist = addfront(strlist, n2);
    strlist = addfront(strlist, n3);
    strlist = addfront(strlist, n4);

    intlist = addfront(intlist, n5);
    intlist = addfront(intlist, n6);
    intlist = addfront(intlist, n7);
    intlist = addfront(intlist, n8);

    printf("strlist & intlist initial state:\n\t");
    print_strlist(strlist);
    printf("\n\t");
    print_intlist(intlist);
    printf("\n");

    strlist = reverse(strlist);
    intlist = reverse(intlist);
    printf("reversed:\n\t");
    print_strlist(strlist);
    printf("\n\t");
    print_intlist(intlist);
    printf("\n");

    freeall(strlist);
    freeall(intlist);
}

