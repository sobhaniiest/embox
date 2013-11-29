/**
	Interface for thread entities, used by scheduler
*/
#ifndef _KERNEL_RUNNABLE_H_
#define _KERNEL_RUNNABLE_H_


#include <kernel/sched/sched_strategy.h>

struct runnable {
	/**
		Thread-specific function, puts current thread in runq
	*/
	void                *(*sched_thread_specific)(struct runnable *p, struct runq *rq);

	/** Called by sched when replanned.
	*/
	void               *(*run)(struct runnable *p, struct runnable *n, struct runq *rq);
	void			   *run_arg;     /* Argument to be passed to run function */

	int                policy;       /**< Scheduling policy pointer*/
	struct sched_attr  sched_attr;   /**< Scheduler-private data pointer */
};

extern struct runnable *runnable_get_current(void);
extern void sched_thread_specific(struct runnable *p, struct runq *rq);
extern void sched_execute_thread(struct runnable *p, struct runnable *n, struct runq *rq);


#endif /* _KERNEL_RUNNABLE_H_ */
