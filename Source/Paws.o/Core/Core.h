#define CORE_H

#if defined(EXTERNALIZE)
      /* Heh. Heheh. */
# define E(NAME) \
    Paws__ ## NAME
#else
# define E(NAME) \
    NAME
#endif
