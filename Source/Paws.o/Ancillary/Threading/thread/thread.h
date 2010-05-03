#define THREAD_H

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

struct E(thread) {
  pthread_t    *pthread; /* The underlying opaque POSIX thread-structure. */
};


/* ### Method Declarations ### */

struct E(Thread) {
  /* `Thread` functions */
  E(thread)   (*create)     ( void );
  
  /* `struct thread` methods */
  void        (*destroy)    ( E(thread) this );
};
#if !defined(EXTERNALIZE)
  struct E(Thread) extern const Thread;
#endif
