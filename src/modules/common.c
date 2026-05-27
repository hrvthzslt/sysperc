#include <stdio.h>
#include "../defs.h"

void print_output(double perc, Options options)
{
	if (options.doub) {
		if (options.perc == 1) {
			printf("%.2f%%\n", (double)perc);
			return;
		} else {
			printf("%.2f\n", perc);
			return;
		}
	} else if (options.perc == 1) {
		printf("%.0f%%\n", (double)perc);
		return;
	}

	printf("%.0f\n", perc);
}
