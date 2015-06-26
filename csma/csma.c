#include "csma.h"

void debug(const char *format, ...) {
	if (DEBUG == 0)
		return;

	va_list ap;
	va_start(ap, format);
	char **args = va_arg(ap, char*);
	printf(format, args);
	va_end(ap);
}

/* wrappers to print error message if pthread routines fail */
void pt_mutex_init_wrapper(pthread_mutex_t *thread, 
	                       const pthread_mutexattr_t *attr) {
	if (pthread_mutex_init(thread, attr) != 0)
		errExit("pthread_mutex_init");
}

void pt_cond_init_wrapper(pthread_cond_t *cond, 
	                       const pthread_condattr_t *attr) {
	if (pthread_cond_init(cond, attr) != 0)
		errExit("pthread_cond_init");
}

void pt_mutex_lock_wrapper(pthread_mutex_t *mutex) {
	if (pthread_mutex_lock(mutex) != 0)
		errExit("pthread_mutex_lock");
}

void pt_mutex_unlock_wrapper(pthread_mutex_t *mutex) {
	if (pthread_mutex_unlock(mutex) != 0)
		errExit("pthread_mutex_unlock");
}

void pt_cond_wait_wrapper(pthread_cond_t *cond, pthread_mutex_t *mutex) {
	if (pthread_cond_wait(cond, mutex) != 0)
		errExit("pthread_cond_wait");
}

void pt_cond_broadcast_wrapper(pthread_cond_t *cond) {
	if (pthread_cond_broadcast(cond) != 0)
		errExit("pthread_cond_broadcast");
}

void pt_mutex_destroy_wrapper(pthread_mutex_t *mutex) {
	if (pthread_mutex_destroy(mutex) != 0)
		errExit("pthread_mutex_destroy");
}

void pt_cond_destroy_wrapper(pthread_cond_t * cond) {
	if (pthread_cond_destroy(cond) != 0)
		errExit("pthread_cond_destroy");
}

void pt_create_wrapper(pthread_t *thread, const pthread_attr_t *attr,
                              void *(*start_routine)(void*), void *arg) {
	if (pthread_create(thread, attr, start_routine, arg) != 0)
		errExit("pthread_create");
}

void pt_join_wrapper(pthread_t thread, void **value_ptr) {
	if (pthread_join(thread, value_ptr) != 0)
		errExit("pthread_join");
}