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

	Options options = {.round = 0, .help = 0};

	while ((option = getopt(argc, argv, "rch")) != -1) {
		switch (option) {
			case 'r':
				options.round = 1;
				break;
			case 'c':
				options.clean = 1;
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
	printf("Usage: %s [-r] [-h]\n", command);
	puts("  -r  Round the memory usage percentage");
	puts("  -c  Clean number without percentage sign");
	puts("  -h  Display this help message");
}
