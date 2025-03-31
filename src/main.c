#include<stdio.h>
#include<math.h>
#include"bitset.h"

int main()
{
	bitset *bit = bitset_new(32);
	bitset_set(bit, 2, 1);
	bitset_set(bit, 3, 1);
	printf("%d\n", bitset_get(bit, 2));
	printf("%d\n", bitset_get(bit, 12));
	printf("%d\n", bitset_get(bit, 30));
	printf("%d\n", bitset_get(bit,3));
	bitset_free(bit);
	return 0;
}