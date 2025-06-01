#include <stdio.h>
#include "dynamic_array.h"


#define GAP() printf("\n------------------------------\n\n")


void square(int *);
int is_odd(int);

int main(void)
{
    DynamicArray *da = da_create(16);

    printf("Filling the array with numbers 1 to 16:\n");
    for (int i = 0; i < da_capacity(da); i++)
        da_add_last(da, i + 1);

    for (int i = 0; i < da_size(da); i++)
        printf("da[%d] --> %d\n", i, da_get(da, i));
    
    printf("Capacity before exceeding: %d\n", da_capacity(da));
    
    GAP();

    printf("Adding one more element to exceed initial capacity:\n");
    da_add_last(da, 17);
    printf("New capacity after resizing: %d\n", da_capacity(da));

    GAP();

    printf("Applying square() to each element:\n");
    da_foreach(da, square);
    for (int i = 0; i < da_size(da); i++)
        printf("da[%d] --> %d\n", i, da_get(da, i));

    GAP();

    printf("Filtering elements to keep only odd numbers:\n");
    DynamicArray *odds = da_filter(da, is_odd);
    for (int i = 0; i < da_size(odds); i++)
        printf("odds[%d] --> %d\n", i, da_get(odds, i));
    
    GAP();

    printf("Sorting the array in descending order:\n");
    da_sort(da, DESCENDING);
    for (int i = 0; i < da_size(da); i++)
        printf("da[%d] --> %d\n", i, da_get(da, i));

    return 0;
}

void square(int *a)
{
    *a *= *a;
}

int is_odd(int a)
{
    return a % 2 == 1;
}
