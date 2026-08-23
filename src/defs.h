typedef struct {
	int doub;
	int perc;
	int help;
	int icon;
} Options;

void print_output(double perc, Options options, const char *icon);

int cpup(Options options);
int memp(Options options);
int dskp(int argc, char *argv[], Options options);
void dskp_help();
int batp(int argc, char *argv[], Options options);
void batp_help();
