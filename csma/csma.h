#ifndef CSMA_H
#define CSMA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <getopt.h>
#include <stdarg.h>

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define TIME_SLOT 51 /* usecs */
#define ROUNDS 100
#define DEBUG 0 /* change to turn on/off debugging statements */

/* stations need both of these to transmit */
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
 * Transmit, reporting wait time and increment the global wait 
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

/* station :
 *
 * Go through designated number of rounds and attempt to transmit
 * with probability assigned from command line.
 */
void *station(void *arg);

/*
 * master :
 *
 * Field the time slot alarm and send broadcast signal to all 
 * threads ready to transmit.
 */
void *master(void *arg);

void parse_args(int argc, char**argv);

void help(char *name);

void print_globals();

void debug(const char *format, ...);

/* wrappers to print error message if pthread routines fail */
void pt_mutex_init_wrapper(pthread_mutex_t *thread, 
	                       const pthread_mutexattr_t *attr);

void pt_cond_init_wrapper(pthread_cond_t *cond, 
	                       const pthread_condattr_t *attr);

void pt_mutex_lock_wrapper(pthread_mutex_t *mutex);

void pt_mutex_unlock_wrapper(pthread_mutex_t *mutex);

void pt_cond_wait_wrapper(pthread_cond_t *cond, pthread_mutex_t *mutex);

void pt_cond_broadcast_wrapper(pthread_cond_t *cond);

void pt_mutex_destroy_wrapper(pthread_mutex_t *mutex);

void pt_cond_destroy_wrapper(pthread_cond_t * cond);

void pt_create_wrapper(pthread_t *thread, const pthread_attr_t *attr,
                              void *(*start_routine)(void*), void *arg);

void pt_join_wrapper(pthread_t thread, void **value_ptr);

#endif