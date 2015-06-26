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

sigset_t vtalrm;
struct itimerval timer;
struct sigaction act;

pthread_mutex_t wire;
pthread_cond_t slot;

int verbose;
int on_wire; 
int n_stations;
int trans_count;
int global_wait;
long slot_count;
double prob_transmit;

/* Sends broadcast signal to all stations waiting for time slot */
void alrm_handler(int sig);

/*
 * Transmit, reporting wait time and incrementing the global wait 
 * counter to print to global stats at end of runs.
 */
void transmit(int tid, int wait);

void wait(int tid);

/* 
 * Attempt to transmit. First, check if any other station is trying 
 * to use the wire. If so, signal is jammed, so wait a random number 
 * of time slots, then re-attempt.
 */
void try_transmit(int tid);

void play_round(int tid);

/* station threads :
 *
 * Go through designated number of rounds and attempt to transmit
 * with probability assigned from command line.
 */
void *station(void *arg);

/*
 * master :
 *
 * Fields the time slot alarm and send broadcast signal to all 
 * threads ready to transmit.
 */
void *master(void *arg);