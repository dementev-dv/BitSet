#ifndef BITARRAY_H

#define BITARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

enum SIZES {
	DEFAULT_CAPACITY = 2,
	EXTRA_CAPACITY = 2,
	ELEMENT_SIZE = 64
};

typedef enum BITS {
	SET = 1,
	UNSET = 0
} bit_t;

typedef struct {
	uint64_t *array;
	size_t size;
	size_t capacity;
} bitarr_t;

void *Calloc (size_t num, size_t size);
void *Malloc (size_t size);
void Construct (bitarr_t *bitarr, size_t capacity);
void Reset (bitarr_t *bitarr);
void ResizeUP (bitarr_t *bitarr, size_t extra);
void ResizeDown (bitarr_t *bitarr, size_t extra);
int GetBit (bitarr_t *bitarr, size_t pos);
int SetBit (bitarr_t *bitarr, size_t pos, bit_t bit);
int FindFirstSet (bitarr_t *bitarr);

#endif // BITARRAY_H
