#define THREAD_H

#if !defined(POOL_H)
# include "Paws.o/Ancillary/Threading/pool/pool.h"
#endif

#include <pthread.h>
#include <stdbool.h>


/* ==================
= Thread Management =
================== */

/* ### Data Types & Structures ### */

        struct E(thread); /* Our threading implementation’s thread object. */
typedef struct E(thread)* E(thread);

struct E(thread) {
  pthread_t     pthread; /* The underlying opaque POSIX thread-structure. (A pointer type!) */
  E(pool)       pool; /* The pool to which this thread belongs. */
  
  bool          initialized; /* Whether or not this thread is prepared to process routines */
};


/* ### Method Declarations ### */

struct E(Thread) {
  /* `Thread` functions */
  E(thread)   (*create)     ( E(pool) a_pool );
  
  /* `struct thread` methods */
  void        (*work)       ( E(thread) this );
  void        (*destroy)    ( E(thread) this );
};
#if !defined(EXTERNALIZE)
  struct E(Thread) extern const Thread;
#endif
