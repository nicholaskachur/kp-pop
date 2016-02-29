/***********************************************************************
 * Implements a dynamic array of Nameval structs (Name & Value), and
 * provides functions for adding and removing elements from that
 * array.
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
};

struct NVtab {
    int nval;
    int max;
    Nameval *nameval;
} nvtab;

enum { NVINIT = 1, NVGROW = 2 };

/* addname: add new name and value to nvtab
 * Adapted from Kernighan & Pike "Practice of Programming and updated to
 * search for the first empty (name != NULL) place for the newname
 */
int addname(Nameval newname)
{
    Nameval *nvp;

    if (nvtab.nameval == NULL) { /* first time */
        nvtab.nameval = (Nameval *) malloc(NVINIT * sizeof(Nameval));
        if (nvtab.nameval == NULL)
            return -1;
        nvtab.max = NVINIT;
        nvtab.nval = 0;
    } else if (nvtab.nval >= nvtab.max) { /* grow */
        nvp = (Nameval *) realloc(nvtab.nameval,
                (NVGROW*nvtab.max) * sizeof(Nameval));
        if (nvp == NULL)
            return -1;
        nvtab.max *= NVGROW;
        nvtab.nameval = nvp;
    }

    int i;
    for (i = 0; i < nvtab.max; ++i)
    {
        if (nvtab.nameval[i].name == NULL) {
            nvtab.nameval[i] = newname;
            nvtab.nval++;
            printf("Added a name in an unused space: (%s, %d)\n",
                    newname.name, newname.value);
            return i;
        }
    }
    /* no empty space found, add at the end */
    nvtab.nameval[nvtab.nval] = newname;
    printf("Added a name at the end: (%s, %d)\n", nvtab.nameval[nvtab.nval].name,
            nvtab.nameval[nvtab.nval].value);
    return nvtab.nval++;
}

/* delname: remove first matching nameval from nvtab and mark as unused
 * Adapted from Kernighan & Pike "Practice of Programming" and updated
 * to mark the deleted nameval as unused (name = NULL).
 */
int delname(char *name)
{
    int i;

    for (i = 0; i < nvtab.nval; ++i)
    {
        if (nvtab.nameval[i].name != NULL) { /* protect against strcmp(NULL, x) */
            if (strcmp(nvtab.nameval[i].name, name) == 0) {
                nvtab.nameval[i].name = NULL;
                nvtab.nval--;
                return 1;
            }
        }
    }
    return 0;
}

/* print_nvtab: utility function to print out the whole nvtab */
void print_nvtab()
{
    if (nvtab.nameval[0].name == NULL) { /* first element */
        printf("(NULL)");
    } else {
        printf("(%s, %d)", nvtab.nameval[0].name, nvtab.nameval[0].value);
    }

    int i;
    for (int i = 1; i < nvtab.nval; ++i)
    {
        if (nvtab.nameval[i].name == NULL) { /* subsequent elements */
            printf(", (NULL)");
        } else {
            printf(", (%s, %d)", nvtab.nameval[i].name, nvtab.nameval[i].value);
        }
    }
}

int main(int argc, char **argv)
{
    Nameval nv1, nv2, nv3, nv4, nv5, nv6;
    nv1.name = "Nick";
    nv1.value = 0;
    addname(nv1);
    nv2.name = "Harlan";
    nv2.value = 1;
    addname(nv2);
    nv3.name = "Dario";
    nv3.value = 2;
    addname(nv3);
    nv4.name = "Rebecca";
    nv4.value = 3;
    addname(nv4);
    nv5.name = "Misha";
    nv5.value = 4;
    addname(nv5);

    printf("nvtab initial state:\n\t");
    print_nvtab();

    delname(nv2.name);
    delname(nv2.name); /* this shouldn't do anything */
    delname(nv3.name);
    printf("\nnvtab after deleting second and third elements:\n\t");
    print_nvtab();

    nv6.name = "Rob";
    nv6.value = 9001;
    addname(nv6);
    printf("\nnvtab after adding a new element:\n\t");
    print_nvtab();
    printf("\n");

    return 0;
}
