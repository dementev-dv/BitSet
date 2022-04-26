#include "bitarray.h"

int main () {

	bitarr_t *bitarr = Construct (128);
	SetBit (bitarr, 0);
	SetBit (bitarr, 63);
	SetBit (bitarr, 64);
	SetBit (bitarr, 65);
	SetBit (bitarr, 66);
	SetBit (bitarr, 67);
	SetBit (bitarr, 68);
	SetBit (bitarr, 69);
	SetBit (bitarr, 70);
	SetBit (bitarr, 71);
	SetBit (bitarr, 72);
	SetBit (bitarr, 127);
	SetBit (bitarr, 126);
	SetBit (bitarr, 125);
	SetBit (bitarr, 124);
	SetBit (bitarr, 123);
	SetBit (bitarr, 122);
	SetBit (bitarr, 121);
	SetBit (bitarr, 120);
	SetBit (bitarr, 119);

	SetBit (bitarr, 128);

	Set (bitarr);
	UnsetBit (bitarr, 1);
	UnsetBit (bitarr, 2);
	UnsetBit (bitarr, 3);


	printf ("ffs = %d\n", FindFirstSet (bitarr));
	printf ("fls = %d\n", FindLastSet (bitarr));
	printf ("set %d = %d\n", 3, FindSetPos (bitarr, 3));
	printf ("count = %d\n", Count (bitarr));
	printf ("unset %d = %d\n", 4, FindUnsetPos (bitarr, 4));
	printf ("ffu = %d\n", FindFirstUnset (bitarr));
	printf ("flu = %d\n", FindLastUnset (bitarr));
	Flip (bitarr);
	printf ("count = %d\n", Count (bitarr));

	Dump (bitarr, "dump.txt");
	Reset (bitarr);

	exit (EXIT_SUCCESS);
}
