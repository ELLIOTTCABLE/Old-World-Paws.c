#if !defined(THREAD_DECLARATIONS)
# define     THREAD_DECLARATIONS

#include "Paws.o/Ancillary/Threading/Pool/Pool.h"

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
  E(thread)     (*allocate)     ( E(pool) a_pool );
  void          (*initialize)   ( void *argument ); /* Actually takes a `thread` */
  E(thread)     (*current)      ( void );
  
  /* `struct thread` methods */
  void          (*work)         ( E(thread) this );
  void          (*destroy)      ( E(thread) this );
  
  /* `Thread` data */
  pthread_key_t   current_thread_key;
};
#if !defined(EXTERNALIZE)
  struct E(Thread) extern *Thread;
#endif

void    Paws__register_Thread   ( void );

#endif
