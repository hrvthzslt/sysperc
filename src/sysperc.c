#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"

Options get_options(int argc, char *argv[]);
int bus(char *command, Options options, int argc, char *argv[]);
void help(char *command);

int main(int argc, char *argv[])
{
	Options options = get_options(argc, argv);

	if (options.help) {
		help(argv[0]);
		return EXIT_SUCCESS;
	}

	return bus(argv[0], options, argc, argv);
}

int bus(char *command, Options options, int argc, char *argv[])
{
	if (!strcmp(command, "cpup")) {
		return cpup(options);
	} else if (!strcmp(command, "memp")) {
		return memp(options);
	} else if (!strcmp(command, "dskp")) {
		return dskp(argc, argv, options);
	} else if (!strcmp(command, "batp")) {
		return batp(argc, argv, options);
	}

	fprintf(stderr, "Unknown command in sysperc executeable: %s\n", command);
	return EXIT_FAILURE;
}

Options get_options(int argc, char *argv[])
{
	int option;

	Options options = {.doub = 0, .perc = 0, .help = 0};

	while ((option = getopt(argc, argv, "dph")) != -1) {
		switch (option) {
			case 'd':
				options.doub = 1;
				break;
			case 'p':
				options.perc = 1;
				break;
			case 'h':
				options.help = 1;
				break;
		}
	}

	return options;
}

void help(char *command)
{
	if (!strcmp(command, "dskp")) {
		dskp_help();
		return;
	} else if (!strcmp(command, "batp")) {
		batp_help();
		return;
	}
	printf("Usage: %s [-d] [-h]\n", command);
	puts("  -d      Show value as double");
	puts("  -p      Print with percentage sign");
	puts("  -h      Display this help message");
}
