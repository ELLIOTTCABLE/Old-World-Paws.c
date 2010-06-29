#include "Thread.c"
#include "Cest.h"

#include <errno.h>


CEST(Thread, allocate) {
  pool a_pool = Pool->allocate();
  thread a_thread;
  
  a_thread = Thread->allocate(a_pool);
  sleep(0); /* A little bit of a hack to try to avoid testing-specific race conditions; probably causes the
               scheduler to schedule the thread we just created instead of us. */
  
  /* `pthread_kill` sends a signal; but with a signal of `0`, no interrupt is actually preformed; instead, this
   * allows us to verify that the thread exists, according to `pthread.h`. */
  ASSERT( pthread_kill(a_thread->pthread, 0) != ESRCH  );
  ASSERT(              a_thread->pool        == a_pool );
  ASSERT(              a_thread->initialized == true   );
  
  // Can’t currently test this; we need to move it into a `routine` and put it in the work queue, so it
  // actually gets run *in the `thread`*.
  // ASSERT( pthread_getspecific(Thread->current_thread_key) == a_thread );
  
  SUCCEED;
}

CEST(Thread, current) { /* TODO: test. */ PEND; }
CEST(thread, work) { /* TODO: test. */ PEND; }

CEST(thread, destroy) {
  /* FIXME: This test ocassionally hangs */
  
  pool a_pool = Pool->allocate();
  thread a_thread;
  
  a_thread = Thread->allocate(a_pool);
  sleep(0);
  
  ASSERT( pthread_kill(a_thread->pthread, 0) != ESRCH  );
  ASSERT(              a_thread->initialized == true   );
  
  Thread->destroy(a_thread);
  sleep(0);
  
  ASSERT( pthread_kill(a_thread->pthread, 0) == ESRCH  );
  ASSERT(              a_thread->initialized == false   );
  
  SUCCEED;
}
