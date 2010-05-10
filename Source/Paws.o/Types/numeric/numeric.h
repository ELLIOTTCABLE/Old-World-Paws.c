#define NUMERIC_H

#if !defined(CORE_H)
# include "Paws.o/Core.h"
#endif
#if !defined(TYPES_H)
# include "Paws.o/Types/Types.h"
#endif

#if !defined(LIST_H)
# include "Paws.o/Types/list/list.h"
#endif


/* =========================
= `infrastructure numeric` =
========================= */

/* ### Data Types & Structures ### */

/* `infrastructure numeric`, the numeric data structure of Paws, is herein
 * implemented natively with C `int` types. It provides no methods for
 * floating-point arithmetic.
 */
struct E(numeric) {
  E(ll)   content; /* The `ll` behind this `numeric`’s `list` interface */
  
  /* TODO: Support floating-point values. */
  int     native;
};


/* ### Method Declarations ### */

struct E(Numeric) {
  /* `Numeric` functions */
  E(numeric)    (*create)     ( int native );
  
  /* `struct numeric` methods */
  E(thing)      (*thing)      ( E(numeric) this );
  int           (*native)     ( E(numeric) this );
};
#if !defined(EXTERNALIZE)
  struct E(Numeric) extern *Numeric;
#endif

void    Paws__register_Numeric    ( void );
