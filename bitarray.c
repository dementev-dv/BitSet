#include "bitarray.h"

enum ERRORS {
	INVALID_POS = -1,
	INVALID_SIZE = -2,
	ALLOC_ERR = -3,

};


// RELEASE // RELEASE // RELEASE // RELEASE // RELEASE // RELEASE // RELEASE // RELEASE // RELEASE // RELEASE // RELEASE // RELEASE //
#ifdef RELEASE

#undef COVER_TEST

void *Calloc (size_t num, size_t size) {return calloc (num, size);}
void *Malloc (size_t size) {return malloc (size);}

#endif // RELEASE
//-------------------------------------------------------------------------------------------------------------------------------------


// COVERAGE TEST // COVERAGE TEST // COVERAGE TEST // COVERAGE TEST // COVERAGE TEST // COVERAGE TEST // COVERAGE TEST // COVERAGE TEST
#ifdef COVER_TEST

static int alloc_call = 0;

void *Calloc (size_t num, size_t size) {
	if (alloc_call == 5) {
		alloc_call = 0;
		return NULL;
	} else {
		alloc_call ++;
		return calloc (num, size);
	}
	return NULL;
}

void *Malloc (size_t size) {
	if (alloc_call == 5) {
		alloc_call = 0;
		return 0;
	} else {
		alloc_call ++;
		return malloc (size);
	}
}
#endif // COVER_TEST
//-------------------------------------------------------------------------------------------------------------------------------------


bitarr_t *Construct (size_t capacity) {
	bitarr_t bitarr;
	bitarr->array = (uint64_t *) calloc (capacity, sizeof (uint64_t));
	bitarr->capacity = capacity;
	bitarr->size = 0;
	return bitarr;
}

void Destruct (bitarr_t bitarr) {
	free (bitarr->array);
	bitarr->array = NULL;
	bitarr->size = 0;
	bitarr->capacity = 0;
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


// LOGS DUMP // LOGS DUMP // LOGS DUMP // LOGS DUMP // LOGS DUMP // LOGS DUMP // LOGS DUMP // LOGS DUMP // LOGS DUMP // LOGS DUMP // 
void Dump (bitarr_t *bitarr, const char *pathname);
char *TimeNow ();

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
//-------------------------------------------------------------------------------------------------------------------------------------
