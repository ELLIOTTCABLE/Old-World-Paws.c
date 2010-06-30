#if !defined(THREADING_DECLARATIONS)
# define     THREADING_DECLARATIONS

#include "Paws.o/Ancillary/Threading/Pool/Pool.h"
#include "Paws.o/Ancillary/Threading/Thread/Thread.h"

struct E(Threading) {
  struct E(Pool)     *Pool;
  struct E(Thread)   *Thread;
};
#if !defined(EXTERNALIZE)
  struct E(Threading) extern *Threading;
#endif

void    Paws__register_Threading    ( void );

#endif
