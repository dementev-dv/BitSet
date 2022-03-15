#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#define handle_error(CMD) {	\
	perror (CMD);			\
	exit (EXIT_FAILURE);	

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

int main () {

	bitarr_t bitarr;
	Construct (&bitarr, 128);
	SetBit (&bitarr, 63, SET);
	SetBit (&bitarr, 64, SET);
	SetBit (&bitarr, 65, SET);
	SetBit (&bitarr, 66, SET);
	SetBit (&bitarr, 67, SET);
	SetBit (&bitarr, 68, SET);
	SetBit (&bitarr, 69, SET);
	SetBit (&bitarr, 70, SET);
	SetBit (&bitarr, 71, SET);
	SetBit (&bitarr, 72, SET);
	SetBit (&bitarr, 127, SET);
	SetBit (&bitarr, 126, SET);
	SetBit (&bitarr, 125, SET);
	SetBit (&bitarr, 124, SET);
	SetBit (&bitarr, 123, SET);
	SetBit (&bitarr, 122, SET);
	SetBit (&bitarr, 121, SET);
	SetBit (&bitarr, 120, SET);
	SetBit (&bitarr, 119, SET);


	int bit = 0;
	for (size_t i = 0; i < 128; i++) {
		bit = GetBit (&bitarr, i);
		printf ("bit[%ld] = %d\n", i, bit);
	}

	Dump (&bitarr, "dump.txt");
	Reset (&bitarr);

	exit (EXIT_SUCCESS);
}

void Construct (bitarr_t *bitarr, size_t capacity) {
	bitarr->array = (uint64_t *) calloc (DEFAULT_CAPACITY, sizeof (uint64_t));
	bitarr->capacity = capacity;
	bitarr->size = 0;
	return;
}

void Reset (bitarr_t *bitarr) {
	for (ssize_t i = 0; i < bitarr->capacity / ELEMENT_SIZE; i++) {
		bitarr->array[i] = 0;
	}
	bitarr->size = 0;
	return;
}

void ResizeUP (bitarr_t *bitarr, size_t extra) {
	bitarr->array = (uint64_t *) realloc (bitarr->array, (bitarr->capacity + extra) / ELEMENT_SIZE + 1);
	bitarr->capacity += (extra / ELEMENT_SIZE + 1) * ELEMENT_SIZE;
	return;
}

void ResizeDown (bitarr_t *bitarr, size_t extra) {
	bitarr->array = (uint64_t *) realloc (bitarr->array, (bitarr->capacity - extra) / ELEMENT_SIZE + 1);
	bitarr->capacity -= extra;
	return;
}

int GetBit (bitarr_t *bitarr, size_t pos) {
	if (pos >= bitarr->capacity)
		return INVALID_POS;

	uint64_t mask = 1;
	mask = mask << pos % ELEMENT_SIZE;
	if (bitarr->array[pos / ELEMENT_SIZE] & mask)
		return 1;
	return 0;
}

int SetBit (bitarr_t *bitarr, size_t pos, bit_t bit) {
	if (pos >= bitarr->capacity) {
		ResizeUP (bitarr, pos - bitarr->capacity);
	}

	uint64_t *point = bitarr->array + pos / ELEMENT_SIZE; 
	uint64_t mask = 1;
	mask = mask << (pos % ELEMENT_SIZE);

	if (bit == SET) {
		*point = *point | mask;
		return 0;
	}
	if (bit == UNSET) {
		mask = ~mask;
		*point = *point & mask;
		return 0;
	}
	return -1;
}

int FindFirstSet (bitarr_t *bitarr) {
	size_t result = 0;
	size_t i = 0;
	for (i = 0; i < bitarr->capacity; i++) {
		if (bitarr->array[i])
			break;
		result += ELEMENT_SIZE;
	}

	uint64_t current = bitarr->array[i];
	
	for (int offset = 0; offset < ELEMENT_SIZE; i++) {
		if (current & (1 << offset))
			break;
		result++;
	}
	return result;
}

void Dump (bitarr_t *bitarr, const char *pathname) {
	FILE *dumpfile = fopen (pathname, "w+");
	fprintf (dumpfile, "BitArray %s\n", TimeNow ());
	uint64_t mask = 1;
	for (size_t i = 0; i < bitarr->capacity / ELEMENT_SIZE; i++) {
		fprintf (dumpfile, "[%ld] =", i);
		for (size_t offset = 0; offset < ELEMENT_SIZE; offset++) {
			if (!(offset % 4)) fprintf (dumpfile, " ");
			if (bitarr->array[i] & (mask << offset)) fprintf (dumpfile, "1");
			else fprintf (dumpfile, "0");
		}
		fprintf (dumpfile, "\n");
	}
	return;
}

char *TimeNow () {
	time_t t = time (NULL);
	return asctime (localtime (&t));
}