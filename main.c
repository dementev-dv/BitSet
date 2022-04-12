#include "bitarray.h"

int main () {

	bitarr_t *bitarr = Construct (128);
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

	printf ("count = %d\n", Count (bitarr));

	Dump (bitarr, "dump.txt");
	Reset (bitarr);

	exit (EXIT_SUCCESS);
}
