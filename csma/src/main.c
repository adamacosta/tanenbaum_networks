#include "csma.h"

int main(int argc, char **argv) {
	long i;
	pthread_t *stations;
	pthread_t master_thread;

	parse_args(argc, argv);
	debug("beginning...\n");

	stations = malloc(n_stations * sizeof(pthread_t));
	on_wire = 0;
	slot_count = 0;
	trans_count = 0;
	global_wait = 0;

	pt_mutex_init_wrapper(&wire, NULL);
	pt_cond_init_wrapper(&slot, NULL);

	/* master thread is needed to sound the time slot alarm */
	pt_create_wrapper(&master_thread, NULL, master, NULL);

	for (i = 0; i < n_stations; i++)
		pt_create_wrapper(&stations[i], NULL, station, (void *) i);

	/* wait only on stations -- master runs forever */
	for (i = 0; i < n_stations; i++)
		pt_join_wrapper(stations[i], NULL);

	pt_mutex_destroy_wrapper(&wire);
	pt_cond_destroy_wrapper(&slot);
	free(stations);

	print_globals();

	return EXIT_SUCCESS;
}

void parse_args(int argc, char**argv) {
	if (argc < 3)
		help(argv[0]);
	
	int help_flag;
	int c;

	struct option longopts[] = {
		/* flags */
		{"verbose", no_argument, &verbose, 1},
		{"help", no_argument, &help_flag, 1},
		{0, 0, 0, 0}
	};

	while (1) {
		int option_index = 0;

		c = getopt_long(argc, argv, ":vh", longopts, &option_index);

		if (c == -1)
			break;

		switch(c) {
			case 0:
				break;
			case 'v':
				verbose = 1;
				break;
			case 'h':
				help(argv[0]);
			case ':':
				break;
			case '?':
			default:
				fprintf(stderr, "%s: option -%c is invalid: ignored\n",
					    argv[0], optopt);
				break;
		}
	}

	if (help_flag)
		help(argv[0]);

	n_stations = atoi(argv[optind++]);
	prob_transmit = atof(argv[optind++]);
}

void help(char *name) {
	printf("usage: %s [OPTION] [N] [P]\n", name);
	printf("Simulate the CSMA/CD transmission contention protocol.\n\n");
	printf("Required arguments:\n\n");
	printf("  N : int         the number of stations\n");
	printf("  P : double      the probability of each\n");
	printf("                    station transmitting in a timeslot\n");
	printf("Optional arguments:\n\n");
	printf("  -v, --verbose   print station messages\n");
	printf("  -h, --help      print this help message and exit\n");
	exit(EXIT_SUCCESS);
}

void print_globals() {
	printf("\n----------     GLOBAL STATS     ----------\n\n");
	printf("stations              : %d\n", n_stations);
	printf("rounds                : %d\n", ROUNDS);
	printf("probability per round : %f\n", prob_transmit);
	printf("transmissions         : %d\n", trans_count);
	printf("wait time             : %d usecs\n", global_wait);
	printf("wait per transmission : %f usecs\n", (double)(global_wait/n_stations));
}