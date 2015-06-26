#include "csma.h"

/*
 * Transmit, reporting wait time and incrementing the global wait 
 * counter to print to global stats at end of runs.
 */
void transmit(int tid, int wait) {
	if (verbose) {
		printf("%d transmitting\n", tid);
		printf("  waited %d usecs\n", wait);
	}
	trans_count++;
	global_wait += wait;
	on_wire--;
	pthread_mutex_unlock(&wire);
}

void wait(int tid) {
	int wait;
	int total_wait;

	wait = 0;
	total_wait = 0;
	on_wire--;
	pthread_mutex_unlock(&wire);
	while (1) {
		wait = (1 + rand() % n_stations) * TIME_SLOT;
		total_wait += wait;
		//printf("station %d waiting %d usecs\n", tid, wait);
		usleep(wait);
		pthread_mutex_lock(&wire);
		on_wire++;
		if (on_wire == 1) {
			transmit(tid, total_wait);
			break;
		}
		on_wire--;
		pthread_mutex_unlock(&wire);
	}
}

/* 
 * Attempt to transmit. First, check if any other station is trying 
 * to use the wire. If so, signal is jammed, so wait a random number 
 * of time slots, then re-attempt.
 */
void try_transmit(int tid) {
	//printf("station %d woke up - attempting to transmit\n", tid);
	while (1) {
		if (on_wire == 1) {
			transmit(tid, 0);
			break;
		} else {
			wait(tid);
			break;
		}
	}
}

void play_round(int tid) {
	if (rand() % 100 > (prob_transmit * 100))
		return;
	pthread_mutex_lock(&wire);
	on_wire++;
	//printf("station %d ready to transmit slot %ld\n", tid, slot_count);
	pthread_cond_wait(&slot, &wire);
	try_transmit(tid);
}

/* station threads :
 *
 * Go through designated number of rounds and attempt to transmit
 * with probability assigned from command line.
 */
void *station(void *arg) {
	int i;
	intptr_t tid;
	struct timeval tu;

	gettimeofday(&tu, NULL);	
	srand(tu.tv_usec);

	tid = (intptr_t) arg;
	for (i = 0; i < ROUNDS; i++)
		play_round(tid);
	
	return NULL;
}