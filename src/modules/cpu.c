#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../defs.h"

typedef struct {
	unsigned long user, nice, system, idle;
} CpuStat;

const char *PROC_FILE = "/proc/stat";
const char *STAT_FILE = "/tmp/sinfo_cpu_stat";

static int get_cpu_stat(char *label, CpuStat *stat);
static unsigned long sum_stat(CpuStat stat);
static int save_stat(const char *label, CpuStat *stat);
static int load_stat(char *label, CpuStat *stat);

int cpup(Options options)
{
	char label[5];
	CpuStat stat1;
	CpuStat stat2;

	int has_prev = load_stat(label, &stat1);

	if (!get_cpu_stat(label, &stat2)) {
		return EXIT_FAILURE;
	}

	if (!save_stat(label, &stat2)) {
		return EXIT_FAILURE;
	}

	if (!has_prev) {
		print_output(0.00, options);
		return EXIT_SUCCESS;
	}

	unsigned long total1 = sum_stat(stat1);
	unsigned long total2 = sum_stat(stat2);
	unsigned long total_diff = total2 - total1;
	unsigned long idle_diff = stat2.idle - stat1.idle;

	double cpu_usage = 0.0;
	if (total_diff > 0) {
		cpu_usage = 100.0 * (total_diff - idle_diff) / total_diff;
	}

	print_output(cpu_usage, options);

	return EXIT_SUCCESS;
}

static int get_cpu_stat(char *label, CpuStat *stat)
{
	FILE *fp = fopen(PROC_FILE, "r");

	if (!fp) {
		fprintf(stderr, "File not found on system: %s\n", PROC_FILE);
		return 0;
	}

	fscanf(fp, "%s %lu %lu %lu %lu", label, &stat->user, &stat->nice,
	       &stat->system, &stat->idle);
	fclose(fp);

	return 1;
}

static unsigned long sum_stat(CpuStat stat)
{
	return stat.user + stat.nice + stat.system + stat.idle;
}

static int save_stat(const char *label, CpuStat *stat)
{
	FILE *fp = fopen(STAT_FILE, "w");
	if (!fp) {
		fprintf(stderr, "Cannot open for write: %s\n", STAT_FILE);
		return 0;
	}

	fprintf(fp, "%s %lu %lu %lu %lu\n", label, stat->user, stat->nice,
	        stat->system, stat->idle);
	fclose(fp);

	return 1;
}

static int load_stat(char *label, CpuStat *stat)
{
	FILE *fp = fopen(STAT_FILE, "r");
	if (!fp) {
		return 0;
	}

	int ret = fscanf(fp, "%s %lu %lu %lu %lu", label, &stat->user, &stat->nice,
	                 &stat->system, &stat->idle);
	fclose(fp);

	return (ret == 5) ? 1 : 0;
}
