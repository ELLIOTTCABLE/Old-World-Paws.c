#define NUMERIC_H

#if !defined(TYPES_H)
# include "Paws.o/Core/Types.h"
#endif

#if !defined(LL_H)
# include "Paws.o/Core/ll.h"
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
  E(ll) content; /* The `ll` behind this `numeric`’s `list` interface */
  /* TODO: Support floating-point values. */
  int   native;
};


/* ### Method Declarations ### */

struct E(Numeric) {
  /* `Numeric` functions */
  E(numeric)  (*create)   ( int );
  
  /* `struct numeric` methods */
  E(thing)    (*to_thing) ( E(numeric) );
  int         (*native)   ( E(numeric) );
};
#if !defined(EXTERNALIZE)
  struct E(Numeric) extern const Numeric;
#endif
