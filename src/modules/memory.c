#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../defs.h"

int memp(Options options)
{
	const char *MEMINFO_FILE = "/proc/meminfo";

	FILE *file = fopen(MEMINFO_FILE, "r");
	if (!file) {
		fprintf(stderr, "File not found: %s\n", MEMINFO_FILE);
		return EXIT_FAILURE;
	}

	long total = 0, available = 0;
	char line[256];

	while (fgets(line, sizeof(line), file)) {
		if (sscanf(line, "MemTotal: %ld kB", &total)) {
			continue;
		}
		if (sscanf(line, "MemAvailable: %ld kB", &available)) {
			break;
		}
	}
	fclose(file);

	if (total == 0) {
		fprintf(stderr, "MemTotal not found from meminfo\n");
		print_output(0.00, options);
		return EXIT_FAILURE;
	}

	float perc;
	perc = 100.0 * (total - available) / total;

	print_output(perc, options);

	return EXIT_SUCCESS;
}
