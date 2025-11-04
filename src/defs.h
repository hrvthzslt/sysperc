typedef struct {
	int round;
	int clean;
	int help;
} Options;

void print_output(float perc, Options options);

int cpup(Options options);
int memp(Options options);
int dskp(int argc, char *argv[], Options options);
void dskp_help();
int batp(int argc, char *argv[], Options options);
void batp_help();
