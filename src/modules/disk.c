#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include "../defs.h"

int dskp(int argc, char *argv[], Options options)
{
	struct statvfs stat;
	char *path = "/";

	if (optind < argc) {
		path = argv[optind];
	}

	if (statvfs(path, &stat) != 0) {
		fprintf(stderr, "Failed to run statvfs on path: %s\n", path);
		return EXIT_FAILURE;
	}

	unsigned long total = stat.f_blocks * stat.f_frsize;
	unsigned long free = stat.f_bfree * stat.f_frsize;
	unsigned long used = total - free;

	float perc = (float)used / (float)total * 100.0;

	print_output(perc, options);

	return EXIT_SUCCESS;
}

void dskp_help()
{
	printf("Usage: dskp [-r] [-c] [-h] [path]\n");
	puts("  path    Disk path (default: /)");
	puts("  -r      Round the memory usage percentage");
	puts("  -c      Clean number without percentage sign");
	puts("  -h      Display this help message");
}
