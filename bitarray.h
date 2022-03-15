#pragma once

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

enum ERRORS {
	INVALID_POS = -1
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

void Construct (bitarr_t *bitarr, size_t capacity);
void Reset (bitarr_t *bitarr);
void ResizeUP (bitarr_t *bitarr, size_t extra);
void ResizeDown (bitarr_t *bitarr, size_t extra);
int GetBit (bitarr_t *bitarr, size_t pos);
int SetBit (bitarr_t *bitarr, size_t pos, bit_t bit);
int FindFirstSet (bitarr_t *bitarr);
void Dump (bitarr_t *bitarr, const char *pathname);
char *TimeNow ();
