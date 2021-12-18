/**
 * Implementation of a threadpool based on the POSIX API
 *
 * Note: it is based on the following article, contributed to Intel
 * https://software.intel.com/fr-fr/articles/Thread-pool
 *
 * Let me note the code was wrong in many aspects:
 * - incorrect queue management for the dequeue case, causing segfaults
 * - inconsistencies in the termination algorithm, leading to deadlocks
 *
 */

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

/* Standard C Headers */
#include <pthread.h>
#include <stdbool.h>


/******************************************************************************/
/* Private types */

/**
 * @brief Here is the definition of a structure representing a task to be
 * executed by a thread pool.
 *
 * @attribute routine The funtion to be called when the task is executed.
 * @attribute data    The data to be sent to the callback function.
 * @attribute next    The next task in the queue that stores the tasks.
 */
typedef struct _pthread_task {
  void (*routine)();
  void *data;
  struct _pthread_task *next;
} pthread_task_t;

/**
 * @brief Here is the definition of a structure representing a synchronized
 * queue where pending tasks are stored before being executed by the thread
 * pool.
 *
 * @attribute mutex The mutex used to synchronize the access to the task queue.
 * @attribute cond  The condition to be used by the threads to wait for tasks.
 * @attribute first The first task in the queue.
 * @attribute last  The last task in the queue.
 * @attribute terminated flag, to say whether the execution has been terminated.
 */

typedef struct _pthread_queue {
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  pthread_task_t *first;
  pthread_task_t *last;
  bool terminated;
} pthread_queue_t;

/**
 * @brief Here is the definition of a structure representing a thread pool.
 *
 * @attribute mutex   A mutex used to synchronize the access to the thread pool.
 * @attribute queue   The instance of pthread_queue_t used to store the pending
 * tasks.
 * @attribute threads The vector storing the list of threads.
 * @attribute thread_init The number of initialized threads.
 * @attribute thread_count The number of threads in the thread pool.
 */
struct _pthread_pool {
  pthread_mutex_t mutex;
  pthread_queue_t queue;
  pthread_t *threads;
  size_t thread_init;
  size_t thread_count;
};

/**
 * Thread pool API
 */

typedef struct _pthread_pool pthread_pool_t;
/** Opaque structure representing a thread pool, see .c for details */

pthread_pool_t *pthread_pool_init (int nbThreads);
/** Initialize a thread pool with nbThreads */

int pthread_pool_exec(pthread_pool_t *thread_pool, void (*function)(), void *data);

/** Have the threadpool execute function(), passing data as optional
    parameter.

    WARNING: data cannot be a variable allocated on the stack, it has
    to be allocated through malloc().

 */

void pthread_pool_destroy (void *data);
//void pthread_pool_destroy (pthread_pool_t *thread_pool);
/** Destroy threadpool, handling graceful termination of the tasks */

#endif /* __THREADPOOL_H__ */
