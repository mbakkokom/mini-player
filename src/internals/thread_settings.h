#ifndef INTERNALS_THREAD_SETTINGS_H_
#define INTERNALS_THREAD_SETTINGS_H_

#include <pthread.h>

#ifdef THREAD_INSTANCES
	extern volatile int thread_should_exit;
#else
	extern void *thread_renderer(void *arguments);
	extern void *thread_bufferer(void *arguments);
#endif

#endif /* INTERNALS_THREAD_SETTINGS_H_ */
