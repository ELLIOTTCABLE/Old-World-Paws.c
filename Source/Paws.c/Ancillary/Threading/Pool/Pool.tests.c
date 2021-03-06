#include "Pool.c"

#define DECLARATIONS
# include "Cest.c"

# include <errno.h>
#undef  DECLARATIONS


CEST(Pool, allocate) {
  pool a_pool = Pool->allocate();
  
  ASSERT( a_pool->size  == 0    );
  ASSERT( a_pool->queue == NULL );
  
  /* These are hacky ways to test whether the mutex and condvar were initialized */
  ASSERT( pthread_mutex_trylock(a_pool->mutex)     != EINVAL );
          pthread_mutex_unlock (a_pool->mutex);
  ASSERT( pthread_cond_signal  (a_pool->condition) != EINVAL );
  
  SUCCEED;
}

CEST(pool, enqueue) {
  pool    a_pool = Pool->allocate();
  routine routine1 = Routine->allocate(Node->scope()),
          routine2 = Routine->allocate(Node->scope()),
          routine3 = Routine->allocate(Node->scope());
  
  Pool->enqueue(a_pool, routine1);
  ASSERT( *((routine *)a_pool->queue + 0) == routine1 );
  ASSERT(              a_pool->size       == 1        );
  
  Pool->enqueue(a_pool, routine2);
  ASSERT( *((routine *)a_pool->queue + 0) == routine1 );
  ASSERT( *((routine *)a_pool->queue + 1) == routine2 );
  ASSERT(              a_pool->size       == 2        );
  
  Pool->enqueue(a_pool, routine3);
  ASSERT( *((routine *)a_pool->queue + 0) == routine1 );
  ASSERT( *((routine *)a_pool->queue + 1) == routine2 );
  ASSERT( *((routine *)a_pool->queue + 2) == routine3 );
  ASSERT(              a_pool->size       == 3        );
  
  PEND;
  
  /* TODO: Test that the condvar is properly signaled. */
  
  SUCCEED;
}

CEST(pool, drip) {
  pool    a_pool = Pool->allocate();
  routine routine1 = Routine->allocate(Node->scope()); Pool->enqueue(a_pool, routine1);
  routine routine2 = Routine->allocate(Node->scope()); Pool->enqueue(a_pool, routine2);
  routine routine3 = Routine->allocate(Node->scope()); Pool->enqueue(a_pool, routine3);
  
  ASSERT(            a_pool->size == 3        );
  ASSERT( Pool->drip(a_pool)      == routine1 );
  ASSERT(            a_pool->size == 2        );
  ASSERT( Pool->drip(a_pool)      == routine2 );
  ASSERT(            a_pool->size == 1        );
  ASSERT( Pool->drip(a_pool)      == routine3 );
  ASSERT(            a_pool->size == 0        );
  
  SUCCEED;
}

CEST(pool, destroy) { PEND; }
