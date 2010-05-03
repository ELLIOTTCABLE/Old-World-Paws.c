#define THREADING_H

#if !defined(THREAD_H)
# include "Paws.o/Ancillary/Threading/thread/thread.h"
#endif
#if !defined(POOL_H)
# include "Paws.o/Ancillary/Threading/pool/pool.h"
#endif


struct E(Threading) {
  struct E(Thread)    Thread;
  struct E(Pool)      Pool;
};
#if !defined(EXTERNALIZE)
  struct E(Threading) extern Threading;
#endif
