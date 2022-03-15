#include "bitarray.h"

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


	Dump (&bitarr, "dump.txt");
	Reset (&bitarr);

	exit (EXIT_SUCCESS);
}
