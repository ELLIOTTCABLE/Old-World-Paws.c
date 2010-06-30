#if !defined(POOL_DECLARATIONS)
# define     POOL_DECLARATIONS

#include "Paws.o/Types/routine/routine.h"

#include <pthread.h>


/* ==================
= Thread Management =
================== */

/* ### Data Types & Structures ### */

        struct E(pool); /* Our threading implementation’s queue pool. */
typedef struct E(pool)* E(pool);

typedef   unsigned long long int    E(pool_size); /* The maximum number of routine pointers in a pool */

struct E(pool) {
  pthread_mutex_t    *mutex; /* The mutex for this pool’s condvar */
  pthread_cond_t     *condition; /* A condvar that signals when routines are available to be interpreted */
  
  E(pool_size)        size; /* The number of `routine`s queued */
  E(routine)         *queue; /* An array of `routine` pointers */
};


/* ### Method Declarations ### */

struct E(Pool) {
  /* `Pool` functions */
  E(pool)       (*allocate)   ( void );
  
  /* `struct pool` methods */
  void          (*enqueue)    ( E(pool) this, E(routine) a_routine );
  E(routine)    (*drip)       ( E(pool) this );
  void          (*destroy)    ( E(pool) this );
};
#if !defined(EXTERNALIZE)
  struct E(Pool) extern *Pool;
#endif

void    Paws__register_Pool   ( void );

#endif
