#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include "../defs.h"

int batp(int argc, char *argv[], Options options)
{
	char *battery = "BAT0";
	char path[128];

	if (optind < argc) {
		battery = argv[optind];
	}

	sprintf(path, "/sys/class/power_supply/%s/capacity", battery);

	FILE *fp = fopen(path, "r");

	if (!fp) {
		fprintf(stderr, "Cannot open battery capacity file: %s\n", battery);
		return EXIT_FAILURE;
	}

	int perc;

	if (fscanf(fp, "%d", &perc) != 1) {
		fclose(fp);
		fprintf(stderr, "Cannot read battery percentage\n");
		return EXIT_FAILURE;
	}

	print_output(perc, options, "B: ");

	return EXIT_SUCCESS;
}

void batp_help()
{
	printf("Usage: batp [-d] [-p] [-h] [battery]\n");
	puts("  battery Battery name (default: BAT0)");
	puts("  -d      Show value as double");
	puts("  -p      Print with percentage sign");
	puts("  -i      Show icon before value");
	puts("  -h      Display this help message");
}
