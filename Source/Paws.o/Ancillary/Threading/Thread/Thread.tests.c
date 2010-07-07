#include "Thread.c"

#define DECLARATIONS
# include "Cest.c"

# include <errno.h>
#undef  DECLARATIONS


CEST(Thread, allocate) {
  pool a_pool = Pool->allocate();
  thread a_thread;
  
  a_thread = Thread->allocate(a_pool);
  
  /* This is a bit of a hack; we loop until `a_thread->initialized` is `true`. However, we use a `for()` instead
   * of a `while`  */
  for (unsigned char i = 0; i < UCHAR_MAX; i++) { sleep(0); /* Cede scheduling */ if (a_thread->initialized) {
    
    /* `pthread_kill` sends a signal; but with a signal of `0`, no interrupt is actually preformed; instead, this
     * allows us to verify that the thread exists, according to `pthread.h`. */
    ASSERT( pthread_kill(a_thread->pthread, 0) != ESRCH  );
    ASSERT(              a_thread->pool        == a_pool );
    ASSERT(              a_thread->initialized == true   ); // Redundant, but… whatever.
    
    PEND;
    
    // Can’t currently test this; we need to move it into a `routine` and put it in the work queue, so it
    // actually gets run *in the `thread`*.
    // ASSERT( pthread_getspecific(Thread->current_thread_key) == a_thread );
    
    SUCCEED;
  }} FAIL; // This should never be reached.
}

CEST(Thread, current) { /* TODO: test. */ PEND; }
CEST(thread, work) { /* TODO: test. */ PEND; }

CEST(thread, destroy) {
  /* FIXME: This test ocassionally hangs */
  
  pool a_pool = Pool->allocate();
  thread a_thread;
  
  a_thread = Thread->allocate(a_pool);
  
  for (unsigned char i = 0; i < UCHAR_MAX; i++) { sleep(0); /* Cede scheduling */ if (a_thread->initialized) {
    ASSERT( pthread_kill(a_thread->pthread, 0) != ESRCH  );
    
    Thread->destroy(a_thread);
    for (unsigned char j = 0; j < UCHAR_MAX; j++) { sleep(0); /* Cede scheduling */ if (!a_thread->initialized) {
      ASSERT( pthread_kill(a_thread->pthread, 0) == ESRCH  );
      
      SUCCEED;
    }} FAIL;
  }} FAIL;
}
