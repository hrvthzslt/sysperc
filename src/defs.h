typedef struct {
	int doub;
	int perc;
	int help;
} Options;

void print_output(double perc, Options options);

int cpup(Options options);
int memp(Options options);
int dskp(int argc, char *argv[], Options options);
void dskp_help(void);
int batp(int argc, char *argv[], Options options);
void batp_help(void);
