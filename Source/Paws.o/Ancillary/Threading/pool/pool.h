#define POOL_H

#if !defined(CORE_H)
# include "Paws.o/Core/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif


/* ==================
= Thread Management =
================== */

/* ### Data Types & Structures ### */

struct E(pool) {
  E(thread)    *pthread; /* The underlying opaque POSIX thread-structure. */
};


/* ### Method Declarations ### */

struct E(Pool) {
  /* `Pool` functions */
  E(pool)   (*create)     ( void );
  
  /* `struct pool` methods */
  void      (*destroy)    ( E(pool) this );
};
#if !defined(EXTERNALIZE)
  struct E(Pool) extern const Pool;
#endif
