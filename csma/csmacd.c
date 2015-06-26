/* 
 * Write a program to simulate the behavior of the CSMA/CD protocol over Ethernet
 * when there are N stations ready to transmit while a frame is being transmitted.
 * Your program should report the time when each station successfully starts sending
 * its frame. Assume that a clock tick occurs every slot time (51.2 mu-secs) and a 
 * collision detection and sending of a jamming sequence takes one time slot. All 
 * frames are the maximum length allowed.
 */

/*
 * CSMA/CD - Carrier Sense Multiple Access with Collision Detection
 * 
 * Each station has a probability p of attempting to transmit in any time slot.
 * If a collision is detected, each station will wait a random amount of time
 * before attempting to re-transmit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>

#define TIME_SLOT 51
#define ROUNDS 100

static sigset_t vtalrm;
static struct itimerval timer;
static struct sigaction act;

pthread_mutex_t wire;
pthread_cond_t slot;
static int verbose;
static int on_wire; 
static int n_stations;
static int trans_count;
static int global_wait;
static long slot_count;
static double prob_transmit;

/* Sends broadcast signal to all stations waiting for time slot */
void alrm_handler(int sig) {
	//printf("alarm\n");
	slot_count++;
	pthread_cond_broadcast(&slot);
}

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
}

/* 
 * Attempt to transmit. First, check if any other station is trying 
 * to use the wire. If so, signal is jammed, so wait a random number 
 * of time slots, then re-attempt.
 */
void try_transmit(int tid) {
	int wait;
	int total_wait;

	wait = 0;
	total_wait = 0;
	//printf("station %d woke up - attempting to transmit\n", tid);
	while (1) {
		if (on_wire == 1) {
			transmit(tid, total_wait);
			on_wire--;
			pthread_mutex_unlock(&wire);
			break;
		} else {
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
					on_wire--;
					pthread_mutex_unlock(&wire);
					break;
				}
				on_wire--;
				pthread_mutex_unlock(&wire);
			}
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
void *stat_proc(void *arg) {
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

/*
 * master :
 *
 * Fields the time slot alarm and send broadcast signal to all 
 * threads ready to transmit.
 */
void *master(void *arg) {
	sigemptyset(&vtalrm);
  	sigaddset(&vtalrm, SIGVTALRM);
  	sigprocmask(SIG_UNBLOCK, &vtalrm, NULL);

  	timer.it_value.tv_sec = timer.it_interval.tv_sec = 0;
  	timer.it_value.tv_usec = timer.it_interval.tv_usec = TIME_SLOT;

  	setitimer(ITIMER_VIRTUAL, &timer, NULL);

	memset (&act, '\0', sizeof(act));
	act.sa_handler = &alrm_handler;
	if (sigaction(SIGVTALRM, &act, NULL) < 0) {
		perror ("sigaction");
		exit(EXIT_FAILURE);
	}

	while (1)
		;

	return NULL;
}

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
		pthread_create(&stations[i], NULL, stat_proc, (void *) i);

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