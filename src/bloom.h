#ifndef BLOOM_H
#define BLOOM_H

#include<stddef.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

#define BITSET_IMPLEMENETATION
#include"bitset.h"

#define DIVISOR 128
#define KEYVALUE 0.357840 


typedef struct {
	bitset* bits;
	size_t bits_size;
}bloom_filter;

int div_hash(void* value, size_t length, bloom_filter* filter);
int multi_has(void* value, size_t length, bloom_filter* filter);
int mid_square_hash(void* value, size_t length, bloom_filter* filter);

bloom_filter* new_bloom_filter(size_t size);
void bloom_filter_add(bloom_filter* filter, void* value, size_t length);
bool bloom_filter_test(bloom_filter* filter, void* value, size_t length);
void free_bloom_filter(bloom_filter* filter);

#endif

#ifdef BLOOM_IMPLEMENTATION

int div_hash(void* value, size_t length,bloom_filter* filter)
{
	int temp = (intptr_t)value;
	temp %= DIVISOR;

	if(temp != 0)
	   temp /= filter->bits_size;

	return temp;
}
int multi_has(void* value, size_t length,bloom_filter* filter)
{
	float temp = (intptr_t)value;
	temp *= KEYVALUE;

	int temp2 = (int)temp;
	temp -= temp2;
	temp *= filter->bits_size;

	return (int)temp;
}
int mid_square_hash(void* value, size_t length, bloom_filter* filter)
{
	int temp = (intptr_t)value;
	int index = 0;
	int numbers[8];
	while (temp > 0)
	{
		numbers[index] = temp % 10;
		temp /= 10;
		index++;
	}

	int pow = 1;
	for (size_t i = index / 2 - 1; i < (index / 2 - 1) * 2; i++,pow *= 10)
	{
		temp = temp + pow * numbers[i];
	}

	return temp;
}

bloom_filter* new_bloom_filter(size_t size)
{
	bloom_filter* filter = (bloom_filter*)malloc(sizeof(bloom_filter));
	filter->bits = bitset_new(size);
	filter->bits_size = size;
}
void bloom_filter_add(bloom_filter *filter,void* value, size_t length)
{
	int index1 = multi_has(value, length, filter);
	int index2 = div_hash(value, length, filter);
	int index3 = mid_square_hash(value, length, filter);

	if (index1 < filter->bits_size)
		bitset_set(filter->bits, index1, 1);
	if (index2 < filter->bits_size)
		bitset_set(filter->bits, index2, 1);
	if (index3 < filter->bits_size)
		bitset_set(filter->bits, index2, 1);
}

bool bloom_filter_test(bloom_filter* filter, void* value, size_t length)
{
	int index1 = multi_has(value, length, filter);
	int index2 = div_hash(value, length, filter);
	int index3 = mid_square_hash(value, length, filter);

	return bitset_get(filter->bits, index1) == bitset_get(filter->bits, index2) == bitset_get(filter->bits, index3) == true;
}
void free_bloom_filter(bloom_filter* filter)
{
	bitset_free(filter->bits);
	free(filter);
}

#endif