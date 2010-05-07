#include "thread.h"

#include "Paws.o/Paws.h"
#include <stdlib.h>
#include <unistd.h>


/* ==================
= Thread Management =
================== */

/* ### Method Declarations ### */

thread    Thread__create      (pool a_pool);
void      register_a_thread   (void *argument);

void      thread__work        (thread this);
void      thread__destroy     (thread this);

struct Thread const Thread = {
  .create     = Thread__create,
  
  .work       = thread__work,
  .destroy    = thread__destroy
};
void constructor Paws__register_Thread(void) { Paws.Threading.Thread = Thread; }


/* ### Method Implementations ### */

thread Thread__create(pool a_pool) {
  thread this = malloc(sizeof(struct thread));
  this->pthread = malloc(sizeof(pthread_t));
  
  this->pool = a_pool;
  pthread_create(&this->pthread,
    NULL, (void *(*)(void *))register_a_thread, (void *)this);
  
  return this;
}

void register_a_thread(void *argument) {
  thread this = (thread)argument;
  
  this->initialized = true;
  Thread.work(this);
  Thread.destroy(this);
  
  //return; /* This can never return; `Thread.destroy()` calls `pthread_exit()`. */
}

void thread__work(thread this) {
  /* This is the primary work loop. As long as the thread is `initialized`
   * (meaning it hasn’t been informed that it should terminate), it will
   * wait for signals (via it’s pool’s condvar) that there is work available
   * to be done, specifically, that there are routines in the queue to be
   * interpreted.
   * --
   * FIXME: Should we move the *loop* out of here, and just have the condition
   *        check? Perhaps move even that out, and only execute routines. */
  while (this->initialized) {
    pthread_mutex_lock  (                       this->pool->mutex);
    pthread_cond_wait   (this->pool->condition, this->pool->mutex);
    pthread_mutex_unlock(                       this->pool->mutex);
    
    /* Once the thread is woken up by a condvar signal, we check that there’s
     * actually routines to process (if not, it falls through to waiting
     * again) */
    while (this->initialized && this->pool->size > 0)
      Routine.execute( Pool.drip(this->pool) );
  }
  
  /* Usually, this is called from `register_a_thread()`, so it’s quite likely
   * that the thread will destroy itself after this returns. */
  return;
}

void thread__destroy(thread this) {
  this->initialized = false;
  
  /* If `this` is the current thread, we directly kill ourselves after having
   * cleaned up. Else, we `join` against the passed `thread`, blocking until
   * it finishes its work and terminates. We only preform the actual `free`ing
   * in the former case, because the latter case will *cause* the former,
   * eventually. */
  if (pthread_equal( pthread_self(), this->pthread )) {
    /* FIXME: How do I deallocate the `pthread_t` structure? There’s no
     *        documented `pthread_destroy()` function. */
    /* FIXME: How do I ensure nobody else tries to access this after it is
     *        freed? Other people may still have references to it. */
    free(this);
    pthread_exit(NULL);
  } else {
    /* TODO: Find a way to signal a specific thread to wake, instead of
     *       broadcasting a pointless wake to *all* threads in the pool. Seems
     *       wasteful, if not dangerous. */
    pthread_cond_broadcast(this->pool->condition);
    
    /* TODO: Replace this with an ‘is active’ mutex; prevent any destructive
     *       modifications to the `thread` structure while it’s running.
     *       Locking against that mutex would be equivalent to `join`ing,
     *       because the thread would only release the mutex while it’s
     *       shutting down. */
    pthread_join(this->pthread, NULL);
  }
  
  return; /* This will never return, if called from the thread itself */
}
