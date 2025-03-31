#ifndef BITSET_H
#define BITSET_H

#define BYTE_AS_BIT 8
#define TYPE_AS_BIT(type) (BYTE_AS_BIT * sizeof(type))

#include<stdint.h>
#include<stddef.h>
#include<stdbool.h>

typedef struct {
	uint32_t* mem;
	size_t mem_size;
}bitset;

void bitset_free(bitset* bit);
bitset* bitset_new(size_t size);
void bitset_set(bitset* bit, size_t index, bool value);
bool bitset_get(bitset* bit, size_t index);

#endif

#ifdef BITSET_IMPLEMENETATION

bitset* bitset_new(size_t size)
{
	bitset* bit = malloc(sizeof(*bit));
	int mem_size = ceil(size / TYPE_AS_BIT(uint32_t));
	bit->mem = malloc(mem_size * sizeof(uint32_t));
	bit->mem_size = size;

	return bit;
}

void bitset_set(bitset* bit, size_t index, bool value)
{
	if (index > bit->mem_size * TYPE_AS_BIT(uint32_t)) {
		fprintf(stderr, "Out of range!!!\n");
		exit(1);
	}

	size_t mem_index = index / TYPE_AS_BIT(uint32_t);
	if (value) {
		bit->mem[mem_index] |= ((uint32_t)1) << index;
	}
	else {
		bit->mem[mem_index] &= ~(1 << index);
	}
}

bool bitset_get(bitset* bit, size_t index)
{
	if (index > bit->mem_size * TYPE_AS_BIT(uint32_t)) {
		fprintf(stderr, "Out of range!!!\n");
		exit(1);
	}

	size_t mem_index = index / TYPE_AS_BIT(uint32_t);
	uint32_t temp = bit->mem[mem_index];
	return (temp >> index) & 1;
}

void bitset_free(bitset* bit)
{
	free(bit->mem);
	free(bit);
}


#endif