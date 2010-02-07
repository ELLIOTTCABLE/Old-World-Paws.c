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
struct numeric {
  ll  content; /* The `ll` behind this `numeric`’s `list` interface */
  /* TODO: Support floating-point values. */
  int native;
};


/* ### Method Declarations ### */

struct Paws__Numeric {
  /* `Numeric` functions */
  numeric (*create)   (int);
  
  /* `struct numeric` methods */
  thing   (*to_thing) (numeric);
};
#if !defined(EXTERNALIZE)
  struct Paws__Numeric extern const Numeric;
#endif
