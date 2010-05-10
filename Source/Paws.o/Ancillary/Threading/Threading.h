#define THREADING_H

#if !defined(POOL_H)
# include "Paws.o/Ancillary/Threading/pool/pool.h"
#endif
#if !defined(THREAD_H)
# include "Paws.o/Ancillary/Threading/thread/thread.h"
#endif

struct E(Threading) {
  struct E(Pool)     *Pool;
  struct E(Thread)   *Thread;
};
#if !defined(EXTERNALIZE)
  struct E(Threading) extern *Threading;
#endif

void    Paws__register_Threading    ( void );
