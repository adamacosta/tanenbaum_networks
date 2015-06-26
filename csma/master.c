#include "csma.h"

/* Sends broadcast signal to all stations waiting for time slot */
void alrm_handler(int sig) {
	//printf("alarm\n");
	slot_count++;
	pthread_cond_broadcast(&slot);
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