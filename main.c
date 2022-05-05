#include "bitarray.h"

void ErrorTest ();
void CountTest ();
void SetGetTest ();
void FullSetTest ();
void FindTest ();
void ConstructTest ();
void DestructTest ();
void CheckTest ();

int main () {
	CheckTest ();
	ConstructTest ();
	DestructTest ();
	SetGetTest ();
	FindTest ();
	FullSetTest ();
	CountTest ();
	ErrorTest ();

	exit (EXIT_SUCCESS);
}

void ErrorTest () {
	int capacity = 128;
	bitarr_t *bitarr = Bitarr (capacity);
	All (NULL);
	Any (NULL);
	bitarr->capacity = -5;
	None (bitarr);
	Reset (bitarr);
	Set (bitarr);
	SetVal (bitarr, SET);
	Flip (bitarr);

	bitarr->capacity = capacity;
	ResizeUp (bitarr, -5);

	free (bitarr->array);
	bitarr->array = NULL;

	GetBit (bitarr, 5);
	SetBit (bitarr, 10);
	UnsetBit (bitarr, 6);
	SetBitVal (bitarr, 3, SET);
	FindLastSet (bitarr);
	FindFirstUnset (bitarr);
	FindFirstSet (bitarr);
	FindLastUnset (bitarr);
	FindSetPos (bitarr, 15);
	FindUnsetPos (bitarr, 3);
	Count (bitarr);
	Dump (NULL, "dump.txt");

	printf ("error test done\n");
	Destruct (bitarr);
	return;
}

void CountTest () {
	int num = 57;
	bitarr_t *bitarr = Bitarr (128);

	for (size_t i = 0; i < num; i ++) {
		SetBit (bitarr, i + 5);
	}

	if (Count (bitarr) != num) {
		Destruct (bitarr);
		printf ("count test not passed\n");
		return;
	}

	Flip (bitarr);

	if (Count (bitarr) != Capacity (bitarr) - num) {
		Destruct (bitarr);
		printf ("count test not passed\n");
		return;
	}

	Dump (bitarr, "dump.txt");
	Destruct (bitarr);

	printf ("count test passed\n");
	return;
}

void SetGetTest () {
	bitarr_t *bitarr = Bitarr (130);
	int pos = 0;

	SetBit (bitarr, -1);
	UnsetBit (bitarr, -2);
	SetBitVal (bitarr, -3, SET);
	SetBitVal (bitarr, 5, 3);
	GetBit (bitarr, -5);

	SetBitVal (bitarr, Capacity (bitarr) + 1, SET);
	SetBitVal (bitarr, Capacity (bitarr) + 5, UNSET);
	SetBit (bitarr, Capacity (bitarr) + 1);
	UnsetBit (bitarr, Capacity (bitarr) + 1);

	if (GetBit (bitarr, Capacity (bitarr) + 1) != 0) {
		printf ("set - get test not passed (out of capacity got something but not zero)\n");
		Destruct (bitarr);
		return;
	}

	Destruct (bitarr);
	bitarr = Bitarr (64);

	for (ssize_t i = 0; i < 9; i ++) {
		pos = i * i;
		SetBitVal (bitarr, pos, SET);
		if (GetBit (bitarr, pos) != SET) {
			Destruct (bitarr);
			printf ("SetGet test not passed (bit %ld was not set)\n", i);
			return;
		}
	}

	Set (bitarr);

	for (ssize_t i = 0; i < 12; i++) {
		pos = i * i + 5;
		SetBitVal (bitarr, pos, UNSET);
		if (GetBit (bitarr, pos) != UNSET) {
			Destruct (bitarr);
			printf ("SetGet tests no passed (bit %ld was not unset)\n", i);
			return;
		}
	}

	Destruct (bitarr);

	printf ("set - get tests passed\n");
	return;
}

void FullSetTest () {

	bitarr_t *bitarr = Bitarr (130);

	SetVal (bitarr, UNSET);
	SetVal (bitarr, SET);
	SetVal (bitarr, -1);
	Reset (bitarr);

	if (!All (bitarr)) Set (bitarr);
	if (!All (bitarr)) {
		Destruct (bitarr);
		printf ("full set tests not passed (all != 1 after Set)\n");
		return;
	}

	if (!Any (bitarr)) {
		Destruct (bitarr);
		printf ("full set tests not passed (any != 1 after Set)\n");
		return;
	}

	if (!None (bitarr)) Reset (bitarr);
	if (!None (bitarr)) {
		Destruct (bitarr);
		printf ("full set tests not passed (none != 1 after Reset)\n");
		return;
	}

	if (Any (bitarr)) {
		Destruct (bitarr);
		printf ("full set tests not passed (any != 0 after Reet)\n");
		return;
	}

	Destruct (bitarr);

	printf ("full set tests passed\n");
	return;
}

void FindTest () {
	bitarr_t *bitarr = Bitarr (128);

	Reset (bitarr);

	if (FindLastSet (bitarr) != -1) {
		Destruct (bitarr);
		printf ("find tests not passed (fls 1 error)\n");
		return;
	}
	if (FindFirstUnset (bitarr) != 0) {
		Destruct (bitarr);
		printf ("find tests not passed (ffu 1 error)\n");
		return;
	}
	if (FindFirstSet (bitarr) != -1) {
		Destruct (bitarr);
		printf ("find tests not passed (ffs 1 error)\n");
		return;		
	}
	if (FindLastUnset (bitarr) != Capacity (bitarr) - 1) {
		Destruct (bitarr);
		printf ("find tests not passed (flu 1 error)\n");
		return;
	}
	if (FindSetPos (bitarr, 3) != -1) {
		Destruct (bitarr);
		printf ("find tests not passed (fsp 1 error)\n");
		return;
	}
	if (FindUnsetPos (bitarr, 2) != 1) {
		Destruct (bitarr);
		printf ("find tests not passed (fup 1 error)\n");
		return;
	}
	
	Set (bitarr);

	if (FindLastSet (bitarr) != Capacity (bitarr) - 1) {
		Destruct (bitarr);
		printf ("find tests not passed (fls 2 error)\n");
		return;
	}
	if (FindFirstUnset (bitarr) != -1) {
		Destruct (bitarr);
		printf ("find tests not passed (ffu 2 error)\n");
		return;
	}
	if (FindFirstSet (bitarr) != 0) {
		Destruct (bitarr);
		printf ("find tests not passed (ffs 2 error)\n");
		return;
	}
	if (FindLastUnset (bitarr) != -1) {
		Destruct (bitarr);
		printf ("find tests not passed (flu 2 error)\n");
		return;
	}
	if (FindSetPos (bitarr, 3) != 2) {
		Destruct (bitarr);
		printf ("find tests not passed (fsp 2 error)\n");
		return;
	}
	if (FindUnsetPos (bitarr, 2) != -1) {
		Destruct (bitarr);
		printf ("find tests not passed (fup 2 error)\n");
		return;
	}


	if (FindSetPos (bitarr, -1) >= 0) {
		Destruct (bitarr);
		printf ("find tests not passed (fsp 3 error)\n");
		return;
	}
	if (FindUnsetPos (bitarr, -5) >= 0) {
		Destruct (bitarr);
		printf ("find tests not passed (fup 3 error)\n");
		return;
	}

	Destruct (bitarr);

	printf ("find tests passed\n");
	return;
}

void ConstructTest () {
	bitarr_t *arr = Bitarr (64);
	Destruct (arr);

	arr = Bitarr (-5);
	Destruct (arr);

	for (size_t i = 0; i < 10; i ++) {
		bitarr_t *arr = Bitarr (i * 64 + i);
		Destruct (arr);
	}

	printf ("construct tests done\n");
	return;
}

void DestructTest () {
	bitarr_t *set1 = Bitarr (128);
	Destruct (set1);

	bitarr_t *set2 = Bitarr (128);
	free (set2->array);
	set2->array = NULL;
	Destruct (set2);

	Destruct (NULL);

	printf ("destruct tests done\n");
	return;
}

void CheckTest () {
	bitarr_t *set1 = Bitarr (128);
	set1->capacity = -1;
	Check (set1);
	Destruct (set1);

	bitarr_t *set2 = Bitarr (128);
	free (set2->array);
	set2->array = NULL;
	Check (set2);
	Destruct (set2);

	Check (NULL);

	printf ("check tests done\n");
	return;
}