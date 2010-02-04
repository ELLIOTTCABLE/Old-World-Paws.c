#define NUMERIC_H

#ifndef TYPES_H
#  include "Paws.o/Types.h"
#endif
#ifndef LL_H
#  include "Paws.o/Core/ll.h"
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

struct Numeric_methods {
  numeric (*create)   (int);
  thing   (*to_thing) (numeric);
} const Numeric;
