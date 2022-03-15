#include <stdio.h>
#include <stdint.h>

int main () {
	uint64_t a = 1023;
	printf ("%ld %ld\n", sizeof (uint64_t), sizeof (a));
}