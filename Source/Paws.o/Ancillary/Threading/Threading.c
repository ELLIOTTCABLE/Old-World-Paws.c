#if !defined(THREADING_DECLARATIONS)
# define     THREADING_DECLARATIONS

#if !defined(DECLARATIONS)
# define THREADING_C__BEHEST
# define DECLARATIONS
#endif
#   include "Paws.o/Ancillary/Threading/Pool/Pool.c"
#   include "Paws.o/Ancillary/Threading/Thread/Thread.c"
#if defined(THREADING_C__BEHEST)
# undef DECLARATIONS
#endif


struct E(Threading) {
  struct E(Pool)     *Pool;
  struct E(Thread)   *Thread;
};
#if !defined(EXTERNALIZE)
  struct E(Threading) extern *Threading;
#endif

void    Paws__register_Threading    ( void );



#endif
#if !defined(DECLARATIONS) && !defined(THREADING_IMPLEMENTATION) /* ===================================== BODY */
# define                               THREADING_IMPLEMENTATION
# define DECLARATIONS
#   include "Paws.o/Paws.c"
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


                               struct Threading // »
                                     *Threading   = NULL;
void Paws__register_Threading(void) { Threading   = malloc(sizeof(struct Threading));
                  Paws->Threading   = Threading;
  
  struct Threading // »
  data = {
    .Pool     = NULL,
    .Thread   = NULL
  };
  
  memcpy(Threading, &data, sizeof(struct Threading));
  
  Paws__register_Pool();
  Paws__register_Thread();
}

#endif
