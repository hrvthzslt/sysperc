#include <math.h>
#include <stdio.h>
#include "../defs.h"

void print_output(float perc, Options options)
{
	const char *fmt;

	if (options.round) {
		perc = roundf(perc);
		fmt = options.perc == 1 ? "%.0f%%\n" : "%.0f\n";
	} else {
		fmt = options.perc == 1 ? "%.2f%%\n" : "%.2f\n";
	}

	printf(fmt, perc);
}
