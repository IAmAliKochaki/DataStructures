#include <stdio.h>
#include "hash_table.h"

#define GAP "\n===============================\n\n"

int main(void)
{
    ht_add(NULL, 2342); // Should error out gracefully
    
    HashTable *ht = ht_create(5);
    if (!ht)
        return 1;

    if (ht_is_empty(ht) == 1)
        printf("is empty\n");

    ht_add(ht, 2342);
    ht_add(ht, 2222342);
    ht_add(ht, 234211);
    ht_add(ht, 234216);
    ht_add(ht, 234216); // Duplicate

    ht_remove(ht, 321); // Not in table

    ht_remove(ht, 2342);

    printf("size: %zu\n", ht_size(ht));
    
    if (ht_is_empty(ht) == 0)
        printf("not empty.\n");

    ht_destroy(ht); 
    return 0;
}
