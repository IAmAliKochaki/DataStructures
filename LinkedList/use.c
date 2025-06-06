#include <stdio.h>
#include "linkedlist.h"

void linkedlist_iterator(linkedlist *);

int main(void)
{
	linkedlist *ll = ll_create();
	if (!ll)
	{
		printf("ll creation failed\n");
		return 0;
	}

	ll_add_last(ll, 5);
	ll_add_last(ll, 15);
	ll_add_last(ll, 25);
	ll_add_last(ll, 35);

	linkedlist_iterator(ll);
	printf("-------------------\n\n");

	ll_add_first(ll, -5);
	linkedlist_iterator(ll);
	printf("-------------------\n\n");

	ll_add(ll, 20, ll_index_of(ll, 15) + 1);
	linkedlist_iterator(ll);
	printf("-------------------\n\n");

	ll_remove(ll, ll_index_of(ll, 15));
	linkedlist_iterator(ll);

	return 0;
}

void linkedlist_iterator(linkedlist *ll)
{
	for (int i = 0; i < ll_size(ll); i++)
		printf("%d\n", ll_get(ll, i));
}
