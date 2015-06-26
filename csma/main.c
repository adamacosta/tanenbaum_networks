#include "csma.h"

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("usage: %s [N] [P] [--verbose]\n\n", argv[0]);
		printf("    N    : int    -- the number of stations\n");
		printf("    P    : double -- the probability of each\n");
		printf("                     station transmitting in a timeslot\n");
		printf("    --verbose : print station messages\n");
		exit(EXIT_FAILURE);
	}

	long i;
	pthread_t *stations;
	pthread_t master_thread;
	
	n_stations = atoi(argv[1]);
	prob_transmit = atof(argv[2]);
	stations = malloc(n_stations * sizeof(pthread_t));
	on_wire = 0;
	slot_count = 0;
	trans_count = 0;
	global_wait = 0;
	verbose = 0;

	if (argc == 4 && strcmp(argv[3], "--verbose") == 0)
		verbose = 1;

	pthread_mutex_init(&wire, NULL);
	pthread_cond_init(&slot, NULL);

	/* master thread is needed to sound the time slot alarm */
	pthread_create(&master_thread, NULL, master, NULL);

	for (i = 0; i < atoi(argv[1]); i++)
		pthread_create(&stations[i], NULL, station, (void *) i);

	for (i = 0; i < atoi(argv[1]); i++)
		pthread_join(stations[i], NULL);

	pthread_mutex_destroy(&wire);
	pthread_cond_destroy(&slot);
	free(stations);

	printf("\n----------     GLOBAL STATS     ----------\n\n");
	printf("stations              : %d\n", n_stations);
	printf("rounds                : %d\n", ROUNDS);
	printf("probability per round : %f\n", prob_transmit);
	printf("transmissions         : %d\n", trans_count);
	printf("wait time             : %d usecs\n", global_wait);
	printf("wait per transmission : %f usecs\n", (double)(global_wait/n_stations));

	return EXIT_SUCCESS;
}