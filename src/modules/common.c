#include <math.h>
#include <stdio.h>
#include "../defs.h"

void print_output(double perc, Options options)
{
	const char *fmt;

	if (options.doub) {
		fmt = options.perc == 1 ? "%.2f%%\n" : "%.2f\n";
	} else {
		perc = round(perc);
		fmt = options.perc == 1 ? "%.0f%%\n" : "%.0f\n";
	}

	printf(fmt, perc);
}
