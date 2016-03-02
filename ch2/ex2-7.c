/***********************************************************************
 * Implements a simple list type and some common operations on it
 * which it demonstrates in the main function.
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

/* copy: copy the list, allocating new memory for it, returns the head of the
 * new list
 */
Nameval *copy(Nameval *listp)
{
    Nameval *newp;
    Nameval *headp;

    if (listp != NULL)
        headp = newitem(listp->name, listp->value);
    newp = headp;

    for (listp = listp->next; listp != NULL; listp = listp->next)
    {
        newp->next = newitem(listp->name, listp->value);
        newp = newp->next;
    }

    return headp;
}

/* merge: add list2 at the end of list1 returning the head of the merged list */
Nameval *merge(Nameval *list1, Nameval *list2)
{
    Nameval *headp = list1;
    Nameval *prevp = NULL;
    for ( ; list1 != NULL; list1 = list1->next)
        prevp = list1;
    if (prevp != NULL)
        prevp->next = list2;

    return headp;
}

/* split: split listp into two lists at the element with name splitname, this
 * returns the head of the new list while listp remains the same; if matchname
 * doesn't exist in listp, returns listp
 */
Nameval *split(Nameval *listp, char *splitname)
{
    Nameval *prevp = NULL;
    for ( ; listp != NULL; listp = listp->next)
    {
        if (strcmp(listp->name, splitname) == 0) {
            if (prevp != NULL)
                prevp->next = NULL;
            return listp;
        }
        prevp = listp;
    }

    return listp;
}

/* insertbefore: insert newp into listp before the item with name matchname, 
 * returns 1 if newp was inserted, -1 if it was not
 */
int insertbefore(Nameval *listp, char *matchname, Nameval *newp)
{
    Nameval *prevp = NULL;
    for ( ; listp != NULL; listp = listp->next)
    {
        if (strcmp(listp->name, matchname) == 0)
        {
            if (prevp != NULL)
                prevp->next = newp;
            newp->next = listp;
            return 1;
        }
        prevp = listp;
    }

    return -1;
}

/* insertafter: insert newp into listp after the item with name matchname,
 * returns 1 if newp was inserted, -1 if not
 */
int insertafter(Nameval *listp, char *matchname, Nameval *newp)
{
    for ( ; listp != NULL; listp = listp->next)
    {
        if (strcmp(listp->name, matchname) == 0) {
            newp->next = listp->next; /* be careful not to overwrite listp->next */
            listp->next = newp;       /* until newp has its value */
            return 1;
        }
    }

    return -1;
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

int main(int argc, char **argv)
{
    Nameval *nvlist, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8;
    char name1[] = "Nicholas";
    char name2[] = "Harlan";
    char name3[] = "Dario";
    char name4[] = "Rebecca";
    char name5[] = "Misha";
    char name6[] = "Rob";

    n1 = newitem(name1, 0);
    n2 = newitem(name2, 1);
    n3 = newitem(name3, 2);
    n4 = newitem(name4, 3);
    n5 = newitem(name5, 4);
    n6 = newitem(name6, 5);

    nvlist = addfront(nvlist, n1);
    nvlist = addfront(nvlist, n2);
    nvlist = addfront(nvlist, n3);
    nvlist = addfront(nvlist, n4);

    printf("nvlist initial state:\n\t");
    print_list(nvlist);
    printf("\n");

    insertafter(nvlist, name3, n5);
    printf("nvlist after adding 'Misha' after 'Dario':\n\t");
    print_list(nvlist);
    printf("\n");

    insertbefore(nvlist, name2, n6);
    printf("nvlist after adding 'Rob' before 'Harlan':\n\t");
    print_list(nvlist);
    printf("\n");

    Nameval *splitlist = split(nvlist, name6);
    printf("nvlist and splitlist after splitting on 'Rob':\n\t");
    print_list(nvlist);
    printf("\n\t");
    print_list(splitlist);
    printf("\n");

    nvlist = merge(splitlist, nvlist);
    printf("nvlist after merging splitlist with nvlist:\n\t");
    print_list(nvlist);
    printf("\n");

    Nameval *nvcopy = copy(nvlist);
    printf("nvcopy is:\n\t");
    print_list(nvcopy);
    printf("\n");

    freeall(nvlist);
    freeall(nvcopy);
}

