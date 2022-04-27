# Description

This programm is a C library that implements a bit array container, with supporting of these functions:

| function| description                            													|
|-----|---------------------------------------------------------------------------------------------|
|  Bitarr (capacity)			| constructs bit array of given capacity							|
|  Destruct (bitarr)			| destructs the given array 										|
|  All (bitarr) 				| returns 1 if all the bits are set and 0 if any of them are unset	|
|  Any (bitarr) 				| returns 1 if any of bits is set and 0 otherwise					|
|  None (bitarr)				| returns 1 if all the bits are unset and 0 otherwise				|
|  Reset (bitarr)				| sets all the bits to 0											|
|  Set (bitarr)					| sets all the bits to 1											|
|  SetVal (bitarr, val)			| sets all bits to the given value (0 or 1)							|
|  Flip (bitarr)				| reverses all the bits (fron 1 to 0 and from 0 to 1)				|
|  ResizeUp (bitarr, extra)		| increases the capacity by the extra value							|
|  GetBit (bitarr, pos)			| returns the value of bit on the given position					|
|  SetBit (bitarr, pos)			| sets the bit on the given position to 1							|
|  UnsetBit (bitarr, pos)		| sets the bit on the given position to 0							|
|  SetBitVal (bitarr, pos, val)	| sets the bit on the given position to the given value (o or 1)	|
|  FindLastSet (bitarr)			| returns the position of the last set bit							|
|  FindFirstSet (bitarr)		| returns the position of the last set bit							|
|  FindFirstUnset (bitarr)		| returns the position of the last set bit							|
|  FindLastUnset (bitarr) 		| returns the position of the last set bit							|
|  FindSetPos (bitarr, num)		| returns the position of set bit by num							|
|  FindUnsetPos (bitarr, num)	| returns the position of unset bit by num							|
|  Count (bitarr)				| returns the number of set bits in array							|
|  Check (bitarr)				| checks if the array is valid										|
|  Dump (bitarr, filename)		| dumps all the values in bitset									|


# Make and Run

To use lib with your main gile, you should use [make](https://github.com/krutoi-muzhik/BitSet/blob/main/Makefile)

To see the testing coverage you can use "make test", which executes my tests in [main.c](https://github.com/krutoi-muzhik/BitSet/blob/main/main.c)

# Coverage and tests

In [main.c](https://github.com/krutoi-muzhik/BitSet/blob/main/main.c) you can find some setsing functions. All of them include tests for invalid positions, capacities and pointers.

```C
void ErrorTest ();
void CountTest ();
void SetGetTest ();
void FullSetTest ();
void FindTest ();
void ConstructTest ();
void DestructTest ();
void CheckTest ();
```

The resulting coverage is 97%, you can see it, by using "make test". This make rule will generate html report in "report dir"

![coverage](https://github.com/krutoi-muzhik/BitSet/blob/main/img/coverage.png)

# Implementation

## Main issues

The type of data, where we contain our bits is uint64_t, which is the biffest integer, so it is fast to set it to zero or to the max value.

## Set the whole array

To fo it, we just set all the integers to ULLONG_MAX:

```C
void Set (bitarr_t *bitarr) {
	for (ssize_t i = 0; i < bitarr->capacity / ELEMENT_SIZE; i ++) {
		bitarr->array[i] = ULLONG_MAX;
	}

	return;
}
```

Likewise we set all the integers to 0, to set the whole array to 0

## Set the bit

That's what setting a single bit on a given position looks like:

```C
void SetBit (bitarr_t *bitarr, int pos) {
	if (pos >= bitarr->capacity) {
		ResizeUp (bitarr, pos - bitarr->capacity + 1);
	}

	uint64_t *point = bitarr->array + pos / ELEMENT_SIZE; 
	uint64_t mask = 1;
	mask = mask << (pos % ELEMENT_SIZE);

	*point = *point | mask;

	return;
}
```

Likewhise we can unset a single bit

```C
void UnsetBit (bitarr_t *bitarr, int pos) {
	if (pos >= bitarr->capacity) {
		ResizeUp (bitarr, pos - bitarr->capacity + 1);
		return;
	}

	uint64_t *point = bitarr->array + pos / ELEMENT_SIZE; 
	uint64_t mask = 1;
	mask = mask << (pos % ELEMENT_SIZE);

	mask = ~mask;
	*point = *point & mask;

	return;
}
```

And using the same method we can Get the needed bit

```C
int GetBit (bitarr_t *bitarr, int pos) {
	if (pos >= bitarr->capacity) {
		ResizeUp (bitarr, pos - bitarr->capacity);
			return UNSET;
	}

	uint64_t mask = 1;
	mask = mask << pos % ELEMENT_SIZE;
	if (bitarr->array[pos / ELEMENT_SIZE] & mask)
		return SET;

	return UNSET;
}
```

## Find the set bit

To find we firstly skip the integers, that surely don't contain the needed bit, and then using bit shifts we skip unappropriate bits untill we get the needed one.

```C
int FindFirstSet (bitarr_t *bitarr) {
	int result = 0;
	size_t i = 0;

	for (i = 0; i <= bitarr->capacity / ELEMENT_SIZE - 1; i ++) {
		if (bitarr->array[i])
			break;
		result += ELEMENT_SIZE;
	}

	if (result == bitarr->capacity)
		return -1;

	uint64_t current = bitarr->array[i];
	
	for (size_t offset = 0; offset < ELEMENT_SIZE; offset ++) {
		if (current & ((uint64_t) 1 << offset))
			break;
		result ++;
	}

	return result;
}
```

# Handling Errors

The main Idea of using lcov to test our code coverage is to check, whether we handle every type of errors.

Here are main types of errors:

```C
typedef enum ERRORS {
	VSE_OK = 0,
	NO_MATCH = -1,
	INVALID_SIZE = -2,
	ALLOC_ERR = -3,
	INVALID_ARRAY = -4,
	REALLOC_ERROR = -5,
	INVALID_CAPACITY = -6,	// extra for resize is considered here too
	INVALID_VAL = -7, // only 2 values are available: SET (1) and UNSET (0)
	INVALID_BITARR = -8,
	UNKNOWN_ERROR = -9,
	INVALID_CONTAINER = -10,
	INVALID_NUM = -11,
	INVALID_POS = -12
} error_t;
```

In every function we firstly check the whole container and only after that start the main body of function.

# ToDo

In future I am going to write errors codes and descriptions to STDERR stream