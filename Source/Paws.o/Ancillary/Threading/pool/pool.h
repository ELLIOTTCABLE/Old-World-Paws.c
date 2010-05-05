#define POOL_H

#if !defined(CORE_H)
# include "Paws.o/Core/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#include <pthread.h>


/* ==================
= Thread Management =
================== */

/* ### Data Types & Structures ### */

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
  E(pool)       (*create)     ( void );
  
  /* `struct pool` methods */
  void          (*enqueue)    ( E(pool) this, E(routine) a_routine );
  E(routine)    (*drip)       ( E(pool) this );
  void          (*destroy)    ( E(pool) this );
};
#if !defined(EXTERNALIZE)
  struct E(Pool) extern const Pool;
#endif
