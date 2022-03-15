#include "bitarray.h"

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