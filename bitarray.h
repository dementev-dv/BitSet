#ifndef BITARRAY_H

#define BITARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

typedef enum ERRORS {
	ERROR = 1 << 5,
	VSE_OK = 0 | ERROR,
	INVALID_POS = -1 | ERROR,
	INVALID_SIZE = -2 | ERROR,
	ALLOC_ERR = -3 | ERROR,
	INVALID_ARRAY = -4 | ERROR,
	REALLOC_ERROR = -5 | ERROR,
	INVALID_CAPACITY = -6 | ERROR,	// extra for resize is considered here too
	INVALID_VAL = -7 | ERROR, // only 2 values are available: SET (1) and UNSET (0)
	INVALID_BITARR = -8 | ERROR,
	UNKNOWN_ERROR = -9 | ERROR,
	INVALID_CONTAINER = -10 | ERROR,
	INVALID_NUM = -11 | ERROR
} error_t;

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
	size_t capacity;
} bitarr_t;

void *Calloc (size_t num, size_t size);
void *Malloc (size_t size);
void *Realloc (void *ptr, size_t size);

bitarr_t *Construct (size_t capacity);
error_t Destruct (bitarr_t *bitarr);
error_t All (bitarr_t *bitarr);
error_t Any (bitarr_t *bitarr);
error_t None (bitarr_t *bitarr);
error_t Reset (bitarr_t *bitarr);
error_t Set (bitarr_t *bitarr);
error_t SetVal (bitarr_t *bitarr, bit_t bit);
error_t Flip (bitarr_t *bitarr);
error_t ResizeUP (bitarr_t *bitarr, size_t extra);
error_t ResizeDown (bitarr_t *bitarr, size_t extra);
int GetBit (bitarr_t *bitarr, size_t pos);
error_t SetBit (bitarr_t *bitarr, size_t pos);
error_t UnsetBit (bitarr_t *bitarr, size_t pos);
error_t SetBitVal (bitarr_t *bitarr, size_t pos, bit_t bit);
int FindLastSet (bitarr_t *bitarr);
int FindFirstSet (bitarr_t *bitarr);
int FindSetPos (bitarr_t *bitarr, int num);
int Count (bitarr_t *bitarr);
error_t Check (bitarr_t *bitarr);

void Dump (bitarr_t *bitarr, const char *pathname);
char *TimeNow ();

#endif // BITARRAY_H
