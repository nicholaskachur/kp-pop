/***********************************************************************
 * Implements a simple list type and some common operations on it
 * which it demonstrates in the main function.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

#include <stdio.h>
#include <strcmp.h>

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

/* addend: add newp to the end of listp
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
Nameval *addend(Nameval *listp, Nameval *newp)
{
    Nameval *p;

    if (listp == NULL)
        return newp;
    for (p = listp; p->next != NULL; p = p->next)
        ;
    p->next = newp;
    return listp;
}

/* copy: copy the list, allocating new memory for it, returns the head of the
 * new list
 */
Nameval *listcopy(Nameval *listp)
{

}

/* merge: add list2 at the end of list1 returning the head of the merged list */
Nameval *merge(Nameval *list1, Nameval *list2)
{

}

/* insertbefore: insert newp into listp before matchp, returns the head of the
 * list
 */
Nameval *insertbefore(Nameval *listp, Nameval *matchp, Nameval *newp)
{

}

