/***********************************************************************
 * Implements a generic list type and shows a small demonstration.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ListElement ListElement;
struct ListElement {
    void *data;
    ListElement *next;
};

/* newitem: create new item from data (cast to a void*) and 
 */
ListElement *newitem(void *data)
{
    ListElement *newp;

    newp = (ListElement *) malloc(sizeof(ListElement));
    if (newp == NULL) {
        printf("Call to newitem failed, sorry bro.\n");
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
        /* assumes data is freed elsewhere */
        free(listp);
    }
}

/* apply: execute fn for each element in listp
 * Adapted from Kernighan & Pike "Practice of Programming"
 */
void apply(ListElement *listp, void (*fn)(ListElement*, void*), void *arg)
{
    for ( ; listp != NULL; listp = listp->next)
        (*fn)(listp, arg); /* call the function */
}

/* printint: print a ListElement that has an int * as the data */
void printint(ListElement *p, void *arg)
{
    char *fmt;

    fmt = (char *)arg;
    printf(fmt, *(int *)p->data);
}

/* printstr: print a ListElement that has a char * as the data */
void printstr(ListElement *p, void *arg)
{
    char *fmt;

    fmt = (char *)arg;
    printf(fmt, (char *)p->data);
}

/* insertbefore: insert newp into listp before the item with name matchname, 
 * returns 1 if newp was inserted, -1 if it was not
 */
int insertbefore(ListElement *listp, void *matchdata, ListElement *newp,
        int (*match)(void *p1, void *p2))
{
    ListElement *prevp = NULL;
    for ( ; listp != NULL; listp = listp->next)
    {
        if ((*match)(listp->data, matchdata))
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

/* matchint: return 1 if (int *)d1 == (int *)d2, else return 0 */
int matchint(void *d1, void *d2)
{
    int i1 = *(int *)d1;
    int i2 = *(int *)d2;

    return i1 == i2;
}

/* matchstr: return 1 if strcmp((char *)d1, (char *)d2) == 0, else return 0 */
int matchstr(void *d1, void *d2)
{
    char *s1 = (char *)d1;
    char *s2 = (char *)d2;

    return strcmp(s1, s2) == 0;
}

int main(int argc, char **argv)
{
    ListElement *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8;

    int i1 = 0;
    int i2 = 1;
    int i3 = 2;
    int i4 = 3;

    char s1[] = "Nicholas";
    char s2[] = "Noah";
    char s3[] = "Lizzie";
    char s4[] = "Naomi";

    p1 = newitem((void *)&i1);
    p2 = newitem((void *)&i2);
    p3 = newitem((void *)&i3);
    p4 = newitem((void *)&i4);
    p5 = newitem((void *)s1);
    p6 = newitem((void *)s2);
    p7 = newitem((void *)s3);
    p8 = newitem((void *)s4);

    ListElement *intlist, *strlist;

    intlist = addfront(intlist, p1);
    intlist = addfront(intlist, p2);
    intlist = addfront(intlist, p3);
    intlist = addfront(intlist, p4);

    strlist = addfront(strlist, p5);
    strlist = addfront(strlist, p6);
    strlist = addfront(strlist, p7);
    strlist = addfront(strlist, p8);

    printf("intlist is:\n");
    apply(intlist, printint, "(%d)\n");

    printf("strlist is:\n");
    apply(strlist, printstr, "(%s)\n");

    freeall(intlist);
    freeall(strlist);
    
    return 0;
}
