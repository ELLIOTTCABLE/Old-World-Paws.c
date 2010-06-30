#if !defined(NUMERIC_DECLARATIONS)
# define     NUMERIC_DECLARATIONS

#include "Paws.o/Core.h"
#include "Paws.o/Types/Types.h"

#include "Paws.o/Types/list/list.h"


/* =========================
= `infrastructure numeric` =
========================= */

/* ### Data Types & Structures ### */

/* `infrastructure numeric`, the numeric data structure of Paws, is herein implemented natively with C `int`
 * types. It provides no recourse for floating-point arithmetic. */
struct E(numeric) {
  E(ll)   content; /* The `ll` behind this `numeric`’s `list` interface */
  
  /* TODO: Support floating-point values. */
  int     native;
};


/* ### Method Declarations ### */

struct E(Numeric) {
  /* `Numeric` functions */
  E(numeric)    (*allocate)   ( int native );
  
  /* `struct numeric` methods */
  E(thing)      (*thing)      ( E(numeric) this );
  int           (*native)     ( E(numeric) this );
};
#if !defined(EXTERNALIZE)
  struct E(Numeric) extern *Numeric;
#endif

void    Paws__register_Numeric    ( void );

#endif
