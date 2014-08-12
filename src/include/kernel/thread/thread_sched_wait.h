/**
 * @file
 * @brief Defines thread-specific methods for waiting. You can also or instead
 *        use ones from sched.h
 *
 * @date 7.08.2014
 * @author Vita Loginova
 */

#ifndef THREAD_SCHED_WAIT_H_
#define THREAD_SCHED_WAIT_H_

#include <kernel/thread/signal_lock.h>
#include <kernel/sched.h>


/**
 * Wait cond_expr to become TRUE.
 */
#define SCHED_WAIT(cond_expr) \
	SCHED_WAIT_TIMEOUT(cond_expr, SCHED_TIMEOUT_INFINITE)

#define SCHED_WAIT_TIMEOUT(cond_expr, timeout) \
	((cond_expr) ? 0 : ({                                            \
		int __wait_ret = 0;                                          \
		clock_t __wait_timeout = timeout == SCHED_TIMEOUT_INFINITE ? \
			SCHED_TIMEOUT_INFINITE : ms2jiffies(timeout);            \
		                                                             \
		threadsig_lock();                                            \
		do {                                                         \
			sched_wait_prepare();                                    \
			                                                         \
			if (cond_expr)                                           \
				break;                                               \
			                                                         \
			__wait_ret = sched_wait_timeout(__wait_timeout,          \
											&__wait_timeout);        \
		} while (!__wait_ret);                                       \
		                                                             \
		sched_wait_cleanup();                                        \
		                                                             \
		threadsig_unlock();                                          \
		__wait_ret;                                                  \
	}))

#endif /* THREAD_SCHED_WAIT_H_ */
